####################################################################################################
# 2020-2020, David Rowenhorst/The US Naval Research Laboratory, Washington DC
# Pursuant to title 17 section 105 of the United States Code, works of US Governement employees 
# are not not subject to copyright protection.
#
# Copyright (c) 2013-2014, Marc De Graef/Carnegie Mellon University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
#
#     - Redistributions of source code must retain the above copyright notice, this list
#        of conditions and the following disclaimer.
#     - Redistributions in binary form must reproduce the above copyright notice, this
#        list of conditions and the following disclaimer in the documentation and/or
#        other materials provided with the distribution.
#     - Neither the names of Marc De Graef, Carnegie Mellon University nor the names
#        of its contributors may be used to endorse or promote products derived from
#        this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
# USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
####################################################################################################


#Author David Rowenhorst/The US Naval Research Laboratory, Washington DC
# A translation of the original f.90 code produced by Marc De Graef
#
# This implementation is dependant on the Numba Python package, which gives a significant increase in 
# speed (other than the first time called due to compilation time). The numba implmentation is very non-Numpy-like in that
# Loops are not discouraged.  
# No guarantee - but this library is typically numerically accurate to around 5e-6 degrees or better.
# The rotations.py is typically more accurate at the cost of being about 2-10x slower.

# All inputs can be numpy array-like, and either arrays of shape (n,m) OR (m)  where m is the length of a single 
# representation (i.e. for Euler m = 3, for quaternions m = 4); in the case of orientation matrices (om)
# the inputs/outputs should be (n,3,3) OR (3,3). 
# 
# If the inputs are not in C-order or not aligned, a copy of the input will be made. 
#
#

import numpy as np
import numba

P = 1
eps = 1.0e-12 # used for "closeto" approximations in Numba code
PI = np.pi
PI2 = 2.0 * np.pi
nbcache = False # switch to false for debugging.
nbParallel = True # decide if parallelism is desired.
# Once the JIT compiler runs over the code, changing this will not change the parallelism.  
# The package will need to be reimported
nbFastmath = True


# this will check the type of the input and its size.  
# it will also reshape the data in case it is a single dimension
# returns a 2D view of the data, the length of one entry, the number of entries, and datatype. 
@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache)
def prepIn(a):
  shape = a.shape
  intype = a.dtype
  m = shape[-1]
  n = numba.int64(a.size / m)
  aout = a.reshape(n,m)
  return (aout,m,n,intype)


def eu2om(eu,p=P):
  '''Bunge Euler angles to orientation matrix'''
  om = eu2omL(np.require(eu,requirements=['C','A']),p=p)
  om = np.squeeze(om)
  return om


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def eu2omL(euIn,p=P):
  eu,m,n,intype = prepIn(euIn)
  om = np.zeros((n,3,3),dtype=intype)
  for i in numba.prange(n):
    c1 = np.cos(eu[i,0])
    c2 = np.cos(eu[i,1])
    c3 = np.cos(eu[i,2])
    s1 = np.sin(eu[i,0])
    s2 = np.sin(eu[i,1])
    s3 = np.sin(eu[i,2])
    om[i,0,0] = c1 * c3 - s1 * s3 * c2
    om[i,0,1] = s1 * c3 + c1 * s3 * c2
    om[i,0,2] = s3 * s2
    om[i,1,0] = -c1 * s3 - s1 * c3 * c2
    om[i,1,1] = -s1 * s3 + c1 * c3 * c2
    om[i,1,2] = c3 * s2
    om[i,2,0] = s1 * s2
    om[i,2,1] = -c1 * s2
    om[i,2,2] = c2
  return om

 
def eu2ax(eu,p=P):
  '''Bunge Euler angles to axis-angle (radians)  '''
  ax = eu2axL(np.require(eu,requirements=['C','A']),p=p)
  ax = np.squeeze(ax)
  return ax


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def eu2axL(euIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  eu,m,n,intype = prepIn(euIn)
  ax = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    t = np.tan(eu[i,1] * 0.5)
    sig = 0.50 * (eu[i,0] + eu[i,2])
    ssig = np.sin(sig)
    delt = 0.50 * (eu[i,0] - eu[i,2])
    tau = np.sqrt(t * t + ssig * ssig)

    if (np.abs(sig - PI2) < eps):
      alpha = PI
    else:
      alpha = 2.0 * np.arctan(tau / np.cos(sig))

    if np.abs(alpha) < eps:
      ax[i,0] = 0.0
      ax[i,1] = 0.0
      ax[i,2] = -1.0 * pf
      ax[i,3] = 0.0
    else:
      ax[i,0] = -1.0 * pf * t * np.cos(delt) / tau
      ax[i,1] = -1.0 * pf * t * np.sin(delt) / tau
      ax[i,2] = -1.0 * ssig / tau
      ax[i,3] = alpha

    if alpha < 0.0:
      for j in range(4):
        ax[i,j] *= -1.0
  return ax


def eu2qu(eu,p=P):
  '''Bunge Euler angles to quaternions (scalar, axis)  '''
  qu = eu2quL(np.require(eu,requirements=['C','A']),p=p)
  qu = np.squeeze(qu)
  return qu


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def eu2quL(euIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  eu,m,n,intype = prepIn(euIn)
  qu = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    phi1 = eu[i,0] * 0.5
    phi = eu[i,1] * 0.5
    phi2 = eu[i,2] * 0.5

    dphi1phi2 = phi1 - phi2
    sphi1phi2 = phi1 + phi2
    cphi = np.cos(phi)
    sphi = -1.0 * np.sin(phi)
    qu[i,0] = cphi * np.cos(sphi1phi2) + 0.0
    sign = 1.0 if (qu[i,0] >= 0.0) else -1.0
    qu[i,0] *= sign
    qu[i,1] = pf * sign * sphi * np.cos(dphi1phi2) + 0.0
    qu[i,2] = pf * sign * sphi * np.sin(dphi1phi2) + 0.0
    qu[i,3] = -1.0 * pf * sign * cphi * np.sin(sphi1phi2) + 0.0
  qu = quatnormL(qu)
  return qu


def om2eu(om,p=P):
  '''orientation matrix to Bunge Euler angles'''
  if om.ndim == 3:
    omIn = np.require(om,requirements=['C','A'])
  elif om.ndim == 2:
    omIn = np.require(om,requirements=['C','A']).reshape(1,3,3)
  else:
    return -1
  eu = om2euL(omIn,p=p)
  eu = np.squeeze(eu)
  return eu


@numba.jit(nopython=True,fastmath=nbFastmath, cache=nbcache, parallel=nbParallel)
def om2euL(om, p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  intype = om.dtype
  n = np.int64(om.size / 9)
  eu = np.zeros((n, 3), dtype=intype)
  for i in numba.prange(n):
    # [0,0], [0,1], [0, 2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
    #    0      1      2      3      4      5      6      7      8
    if (1.0 - np.abs(om[i, 2, 2])) > eps:
      eu[i,1] = np.arccos(om[i,2,2])
      zeta = 1.0 / (np.sqrt(1.0 - om[i,2,2] * om[i,2,2]))
      eu[i,0] = np.arctan2(om[i,2,0] * zeta,-1.0 * om[i,2,1] * zeta)
      eu[i,2] = np.arctan2(om[i,0,2] * zeta,om[i,1,2] * zeta)
    else:
      if ((np.abs(om[i,2,2] - 1.0)) < eps):
        eu[i,0] = np.arctan2(om[i,0,1],om[i,0,0])
        eu[i,1] = 0.0
        eu[i,2] = 0.0
      else:
        eu[i,0] = -np.arctan2(om[i,0,1],om[i,0,0])
        eu[i,1] = PI
        eu[i,2] = 0.0
    eu[i,0] += 100.0 * PI
    eu[i,0] = np.fmod(eu[i,0],PI2)
    eu[i,2] += 100.0 * PI
    eu[i,2] = np.fmod(eu[i,2],PI2)
  return eu


def ax2om(ax,p=P):
  '''axis-angle (radians) to orientation matrix  '''
  om = ax2omL(np.require(ax,requirements=['C','A']),p=p)
  om = np.squeeze(om)
  return om


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ax2omL(axIn,p=P):
  ax,m,n,intype = prepIn(axIn)
  om = np.zeros((n,3,3),dtype=intype)
  axn = axnormL(ax)
  # [0,0], [0,1], [0, 2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
  #    0      1      2      3      4      5      6      7      8
  for i in numba.prange(n):
    c = np.cos(axn[i,3])
    s = np.sin(axn[i,3])
    omc = 1.0 - c
    for j in range(3):
      om[i,j,j] = axn[i,j] * axn[i,j] * omc + c
    q = omc * axn[i,0] * axn[i,1]
    om[i,1,0] = q + s * axn[i,2]
    om[i,0,1] = q - s * axn[i,2]

    q = omc * axn[i,1] * axn[i,2]
    om[i,2,1] = q + s * axn[i,0]
    om[i,1,2] = q - s * axn[i,0]

    q = omc * axn[i,2] * axn[i,0]
    om[i,0,2] = q + s * axn[i,1]
    om[i,2,0] = q - s * axn[i,1]

    if (p < 0):
      om[i,:,:] = np.transpose(om[i,:,:])

  return om


def qu2eu(qu,p=P):
  '''quaternions (scalar, axis) to Bunge Euler angles  '''
  eu = qu2euL(np.require(qu,requirements=['C','A']),p=p)
  eu = np.squeeze(eu)
  return eu


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def qu2euL(quIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  qu,m,n,intype = prepIn(quIn)
  eu = np.zeros((n,3),dtype=intype)
  for i in numba.prange(n):
    q0 = pf * qu[i,0]
    q03 = q0 * q0 + qu[i,3] * qu[i,3]
    q12 = qu[i,1] * qu[i,1] + qu[i,2] * qu[i,2]
    chi = np.sqrt(q03 * q12)

    if (chi == 0.0):
      if (q12 == 0.0):
        eu[i,2] = 0.0
        eu[i,1] = 0.0
        eu[i,0] = np.arctan2(-2.0 * q0 * qu[i,3],q0 * q0 - qu[i,3] * qu[i,3])
      else:
        eu[i,2] = 0.0
        eu[i,1] = PI
        eu[i,0] = np.arctan2(2.0 * qu[i,1] * qu[i,2],qu[i,1] * qu[i,1] - qu[i,2] * qu[i,2])
    else:
      eu[i,1] = np.arctan2(2.0 * chi,q03 - q12)

      diff = np.arctan2(-qu[i,2],-qu[i,1])
      sum = np.arctan2(-qu[i,3],q0)
      eu[i,0] = diff + sum
      eu[i,2] = sum - diff

    eu[i,0] += PI2
    eu[i,0] = np.fmod(eu[i,0],PI2)
    eu[i,2] += PI2
    eu[i,2] = np.fmod(eu[i,2],PI2)

  return eu


def ax2ho(ax,p=P):
  '''axis-angle (radians) to homochoric vector  '''
  ho = ax2hoL(np.require(ax,requirements=['C','A']))
  ho = np.squeeze(ho)
  return ho


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ax2hoL(axIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  # intype = ax.dtype
  # n = np.int64(ax.size / 4)
  ax,m,n,intype = prepIn(axIn)
  ho = np.zeros((n,3),dtype=intype)
  axn = axnormL(ax)
  #axn = ax
  for i in numba.prange(n):
    f = 0.75 * (axn[i,3] - np.sin(axn[i,3]))
    f = f ** (1.0 / 3.0)
    for j in range(3):
      ho[i,j] = f * axn[i,j]
  return ho


def ho2ax(ho,p=P):
  '''homochoric vector to axis-angle (radians)   '''
  ax = ho2axL(np.require(ho,requirements=['C','A']))
  ax = np.squeeze(ax)
  return ax


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ho2axL(hoIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ho,m,n,intype = prepIn(hoIn)
  ax = np.zeros((n,4),dtype=intype)

  tfit = np.array([1.0000000000018852,-0.5000000002194847,-0.024999992127593126,
                   -0.003928701544781374,-0.0008152701535450438,-0.0002009500426119712,
                   -0.00002397986776071756,-0.00008202868926605841,0.00012448715042090092,
                   -0.0001749114214822577,0.0001703481934140054,-0.00012062065004116828,
                   0.000059719705868660826,-0.00001980756723965647,0.000003953714684212874,
                   -0.00000036555001439719544],dtype=np.float64)

  for i in numba.prange(n):
    hmag = np.float64(0.0)
    for j in range(3):
      hmag += ho[i,j] * ho[i,j]
    if hmag < eps:
      ax[i,0] = 0.0
      ax[i,1] = 0.0
      ax[i,2] = -1.0 * pf
      ax[i,3] = 0.0
    else:
      hm = hmag
      sqrthm = np.sqrt(hm)
      hn = np.zeros(3,dtype=intype)
      for j in range(3):
        hn[j] = ho[i,j] / sqrthm
      # hn = ho[i,:]/sqrthm
      s = tfit[0] + tfit[1] * hmag
      for j in range(2,16):
        hm *= hmag
        s += tfit[j] * hm
      s = 1.0 if (s > 1.0) else s
      s = -1.0 if (s < -1.0) else s
      s = 2.0 * np.arccos(s)

      for j in range(3):
        ax[i,j] = hn[j]
      if np.abs(s - PI) < eps:
        ax[i,3] = PI
      else:
        ax[i,3] = s

  return ax


def ro2ax(ro,p=P):
  '''Rodrigues-Frank vector to axis-angle (radians)  '''
  ax = ro2axL(np.require(ro,requirements=['C','A']),p=p)
  ax = np.squeeze(ax)
  return ax


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ro2axL(roIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ro,m,n,intype = prepIn(roIn)
  ax = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    ta = ro[i,3]
    if ta < eps:
      ax[i,0] = 0.0
      ax[i,1] = 0.0
      ax[i,2] = -1 * pf
      ax[i,3] = 0.0
    else:
      if ta == np.inf:
        ax[i,0] = ro[i,0]
        ax[i,1] = ro[i,1]
        ax[i,2] = ro[i,2]
        ax[i,3] = PI
      else:
        ax[i,3] = 2.0 * np.arctan(ta)
        ta = 0.0
        for j in range(3):
          ta += ro[i,j] * ro[i,j]
        ta = 1.0 / np.sqrt(ta)
        for j in range(3):
          ax[i,j] = ro[i,j] * ta
  return ax


def ax2ro(ax,p=P):
  '''axis-angle (radians) to Rodrigues-Frank vector  '''
  ro = ax2roL(np.require(ax,requirements=['C','A']),p=p)
  ro = np.squeeze(ro)
  return ro


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ax2roL(axIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ax,m,n,intype = prepIn(axIn)
  ro = np.zeros((n,4),dtype=intype)
  axn = axnormL(ax)
  for i in numba.prange(n):
    if axn[i,3] == 0:
      ro[i,0] = 0.0
      ro[i,1] = 0.0
      ro[i,2] = -1.0 * pf
      ro[i,3] = 0.0
    else:
      for j in range(3):
        ro[i,j] = axn[i,j]
      if (PI - ax[i,3]) < eps:
        ro[i,3] = np.inf
      else:
        ro[i,3] = np.tan(axn[i,3] * 0.5)
  return ro


def ax2qu(ax,p=P):
  '''axis-angle (radians) to quaternion (scalar - vector)  '''
  qu = ax2quL(np.require(ax,requirements=['C','A']),p=p)
  qu = np.squeeze(qu)
  return qu


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ax2quL(axIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ax,m,n,intype = prepIn(axIn)
  qu = np.zeros((n,4),dtype=intype)
  axn = axnormL(ax)
  #axn = ax
  for i in numba.prange(n):
    if axn[i,3] < eps:
      qu[i,0] = 1.0
      qu[i,1] = 0.0
      qu[i,2] = 0.0
      qu[i,3] = 0.0
    else:
      qu[i,0] = np.cos(ax[i,3] * 0.5)
      mag = 0.0
      for j in range(3):
        mag += ax[i,j] * ax[i,j]
      s = np.sin(ax[i,3] * 0.5) / mag
      for j in range(3):
        qu[i,j + 1] = ax[i,j] * s
  qu = quatnormL(qu)
  return qu


def ro2ho(ro,p=P):
  '''Rodrigues-Frank  to homochoric  '''
  ho = ro2hoL(np.require(ro,requirements=['C','A']),p=p)
  ho = np.squeeze(ho)
  return ho


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def ro2hoL(roIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ro,m,n,intype = prepIn(roIn)
  ho = np.zeros((n,3),dtype=intype)
  for i in numba.prange(n):
    mag = ro[i,3]
    if mag < eps:
      ho[i,0] = 0.0
      ho[i,1] = 0.0
      ho[i,2] = 0.0
    else:
      if mag > 1e9:
        f = 0.75 * PI
      else:
        t = 2.0 * np.arctan(ro[i,3])
        f = 0.75 * (t - np.sin(t))
      f = f ** (1.0 / 3.0)
      for j in range(3):
        ho[i,j] = ro[i,j] * f

  return ho


def qu2om(qu,p=P):
  '''quaternion (scalar-vector) to orientation matrix  '''
  om = qu2omL(np.require(qu,requirements=['C','A']),p=p)
  om = np.squeeze(om)
  return om


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def qu2omL(quIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  qu,m,n,intype = prepIn(quIn)
  om = np.zeros((n,3,3),dtype=intype)
  # [0,0], [0,1], [0, 2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
  #    0      1      2      3      4      5      6      7      8
  qu = quatnormL(qu)


  for i in numba.prange(n):
    q0 = qu[i,0] * pf
    qq = q0 * q0 - (qu[i,1] ** 2 + qu[i,2] ** 2 + qu[i,3] ** 2)
    om[i,0,0] = qq + 2.0 * qu[i,1] * qu[i,1]
    om[i,0,1] = 2.0 * (qu[i,1] * qu[i,2] - qu[i,0] * qu[i,3])
    om[i,0,2] = 2.0 * (qu[i,1] * qu[i,3] + qu[i,0] * qu[i,2])
    om[i,1,0] = 2.0 * (qu[i,2] * qu[i,1] + qu[i,0] * qu[i,3])
    om[i,1,1] = qq + 2.0 * qu[i,2] * qu[i,2]
    om[i,1,2] = 2.0 * (qu[i,2] * qu[i,3] - qu[i,0] * qu[i,1])
    om[i,2,0] = 2.0 * (qu[i,3] * qu[i,1] - qu[i,0] * qu[i,2])
    om[i,2,1] = 2.0 * (qu[i,3] * qu[i,2] + qu[i,0] * qu[i,1])
    om[i,2,2] = qq + 2.0 * qu[i,3] * qu[i,3]

    tr = om[i,0,0] + om[i,1,1] + om[i,2,2]
    t = 0.50 * (tr - 1.0)
    if np.abs(t) > 1.0:  # there has been enough rounding to justify a re normalization of the matrix
      #using a Gram-Schmidt normalization
      u1 = om[i,0,:]
      u1 /= np.linalg.norm(u1)
      om[i,0,:] = u1
      u2 = om[i,1,:]
      u2 = u2-np.sum(u2*u1)*u1
      u2 /= np.linalg.norm(u2)
      om[i,1,:] = u2
      u3 = om[i,2,:]
      u3 - np.sum(u3*u1)*u1 - np.sum(u3*u2)*u2
      u3 /= np.linalg.norm(u3)
      om[i,2,:] = u3

  return om

def om2ax_old(om,p=P):
  '''orientation matrix to axis-angle (radians) -- depreciated now use qu2ax(om2qu()) '''
  if om.ndim == 3:
    omIn = np.require(om,requirements=['C','A'])
  elif om.ndim == 2:
    omIn = np.require(om,requirements=['C','A']).reshape(1,3,3)
  else:
    return -1
  ax = om2axL(omIn,p=p)
  ax = np.squeeze(ax)
  return ax


@numba.jit(nopython=True,fastmath=nbFastmath, cache=nbcache, parallel=nbParallel)
def om2axL(om, p=P):# depreciated now use qu2ax(om2qu()) -- kept for historical reasons.
  pf = numba.float32(p > 0) * 2.0 - 1.0
  intype = om.dtype
  n = np.int64(om.size / 9)
  ax = np.zeros((n, 4), dtype=intype)
  #  help for translating out of C version
  # [0,0], [0,1], [0, 2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2] 
  #    0      1      2      3      4      5      6      7      8
  for i in numba.prange(n):

    tr = om[i,0,0] + om[i,1,1] + om[i,2,2]
    t = 0.50 * (tr - 1.0)
    t = 1.0 if (t > 1.0) else t
    t = -1.0 if (t < -1.0) else t
    ax[i,3] = np.arccos(t)
    #if ((1.0 - np.abs(t)) > eps):
    mag = numba.float64(0.0)
    ax[i,2] = pf * (om[i,1,0] - om[i,0,1])
    mag += ax[i,2]*ax[i,2]
    ax[i,1] = pf * (om[i,0,2] - om[i,2,0])
    mag += ax[i,1] * ax[i,1]
    ax[i,0] = pf * (om[i,2,1] - om[i,1,2])
    mag += ax[i,0] * ax[i,0]
    mag = np.sqrt(mag)
    if mag > eps:
      for j in range(3):
        ax[i,j] *= 1.0/mag
    else:
      if t > 0.0:
        ax[i, 0] = 0.0
        ax[i, 1] = 0.0
        ax[i, 2] = -1.0*pf
      else:
        d = np.zeros(3,dtype=intype)
        for j in range(3):
          d[j] = np.sqrt(0.5*(om[i,j,j]+1.0))
        dargsrt = np.argsort(d)
        d[dargsrt[1]] = (om[i, dargsrt[2], dargsrt[1]] + om[i, dargsrt[1], dargsrt[2] ]) / (4.0 * d[dargsrt[2]])
        d[dargsrt[0]] = (om[i, dargsrt[2], dargsrt[0]] + om[i, dargsrt[0], dargsrt[2]]) / (4.0 * d[dargsrt[2]])

        for j in range(3):
          ax[i,j] = pf*d[j]

  ax = axnormL(ax)
  return ax

@numba.jit(nopython=True,fastmath=False, cache=nbcache, parallel=nbParallel)
def om2axL_2(om, p=P): # kept for historical reasons
  # ** not sure it gets the axis correct when angle = pi **
  pf = numba.float32(p > 0) * 2.0 - 1.0
  intype = om.dtype
  n = np.int64(om.size / 9)
  ax = np.zeros((n, 4), dtype=intype)
  #  help for translating out of C version
  # [0,0], [0,1], [0, 2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
  #    0      1      2      3      4      5      6      7      8
  for i in numba.prange(n):

    tr = om[i,0,0] + om[i,1,1] + om[i,2,2]
    t = 0.50 * (tr - 1.0)
    t = 1.0 if (t > 1.0) else t
    t = -1.0 if (t < -1.0) else t
    ax[i,3] = np.arccos(t)
    if (ax[i,3] < 1.0e-7):
      ax[i,0] = 0.0
      ax[i,1] = 0.0
      ax[i,2] = -1.0 * pf
    else:
      omcomplex = np.zeros((3,3), dtype=numba.complex128)
      omcomplex[:,:] = om[i,:,:]
      eigval, eigvect = np.linalg.eig(omcomplex)
      whmin = np.argmin(np.absolute(eigval-1.0))
      vect = np.real(eigvect[:,whmin])
      d = (om[i,2,1] - om[i,1,2])
      if d != 0.0:
        vect[0] = np.abs(vect[0])*np.sign(d)

      d = (om[i,0,2] - om[i,2,0])
      if d != 0.0:
        vect[1] = np.abs(vect[1]) * np.sign(d)

      d = (om[i,1,0] - om[i,0,1])
      if d != 0.0:
        vect[2] = np.abs(vect[2]) * np.sign(d)

      ax[i,0] = pf*vect[0]
      ax[i,1] = pf*vect[1]
      ax[i,2] = pf*vect[2]
  ax = axnormL(ax)
  return ax

def om2qu(om,p=P):
  '''orientation matrix to quaternion (scalar-vector)  '''
  if om.ndim == 3:
    omIn = np.require(om,requirements=['C','A'])
  elif om.ndim == 2:
    omIn = np.require(om,requirements=['C','A']).reshape(1,3,3)
  else:
    return -1
  qu = om2quL(omIn,p=p)
  qu = np.squeeze(qu)
  return qu


@numba.jit(nopython=True,fastmath=nbFastmath, cache=nbcache, parallel=nbParallel)
def om2quL(om, p=P):
  """
      Thanks to Martin-Diehl using the same formulation as his rotations.py package.
      This fixes the ambiguity of the axis direction when the angle = pi.
      This also means that om2ax is now qu2ax(om2qu())
      This formulation is from  www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion.
      The original formulation had issues.
  """
  pf = numba.float32(p > 0) * 2.0 - 1.0
  intype = om.dtype
  n = np.int64(om.size / 9)
  qu = np.zeros((n, 4), dtype=intype)

  for i in numba.prange(n):
    s = 0.0
    tr = om[i,0,0] + om[i,1,1] + om[i,2,2]
    if tr > 0:
      s = 0.5 / np.sqrt(tr + 1.0)
      qu[i,0] = 0.25/s
      qu[i,1] = s * (om[i,2,1] - om[i,1,2])
      qu[i,2] = s * (om[i,0,2] - om[i,2,0])
      qu[i,3] = s * (om[i,1,0] - om[i,0,1])
    else:
      if (om[i,0,0] > om[i,1,1]) and (om[i,0,0] > om[i,2,2]):
        s = 2.0 * np.sqrt( 1.0 + om[i,0,0] - om[i,1,1] - om[i,2,2])
        qu[i,0] = (om[i,2,1] - om[i,1,2]) / s
        qu[i,1] = 0.25 * s
        qu[i,2] = (om[i,0,1] + om[i,1,0]) / s
        qu[i,3] = (om[i,0,2] + om[i,2,0]) / s
      elif om[i,1,1] > om[i,2,2]:
        s = 2.0 * np.sqrt(1.0 - om[i,0,0] + om[i,1,1] - om[i,2,2])
        qu[i,0] = (om[i,0,2] - om[i,2,0]) / s
        qu[i,1] = (om[i,0,1] + om[i,1,0]) / s
        qu[i,2] = 0.25 * s
        qu[i,3] = (om[i,1,2] + om[i,2,1]) / s
      else:
        s = 2.0 * np.sqrt(1.0 - om[i,0,0] - om[i,1,1] + om[i,2,2])
        qu[i,0] = (om[i,1,0] - om[i,0,1]) / s
        qu[i,1] = (om[i,0,2] + om[i,2,0]) / s
        qu[i,2] = (om[i,1,2] + om[i,2,1]) / s
        qu[i,3] = 0.25 * s
  qu = quatnormL(qu)
  return qu

def qu2ax(qu,p=P):
  '''quaternion (scalar-vector) to axis-angle (radians)  '''
  ax = qu2axL(np.require(qu,requirements=['C','A']),p=p)
  ax = np.squeeze(ax)
  return ax


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def qu2axL(quIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  qu,m,n,intype = prepIn(quIn)
  qu = quatnormL(qu)
  ax = np.zeros((n,4),dtype=intype)

  for i in numba.prange(n):

    if qu[i,0] > (1.0-eps):
      ax[i,0] = 0.0
      ax[i,1] = 0.0
      ax[i,2] = -pf
      ax[i,3] = 0.0
    else:
      omega = 2.0 * np.arccos(qu[i,0])
      mag = 0.0
      for j in range(3):
        mag += qu[i,j + 1] ** 2
      mag = 1.0 / (np.sqrt(mag)+1e-35)
      for j in range(3):
        ax[i,j] = qu[i,j + 1] * mag
      ax[i,3] = omega

  return ax


def qu2ro(qu,p=P):
  '''quaternion (scalar-vector) to Rodrigues-Frank vector  '''
  ro = qu2roL(np.require(qu,requirements=['C','A']),p=p)
  ro = np.squeeze(ro)
  return ro


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def qu2roL(quIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  qu,m,n,intype = prepIn(quIn)
  qu = quatnormL(qu)
  ro = np.zeros((n,4),dtype=intype)

  for i in numba.prange(n):

    if qu[i,0] < eps:
      ro[i,3] = np.inf
      for j in range(3):
        ro[i,j] = qu[i,j + 1]
    else:
      mag = 0.0
      for j in range(3):
        mag += qu[i,j + 1] ** 2
      if mag < eps:
        ro[0] = 0.0
        ro[1] = 0.0
        ro[2] = -pf
        ro[3] = 0.0
      else:
        mag = 1.0 / np.sqrt(mag)
        q0 = qu[i,0]
        q0 = 1.0-eps if q0 > 1.0 else q0
        q0 = -1.0+eps if q0 < -1.0 else q0
        ro[i,3] = np.tan(np.arccos(q0))
        for j in range(3):
          ro[i,j] = qu[i,j + 1] * mag
  return ro


def qu2ho(qu,p=P):
  '''quaternion (scalar-vector) to homochoric  '''
  ho = qu2hoL(np.require(qu,requirements=['C','A']),p=p)
  ho = np.squeeze(ho)
  return ho


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def qu2hoL(quIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  qu,m,n,intype = prepIn(quIn)
  qu = quatnormL(qu)
  ho = np.zeros((n,3),dtype=intype)

  for i in numba.prange(n):

    if qu[i,0] > (1.0-eps):
      ho[i,0] = 0.0
      ho[i,1] = 0.0
      ho[i,2] = 0.0
    else:
      omega = 2.0 * np.arccos(qu[i,0])
      mag = 0.0
      for j in range(3):
        mag += qu[i,j + 1] ** 2
      f = 0.75 * (omega - np.sin(omega))
      f = f ** (1.0 / 3.0)
      mag = f / np.sqrt(mag)
      for j in range(3):
        ho[i,j] = qu[i,j + 1] * mag
  return ho

def ho2cu(ho,p=P):
  ''' homochoric to cubochoric  '''
  cu = ho2cuL(np.require(ho,requirements=['C','A']),p=p)
  cu = np.squeeze(cu)
  return cu


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache, parallel=nbParallel)
def ho2cuL(hoIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  ho,m,n,intype = prepIn(hoIn)
  cu = np.zeros((n,3),dtype=intype)
  LPR1 = np.float(1.33067003949147)  # (3pi/4)**(1/3)
  LPpref = np.float(1.38197659788534)  # sqrt(6/pi)
  LPbeta = np.float(0.962874509979126)  # pi**(5/6)/6**(1/6)/2
  LPr2 = np.float(1.4142135623731)  # sqrt(2)
  LPpi12 = np.float(0.261799387799149)  # pi/12
  LPsc = np.float(0.897772786961286)  # a/ap == (pi**(5/6)/6**(1/6)) / pi**(2/3)
  eps_loc = 1e-7



  for i in numba.prange(n):
    #cu[i,:] = lambert3DBallToCube(ho[i,:])
    # I have inlined all the function of lambert3DCubeToBall
    # numba really dislikes nested function calls.  This was about a 10x speedup.
    xyz = np.zeros(3,dtype=np.float64)
    xyzcu = np.zeros(3,dtype=np.float64)
    xyz3 = np.zeros(3,dtype=np.float64)
    xyz2 = np.zeros(3,dtype=np.float64)
    xyz1 = np.zeros(3,dtype=np.float64)
    rs = 0.0
    for j in range(3):
      xyz[j] = ho[i,j]
      rs += xyz[j] * xyz[j]
    rs = np.sqrt(np.float64(max(rs,0.0)))

    # if rs > (LPR1 + eps_loc):
    #  return xyzcu-np.float64(5.0) # out of range
    py = 10
    if (np.abs(xyz[0]) <= xyz[2]) and (np.abs(xyz[1]) <= xyz[2]):
      py = 1
    if (np.abs(xyz[0]) <= -xyz[2]) and (np.abs(xyz[1]) <= -xyz[2]):
      py = 2
    if (np.abs(xyz[2]) <= xyz[0]) and (np.abs(xyz[1]) <= xyz[0]):
      py = 3
    if (np.abs(xyz[2]) <= -xyz[0]) and (np.abs(xyz[1]) <= -xyz[0]):
      py = 4
    if (np.abs(xyz[0]) <= xyz[1]) and (np.abs(xyz[2]) <= xyz[1]):
      py = 5
    if (np.abs(xyz[0]) <= -xyz[1]) and (np.abs(xyz[2]) <= -xyz[1]):
      py = 6

    if (py == 1) or (py == 2):
      xyz3[0] = xyz[0]
      xyz3[1] = xyz[1]
      xyz3[2] = xyz[2]
    if (py == 3) or (py == 4):
      xyz3[0] = xyz[1]
      xyz3[1] = xyz[2]
      xyz3[2] = xyz[0]
    if (py == 5) or (py == 6):
      xyz3[0] = xyz[2]
      xyz3[1] = xyz[0]
      xyz3[2] = xyz[1]

    q = np.sqrt(np.float64(max(2.0 * rs / (rs + np.abs(xyz3[2]) + eps),0.0)))
    xyz2[0] = xyz3[0] * q
    xyz2[1] = xyz3[1] * q
    sign = 1.0 if (xyz3[2] >= 0.0) else -1.0
    xyz2[2] = sign * rs / LPpref

    qxy = 0.0
    for j in range(2):
      qxy += xyz2[j] * xyz2[j]

    if qxy == 0.0:
      xyz1[0] = 0.0
      xyz1[1] = 0.0
    else:
      xyswitch = np.abs(xyz2[1]) <= np.abs(xyz2[0])
      if xyswitch:
        x = xyz2[0]
        y = xyz2[1]
      else:
        x = xyz2[1]
        y = xyz2[0]
      q2xy = qxy + x * x
      sq2xy = np.sqrt(q2xy)

      q = q2xy * qxy / (q2xy - np.abs(x) * sq2xy)
      q = np.sqrt(np.float64(max(q,0.0)))
      q *= LPbeta / LPr2 / LPR1

      tt = (y * y + np.abs(x) * sq2xy) / LPr2 / qxy
      if tt > 1.0:
        tt = 1.0
      if tt < -1.0:
        tt = -1.0

      ac = np.arccos(tt)
      sx = 1.0 if (x >= 0.0) else -1.0
      sy = 1.0 if (y >= 0.0) else -1.0

      T1inv = q * sx
      T2inv = q * sy * ac / LPpi12

      if xyswitch:
        xyz1[0] = T1inv
        xyz1[1] = T2inv
      else:
        xyz1[1] = T1inv
        xyz1[0] = T2inv

    xyz1[2] = xyz2[2]
    for j in range(3):
      xyz1[j] *= 1.0 / LPsc

    if (py == 1) or (py == 2):
      xyzcu[0] = xyz1[0]
      xyzcu[1] = xyz1[1]
      xyzcu[2] = xyz1[2]
    if (py == 3) or (py == 4):
      xyzcu[0] = xyz1[2]
      xyzcu[1] = xyz1[0]
      xyzcu[2] = xyz1[1]
    if (py == 5) or (py == 6):
      xyzcu[0] = xyz1[1]
      xyzcu[1] = xyz1[2]
      xyzcu[2] = xyz1[0]
    for j in range(3):
      cu[i, j] = xyzcu[j]
  return cu

def cu2ho(cu,p=P):
  ''' cubochoric to homochoric  '''
  ho = cu2hoL(np.require(cu,requirements=['C','A']),p=p)
  ho = np.squeeze(ho)
  return ho


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache, parallel=nbParallel)
def cu2hoL(cuIn,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  cu,m,n,intype = prepIn(cuIn)
  ho = np.zeros((n,3),dtype=intype)
  LPap = np.float64(2.14502939711103)  # pi**(2/3)
  LPa = np.float64(1.92574901995825)  # pi**(5/6)/6**(1/6)
  LPsc = np.float64(0.897772786961286)  # a/ap == (pi**(5/6)/6**(1/6)) / pi**(2/3)
  LPpref = np.float64(1.38197659788534)  # sqrt(6/pi)
  LPpi12 = np.float64(0.261799387799149)  # pi/12
  LPr2 = np.float64(1.4142135623731)  # sqrt(2)
  LPprek = np.float64(1.6434564029725)  # R1 2**(1/4)/beta == (3pi/4)^(1/3) * 2**(1/4) / (pi**(5/6)/6**(1/6)/2)
  LPsPi = np.float64(1.77245385090552)  # sqrt(pi)
  LPr24 = np.float64(4.89897948556636)  # sqrt(24)
  eps_loc = 2e-6



  # I have inlined all the function of lambert3DCubeToBall
  # numba really dislikes nested function calls.  This was about a 10x speedup.
  # for i in numba.prange(n):
  #   ho[i, :] = lambert3DCubeToBall(cu[i,:])

  for i in numba.prange(n):
    xyz = np.zeros(3,dtype=np.float64)
    xyzba = np.zeros(3,dtype=np.float64)
    sXYZ = np.zeros(3,dtype=np.float64)
    #xyz[:] = cu[i,:]
    xyz[0] = cu[i,0]
    xyz[1] = cu[i,1]
    xyz[2] = cu[i,2]
    mx = np.abs(xyz).max()

    # if mx > (LPap/2.0 + eps_loc):
    #  return np.float64([-5,-5, -5]) #xyzba out of range

    py = 10
    if (np.abs(xyz[0]) <= xyz[2]) and (np.abs(xyz[1]) <= xyz[2]):
      py = 1
    if (np.abs(xyz[0]) <= -xyz[2]) and (np.abs(xyz[1]) <= -xyz[2]):
      py = 2
    if (np.abs(xyz[2]) <= xyz[0]) and (np.abs(xyz[1]) <= xyz[0]):
      py = 3
    if (np.abs(xyz[2]) <= -xyz[0]) and (np.abs(xyz[1]) <= -xyz[0]):
      py = 4
    if (np.abs(xyz[0]) <= xyz[1]) and (np.abs(xyz[2]) <= xyz[1]):
      py = 5
    if (np.abs(xyz[0]) <= -xyz[1]) and (np.abs(xyz[2]) <= -xyz[1]):
      py = 6

    if (py == 1) or (py == 2):
      sXYZ[0] = xyz[0]
      sXYZ[1] = xyz[1]
      sXYZ[2] = xyz[2]
    if (py == 3) or (py == 4):
      sXYZ[0] = xyz[1]
      sXYZ[1] = xyz[2]
      sXYZ[2] = xyz[0]
    if (py == 5) or (py == 6):
      sXYZ[0] = xyz[2]
      sXYZ[1] = xyz[0]
      sXYZ[2] = xyz[1]

    for j in range(3):
      sXYZ[j] = sXYZ[j] * LPsc

    if mx < eps:
      sXYZ[:] = 0.0
    else:
      absX = np.abs(sXYZ[0])
      absY = np.abs(sXYZ[1])

      if (absX < eps) and (absY < eps):
        sXYZ[0] = 0.0
        sXYZ[1] = 0.0
        sXYZ[2] = LPpref * sXYZ[2]
      else:
        z = np.float64(sXYZ[2])
        xyswitch = np.abs(sXYZ[1]) <= np.abs(sXYZ[0])
        if xyswitch:
          x = np.float64(sXYZ[0])
          y = np.float64(sXYZ[1])
        else:
          x = np.float64(sXYZ[1])
          y = np.float64(sXYZ[0])

        q = LPpi12 * y / x
        c = np.float64(np.cos(q))
        s = np.float64(np.sin(q))

        q = LPprek * x / np.sqrt(np.float64(max(LPr2 - c,0.0)))
        T1p = (LPr2 * c - 1.0) * q
        T2p = LPr2 * s * q
        if xyswitch:
          T1 = np.float64(T1p)
          T2 = np.float64(T2p)
        else:
          T1 = np.float64(T2p)
          T2 = np.float64(T1p)

        c = T1 * T1 + T2 * T2
        s = np.pi * c / (24.0 * z * z)

        c = LPsPi * c / LPr24 / z
        q = np.sqrt(np.float64(max([1.0 - s,0.0])))

        sXYZ[0] = T1 * q
        sXYZ[1] = T2 * q
        sXYZ[2] = LPpref * z - c

    if (py == 1) or (py == 2):
      xyzba[0] = sXYZ[0]
      xyzba[1] = sXYZ[1]
      xyzba[2] = sXYZ[2]
    if (py == 3) or (py == 4):
      xyzba[0] = sXYZ[2]
      xyzba[1] = sXYZ[0]
      xyzba[2] = sXYZ[1]
    if (py == 5) or (py == 6):
      xyzba[0] = sXYZ[1]
      xyzba[1] = sXYZ[2]
      xyzba[2] = sXYZ[0]

    for j in range(3):
      ho[i,j] = xyzba[j]

  return ho

# cross dependant codes start here
def eu2ro(eu,p=P):
  '''Bunge Euler angles to Rodrigues-Frank vector  '''
  ro = ax2ro(eu2ax(eu, p=p), p=p)
  return ro

def ro2om(ro,p=P):
  '''Rodrigues-Frank vector to orientation matrix   '''
  om = ax2om(ro2ax(ro, p=p), p=p)
  return om

def ro2eu(ro,p=P):
  '''Rodrigues-Frank vector to Bunge Euler angles  '''
  eu = om2eu(ro2om(ro, p=p), p=p)
  return eu

def eu2ho(eu,p=P):
  '''Bunge Euler angles to homochoric  '''
  ho = ax2ho(eu2ax(eu, p=p), p=p)
  return ho

def om2qu_old(om,p=P):
  '''orientation matrix to quaternion (scalar-vector)  '''
  qu = ax2qu(om2ax(om, p=p), p=p)
  return qu

def om2ax(om,p=P):
  '''orientation matrix to quaternion (scalar-vector)  '''
  ax = qu2ax(om2qu(om, p=p), p=p)
  return ax


def om2ro(om,p=P):
  '''orientation matrix to Rodrigues-Frank vector  '''
  ro = eu2ro(om2eu(om, p=p), p=p)
  return ro

def om2ho(om,p=P):
  '''orientation matrix to homochoric  '''
  ho = ax2ho(om2ax(om, p=p), p=p)
  return ho

def ax2eu(ax,p=P):
  '''axis-angle to Bunge Euler angle  '''
  eu = om2eu(ax2om(ax, p=p), p=p)
  return eu

def ro2qu(ro,p=P):
  '''Rodrigues-Frank vector to quaternion (scalar-vector)  '''
  qu = ax2qu(ro2ax(ro, p=p), p=p)
  return qu

def ho2eu(ho,p=P):
  '''homochoric to Bunge Euler angles  '''
  eu = ax2eu(ho2ax(ho, p=p), p=p)
  return eu

def ho2om(ho,p=P):
  '''homochoric to orientation matrix  '''
  om = ax2om(ho2ax(ho, p=p), p=p)
  return om

def ho2ro(ho,p=P):
  '''homochoric to Rodrigues-Frank vector  '''
  ro = ax2ro(ho2ax(ho, p=p), p=p)
  return ro

def ho2qu(ho,p=P):
  '''homochoric to quaternion (scalar-vector)  '''
  qu = ax2qu(ho2ax(ho, p=p), p=p)
  return qu

def eu2cu(eu,p=P):
  '''Bunge Euler angles in cubochoric  '''
  cu = ho2cu(eu2ho(eu, p=p), p=p)
  return cu

def om2cu(om,p=P):
  '''orientation matrix to cubochoric  '''
  cu = ho2cu(om2ho(om, p=p), p=p)
  return cu

def ax2cu(ax,p=P):
  '''axis-angle to cubochoric  '''
  cu = ho2cu(ax2ho(ax, p=p), p=p)
  return cu

def ro2cu(ro,p=P):
  '''Rodrigues-Frank vector to cubochoric  '''
  cu = ho2cu(ro2ho(ro, p=p), p=p)
  return cu

def qu2cu(qu,p=P):
  '''quaternion (scalar-vector) to cubochoric  '''
  cu = ho2cu(qu2ho(qu, p=p), p=p)
  return cu

def cu2eu(cu,p=P):
  '''cubochoric to Bunge Euler angles  '''
  eu = ho2eu(cu2ho(cu, p=p), p=p)
  return eu

def cu2om(cu,p=P):
  '''cubochoric to orientation matrix  '''
  om = ho2om(cu2ho(cu, p=p), p=p)
  return om

def cu2ax(cu,p=P):
  '''cubochoric to axis-angle  '''
  ax = ho2ax(cu2ho(cu, p=p), p=p)
  return ax

def cu2ro(cu,p=P):
  '''cubochoric to Rodrigues-Frank vector  '''
  ro = ho2ro(cu2ho(cu, p=p), p=p)
  return ro

def cu2qu(cu,p=P):
  '''cubochoric to quaternion (scalar-vector)  '''
  qu = ho2qu(cu2ho(cu, p=p), p=p)
  return qu

# Lambert Ball <--> Cube codes


@numba.jit(['int32(f8[:])','int32(f4[:])'], nopython=True,fastmath=nbFastmath,cache=nbcache)
def lambertGetPyramid(xyz):
  out = numba.int32(10)
  if (np.abs(xyz[0]) <= xyz[2]) and (np.abs(xyz[1]) <= xyz[2]):
    out = 1
  if (np.abs(xyz[0]) <= -xyz[2] ) and (np.abs(xyz[1]) <= -xyz[2]):
    out = 2
  if (np.abs(xyz[2]) <= xyz[0]) and (np.abs(xyz[1]) <= xyz[0]):
    out = 3
  if (np.abs(xyz[2]) <= -xyz[0]) and (np.abs(xyz[1]) <= -xyz[0]):
    out = 4
  if (np.abs(xyz[0]) <= xyz[1]) and (np.abs(xyz[2]) <= xyz[1]):
    out = 5
  if (np.abs(xyz[0]) <= -xyz[1]) and (np.abs(xyz[2]) <= -xyz[1]):
    out = 6
  return out

@numba.jit(['f8[:](f8[:])','f8[:](f4[:])'], nopython=True,fastmath=nbFastmath,cache=nbcache)
def lambert3DCubeToBall(xyz):
  LPap = np.float64(2.14502939711103) # pi**(2/3)
  LPa =   np.float64(1.92574901995825) # pi**(5/6)/6**(1/6)
  LPsc =  np.float64(0.897772786961286) # a/ap == (pi**(5/6)/6**(1/6)) / pi**(2/3)
  LPpref =  np.float64(1.38197659788534) # sqrt(6/pi)
  LPpi12 =  np.float64(0.261799387799149) # pi/12
  LPr2 =  np.float64(1.4142135623731) # sqrt(2)
  LPprek =  np.float64(1.6434564029725) # R1 2**(1/4)/beta == (3pi/4)^(1/3) * 2**(1/4) / (pi**(5/6)/6**(1/6)/2)
  LPsPi =  np.float64(1.77245385090552) # sqrt(pi)
  LPr24 =  np.float64(4.89897948556636) # sqrt(24)
  eps_loc = 2e-6

  xyzba = np.zeros(3, dtype = np.float64)
  sXYZ = np.zeros(3, dtype = np.float64)
  mx = np.abs(xyz).max()

  #if mx > (LPap/2.0 + eps_loc):
  #  return np.float64([-5,-5, -5]) #xyzba out of range

  p = lambertGetPyramid(xyz)

  if (p == 1) or (p == 2):
    sXYZ[0] = xyz[0]
    sXYZ[1] = xyz[1]
    sXYZ[2] = xyz[2]
  if (p == 3) or (p == 4):
    sXYZ[0] = xyz[1]
    sXYZ[1] = xyz[2]
    sXYZ[2] = xyz[0]
  if (p == 5) or (p == 6):
    sXYZ[0] = xyz[2]
    sXYZ[1] = xyz[0]
    sXYZ[2] = xyz[1]

  for i in range(3):
    sXYZ[i] = sXYZ[i] * LPsc


  if mx < eps:
    sXYZ[:] = 0.0
  else:
    absX = np.abs(sXYZ[0])
    absY = np.abs(sXYZ[1])


    if (absX < eps) and (absY < eps):
      sXYZ[0] = 0.0
      sXYZ[1] = 0.0
      sXYZ[2] = LPpref *sXYZ[2]
    else:
      z = np.float64(sXYZ[2])
      xyswitch = np.abs(sXYZ[1]) <= np.abs(sXYZ[0])
      if xyswitch:
        x = np.float64(sXYZ[0])
        y = np.float64(sXYZ[1])
      else:
        x = np.float64(sXYZ[1])
        y = np.float64(sXYZ[0])

      q = LPpi12 * y / x
      c = np.float64(np.cos(q))
      s = np.float64(np.sin(q))

      q = LPprek * x/np.sqrt(np.float64(max(LPr2 - c, 0.0)))
      T1p = (LPr2 * c - 1.0) * q
      T2p = LPr2 *  s * q
      if xyswitch:
        T1 = np.float64(T1p)
        T2 = np.float64(T2p)
      else:
        T1 = np.float64(T2p)
        T2 = np.float64(T1p)

      c = T1*T1 + T2*T2
      s = np.pi * c / (24.0 * z *z)

      c = LPsPi * c / LPr24 / z
      q = np.sqrt(np.float64(max([1.0-s, 0.0])))

      sXYZ[0] = T1 * q
      sXYZ[1] = T2 * q
      sXYZ[2] = LPpref * z -c

  if (p == 1) or (p == 2):
    xyzba[0] = sXYZ[0]
    xyzba[1] = sXYZ[1]
    xyzba[2] = sXYZ[2]
  if (p == 3) or (p == 4):
    xyzba[0] = sXYZ[2]
    xyzba[1] = sXYZ[0]
    xyzba[2] = sXYZ[1]
  if (p == 5) or (p == 6):
    xyzba[0] = sXYZ[1]
    xyzba[1] = sXYZ[2]
    xyzba[2] = sXYZ[0]
  return xyzba


@numba.jit(['f8[:](f8[:])','f8[:](f4[:])'], nopython=True,fastmath=nbFastmath, cache=nbcache)
def lambert3DBallToCube(xyz):
  LPR1 = np.float(1.33067003949147) # (3pi/4)**(1/3)
  LPpref = np.float(1.38197659788534) # sqrt(6/pi)
  LPbeta = np.float(0.962874509979126) # pi**(5/6)/6**(1/6)/2
  LPr2 = np.float(1.4142135623731) # sqrt(2)
  LPpi12 = np.float(0.261799387799149) # pi/12
  LPsc = np.float(0.897772786961286) # a/ap == (pi**(5/6)/6**(1/6)) / pi**(2/3)
  eps_loc = 1e-7

  xyzcu = np.zeros(3, dtype = np.float64)
  xyz3 = np.zeros(3,dtype=np.float64)
  xyz2 = np.zeros(3,dtype=np.float64)
  xyz1 = np.zeros(3,dtype=np.float64)
  rs = 0.0
  for i in range(3):
    rs += xyz[i] * xyz[i]
  rs = np.sqrt(np.float64(max(rs, 0.0)))

  #if rs > (LPR1 + eps_loc):
  #  return xyzcu-np.float64(5.0) # out of range

  p = lambertGetPyramid(xyz)
  if (p == 1) or (p == 2):
    xyz3[0] = xyz[0]
    xyz3[1] = xyz[1]
    xyz3[2] = xyz[2]
  if (p == 3) or (p == 4):
    xyz3[0] = xyz[1]
    xyz3[1] = xyz[2]
    xyz3[2] = xyz[0]
  if (p == 5) or (p == 6):
    xyz3[0] = xyz[2]
    xyz3[1] = xyz[0]
    xyz3[2] = xyz[1]

  q = np.sqrt(np.float64(max(2.0 * rs/(rs+np.abs(xyz3[2])+eps), 0.0)))
  xyz2[0] = xyz3[0] * q
  xyz2[1] = xyz3[1] * q
  sign = 1.0 if (xyz3[2] >= 0.0) else -1.0
  xyz2[2] = sign * rs/LPpref

  qxy = 0.0
  for i in range(2):
    qxy += xyz2[i]*xyz2[i]

  if qxy == 0.0:
    xyz1[0] = 0.0
    xyz1[1] = 0.0
  else:
    xyswitch = np.abs(xyz2[1]) <= np.abs(xyz2[0])
    if xyswitch:
      x = xyz2[0]
      y = xyz2[1]
    else:
      x = xyz2[1]
      y = xyz2[0]
    q2xy = qxy + x * x
    sq2xy = np.sqrt(q2xy)

    q = q2xy * qxy/(q2xy - np.abs(x)*sq2xy)
    q = np.sqrt(np.float64(max(q,0.0)))
    q *= LPbeta / LPr2 / LPR1

    tt = (y * y + np.abs(x) * sq2xy) / LPr2 / qxy
    if tt > 1.0:
      tt = 1.0
    if tt < -1.0:
      tt = -1.0

    ac = np.arccos(tt)
    sx = 1.0 if (x >= 0.0) else -1.0
    sy = 1.0 if (y >= 0.0) else -1.0

    T1inv = q * sx
    T2inv = q * sy * ac/LPpi12

    if xyswitch:
      xyz1[0] = T1inv
      xyz1[1] = T2inv
    else:
      xyz1[1] = T1inv
      xyz1[0] = T2inv

  xyz1[2] = xyz2[2]
  for i in range(3):
    xyz1[i] *= 1.0/LPsc

  if (p == 1) or (p == 2):
    xyzcu[0] = xyz1[0]
    xyzcu[1] = xyz1[1]
    xyzcu[2] = xyz1[2]
  if (p == 3) or (p == 4):
    xyzcu[0] = xyz1[2]
    xyzcu[1] = xyz1[0]
    xyzcu[2] = xyz1[1]
  if (p == 5) or (p == 6):
    xyzcu[0] = xyz1[1]
    xyzcu[1] = xyz1[2]
    xyzcu[2] = xyz1[0]
  return xyzcu

# Basic quaternion functions

def quatnorm(qu):
  '''quaternion normalization -- first term >=0 , unit quaternion length'''
  qout = quatnormL(np.require(qu,requirements=['C','A']))
  qout = np.squeeze(qout)
  return qout


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def quatnormL(qu,unitNorm=True):
  qin,m,n,intype = prepIn(qu)
  qout = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    sign = 1.0 if (qin[i,0] >= 0.0) else -1.0
    sum = 0.0
    for j in range(4):
      qout[i,j] = qin[i,j] * sign
      sum += qout[i,j] * qout[i,j]
    sum = 1.0/(np.sqrt(sum)+1.0e-35)
    if unitNorm == True:
      for j in range(4):
        qout[i,j] *= sum
  return qout

def quatconj(qu):
  '''Provides a quaternion conjugate. For rotations quaternions, this is the inverse quaternion'''
  qout = quatconjL(np.require(qu,requirements=['C','A']))
  qout = np.squeeze(qout)
  return qout


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def quatconjL(quin,unitNorm=True):
  qu,m,n,intype = prepIn(quin)
  qout = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    qout[i,0] = qu[i,0]
    for j in range(3):
      qout[i,j+1] = -1.0*qu[i,j+1]
  return qout

def quat_multiply(q1,q2,p=P):
  '''quaternion multiplication. Can be q1(Nx4) x q2(N x4) or q1(4) x q2(Nx4)'''
  q1q2 = quat_multiplyL(np.require(q1,requirements=['C','A']),np.require(q2,requirements=['C','A']),p=p)
  q1q2 = np.squeeze(q1q2)
  return q1q2


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache)
def quat_multiplyL(q1In,q2In,p=P):
  q1,m,n1,intype = prepIn(q1In)
  q2,m,n2,intype = prepIn(q2In)
  n = max(n1,n2)
  if n1 == n2:
    q1q2 = quat_multiplyLNN(q1,q2,n,intype,p=p)
  elif n1 < n2:
    q0 = q1[0,:]
    q1q2 = quat_multiplyL1N(q0,q2,n,intype,p=p)
  elif n2 < n1:
    q0 = q2[0,:]
    q1q2 = quat_multiplyL1N(q0,q1,n,intype,p=-p)
  #q1q2 = quatnormL(q1q2,unitNorm=False)
  return q1q2


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def quat_multiplyLNN(q1,q2,n,intype,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  q1q2 = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    q1q2[i,0] = q1[i,0] * q2[i,0] - (q1[i,1] * q2[i,1] + q1[i,2] * q2[i,2] + q1[i,3] * q2[i,3])
    q1q2[i,1] = q1[i,0] * q2[i,1] + q2[i,0] * q1[i,1] + pf * (q1[i,2] * q2[i,3] - q1[i,3] * q2[i,2])
    q1q2[i,2] = q1[i,0] * q2[i,2] + q2[i,0] * q1[i,2] + pf * (q1[i,3] * q2[i,1] - q1[i,1] * q2[i,3])
    q1q2[i,3] = q1[i,0] * q2[i,3] + q2[i,0] * q1[i,3] + pf * (q1[i,1] * q2[i,2] - q1[i,2] * q2[i,1])
  return q1q2

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def quat_multiplyL1N(q1,q2,n,intype,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  q1q2 = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    q1q2[i,0] = q1[0] * q2[i,0] - (q1[1] * q2[i,1] + q1[2] * q2[i,2] + q1[3] * q2[i,3])
    q1q2[i,1] = q1[0] * q2[i,1] + q2[i,0] * q1[1] + pf * (q1[2] * q2[i,3] - q1[3] * q2[i,2])
    q1q2[i,2] = q1[0] * q2[i,2] + q2[i,0] * q1[2] + pf * (q1[3] * q2[i,1] - q1[1] * q2[i,3])
    q1q2[i,3] = q1[0] * q2[i,3] + q2[i,0] * q1[3] + pf * (q1[1] * q2[i,2] - q1[2] * q2[i,1])
  return q1q2

# @numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=True)
# def quatMultiplyLN1(q1,q2,n,intype, p=P):
#   q1q2 = np.zeros((n,4),dtype=intype)
#   for i in numba.prange(n):
#     q1q2[i,:] = quatMultiply1(q1[i,:],q2,p=p)
#   return q1q2

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache)
def quat_multiply1(q1,q2,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  q1q2 = np.zeros_like(q1)
  q1q2[0] = q1[0] * q2[0] - (q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3])
  q1q2[1] = q1[0] * q2[1] + q2[0] * q1[1] + pf * (q1[2] * q2[3] - q1[3] * q2[2])
  q1q2[2] = q1[0] * q2[2] + q2[0] * q1[2] + pf * (q1[3] * q2[1] - q1[1] * q2[3])
  q1q2[3] = q1[0] * q2[3] + q2[0] * q1[3] + pf * (q1[1] * q2[2] - q1[2] * q2[1])
  return q1q2


def quat_vector(q,v,p=P):
  '''quaternion vector rotation. Can be q1(Nx4) x v(Nx3) or q1(4) x v(Nx3) or q1(Nx4) x v(3)'''
  vout = quat_vectorL(np.require(q,requirements=['C','A']),np.require(v,requirements=['C','A']),p=p)
  vout = np.squeeze(vout)
  return vout

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache)
def quat_vectorL(qIn,vIn,p=P):
  q,mq,n1,intype = prepIn(qIn)
  v,mv,n2,intype = prepIn(vIn)
  n = max(n1,n2)
  #vout = np.zeros((n,3),dtype=intype)
  if n1 == n2:
    vout = quat_vectorLNN(q,v,n,intype,p=p)
  if n1 < n2:
    q0 = q[0,:]
    vout = quat_vectorL1N(q0,v,n,intype,p=p)
  if n2 < n1:
    v0 = v[0,:]
    vout = quat_vectorLN1(q,v0,n,intype,p=p)
  return vout

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=True)
def quat_vectorLNN(q,v,n,intype,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  vout = np.zeros((n,3),dtype=intype)
  vtemp = np.zeros((3),dtype=intype)
  vtemp2 = np.zeros((3),dtype=intype)
  r = np.zeros((3),dtype=intype)
  w = numba.float64(0.0)
  for i in numba.prange(n):
    w = q[i,0]
    r[0] = pf * q[i,1]
    r[1] = pf * q[i,2]
    r[2] = pf * q[i,3]

    # Wow oh wow, numba hates function calls in a loop! 100x speedup
    #vtemp = np.cross(r,v[i,:])
    #vtemp = qv_crossp(r,v[i,:])
    vtemp[0] = r[1] * v[i,2] - r[2] * v[i,1]
    vtemp[1] = r[2] * v[i,0] - r[0] * v[i,2]
    vtemp[2] = r[0] * v[i,1] - r[1] * v[i,0]

    for j in range(3):
      vtemp[j] += w * v[i,j]

    #vtemp2 = np.cross(r,vtemp)
    #vtemp2 = qv_crossp(r,vtemp)
    vtemp2[0] = r[1] * vtemp[2] - r[2] * vtemp[1]
    vtemp2[1] = r[2] * vtemp[0] - r[0] * vtemp[2]
    vtemp2[2] = r[0] * vtemp[1] - r[1] * vtemp[0]


    for j in range(3):
      vout[i,j] = 2.0 * vtemp2[j] + v[i,j]

  return vout

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=True)
def quat_vectorL1N(q,v,n,intype,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  vout = np.zeros((n,3),dtype=intype)
  vtemp = np.zeros((3),dtype=intype)
  vtemp2 = np.zeros((3),dtype=intype)
  r = np.zeros((3),dtype=intype)
  w = numba.float64(0.0)
  for i in numba.prange(n):
    w = q[0]
    r[0] = pf * q[1]
    r[1] = pf * q[2]
    r[2] = pf * q[3]

    # Wow oh wow, numba hates function calls in a loop! 100x speedup
    #vtemp = np.cross(r,v[i,:])
    #vtemp = qv_crossp(r,v[i,:])
    vtemp[0] = r[1] * v[i,2] - r[2] * v[i,1]
    vtemp[1] = r[2] * v[i,0] - r[0] * v[i,2]
    vtemp[2] = r[0] * v[i,1] - r[1] * v[i,0]

    for j in range(3):
      vtemp[j] += w * v[i,j]

    #vtemp2 = np.cross(r,vtemp)
    #vtemp2 = qv_crossp(r,vtemp)
    vtemp2[0] = r[1] * vtemp[2] - r[2] * vtemp[1]
    vtemp2[1] = r[2] * vtemp[0] - r[0] * vtemp[2]
    vtemp2[2] = r[0] * vtemp[1] - r[1] * vtemp[0]


    for j in range(3):
      vout[i,j] = 2.0 * vtemp2[j] + v[i,j]

  return vout

@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=True)
def quat_vectorLN1(q,v,n,intype,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  vout = np.zeros((n,3),dtype=intype)
  vtemp = np.zeros((3),dtype=intype)
  vtemp2 = np.zeros((3),dtype=intype)
  r = np.zeros((3),dtype=intype)
  w = numba.float64(0.0)
  for i in numba.prange(n):
    w = q[i,0]
    r[0] = pf * q[i,1]
    r[1] = pf * q[i,2]
    r[2] = pf * q[i,3]

    # Wow oh wow, numba hates function calls in a loop! 100x speedup
    # vtemp = np.cross(r,v)
    # vtemp = qv_crossp(r,v)
    vtemp[0] = r[1] * v[2] - r[2] * v[1]
    vtemp[1] = r[2] * v[0] - r[0] * v[2]
    vtemp[2] = r[0] * v[1] - r[1] * v[0]

    for j in range(3):
      vtemp[j] += w * v[j]

    # vtemp2 = np.cross(r,vtemp)
    # vtemp2 = qv_crossp(r,vtemp)
    vtemp2[0] = r[1] * vtemp[2] - r[2] * vtemp[1]
    vtemp2[1] = r[2] * vtemp[0] - r[0] * vtemp[2]
    vtemp2[2] = r[0] * vtemp[1] - r[1] * vtemp[0]

    for j in range(3):
      vout[i,j] = 2.0 * vtemp2[j] + v[j]

  return vout


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache)
def quat_vector1(q,v,p=P):
  pf = numba.float32(p > 0) * 2.0 - 1.0
  vout = np.zeros_like(v)
  vtemp = np.zeros_like(v)
  vtemp2 = np.zeros_like(v)
  r = np.zeros_like(v)
  w = q[0]
  r[0] = pf * q[1]
  r[1] = pf * q[2]
  r[2] = pf * q[3]
  #cross product r,v
  vtemp[0] = r[1] * v[2] - r[2] * v[1]
  vtemp[1] = r[2] * v[0] - r[0] * v[2]
  vtemp[2] = r[0] * v[1] - r[1] * v[0]
  for j in range(3):
    vtemp[j] += w * v[j]

  # cross product r, vtemp
  vtemp2[0] = r[1] * vtemp[2] - r[2] * vtemp[1]
  vtemp2[1] = r[2] * vtemp[0] - r[0] * vtemp[2]
  vtemp2[2] = r[0] * vtemp[1] - r[1] * vtemp[0]

  for j in range(3):
    vout[j] = 2.0 * vtemp2[j] + v[j]

  return vout


# 
def axnorm(ax):
  '''axis-angle normalization -- unit vector length, corrects negative angles and angles over 2Pi'''
  axout = axnormL(np.require(ax,requirements=['C','A']))
  axout = np.squeeze(axout)
  return axout


@numba.jit(nopython=True,fastmath=nbFastmath,cache=nbcache,parallel=nbParallel)
def axnormL(ax):
  axin,m,n,intype = prepIn(ax)
  axout = np.zeros((n,4),dtype=intype)
  for i in numba.prange(n):
    sign = 1.0 if (axin[i,3] >= eps) else -1.0
    axout[i,3] = sign*axin[i,3]
    sum = 0.0
    for j in range(3):
      axout[i,j] = sign * axin[i,j]
      sum += axout[i,j]*axout[i,j]
    axout[i,3] = np.fmod(axout[i,3],PI2)
    sum = 1.0/(np.sqrt(sum)+1e-35)
    for j in range(3):
      axout[i,j] *= sum
    if axout[i,3] > (PI+1e-6):
      for j in range(3):
        axout[i,j] *= -1.0
      axout[i,3] = PI2 - axout[i,3]
  return axout
