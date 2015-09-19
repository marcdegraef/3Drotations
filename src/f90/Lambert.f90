! ###################################################################
! Copyright (c) 2013-2015, Marc De Graef/Carnegie Mellon University
! All rights reserved.
!
! Redistribution and use in source and binary forms, with or without modification, are 
! permitted provided that the following conditions are met:
!
!     - Redistributions of source code must retain the above copyright notice, this list 
!        of conditions and the following disclaimer.
!     - Redistributions in binary form must reproduce the above copyright notice, this 
!        list of conditions and the following disclaimer in the documentation and/or 
!        other materials provided with the distribution.
!     - Neither the names of Marc De Graef, Carnegie Mellon University nor the names 
!        of its contributors may be used to endorse or promote products derived from 
!        this software without specific prior written permission.
!
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
! DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
! SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
! CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
! OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
! USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
! ###################################################################

!--------------------------------------------------------------------------
! EMsoft:Lambert.f90
!--------------------------------------------------------------------------
!
! MODULE: Lambert
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief everything that has to do with the modified Lambert projections
!
!> @details This module contains a number of projection functions for the modified 
!> Lambert projection between square lattice and 2D hemisphere, hexagonal lattice
!> and 2D hemisphere, as well as the more complex mapping between a 3D cubic grid
!> and the unit quaternion hemisphere with positive scalar component.  In addition, there 
!> are some other projections, such as the stereographic one.  Each function is named
!> by the projection, the dimensionality of the starting grid, and the forward or inverse
!> character.  For each function, there is also a single precision and a double precision
!> version, but we use the interface formalism to have only a single call.  The Forward
!> mapping is taken to be the one from the simple grid to the curved grid.  Since the module
!> deals with various grids, we also add a few functions/subroutines that apply symmetry
!> operations on those grids.
!>
!> To use any of these routines, one must first call the InitLambertParameters routine
!> to initialize a bunch of constants.
!
!> @date 7/10/13   MDG 1.0 original
!> @date 7/12/13   MDG 1.1 added forward cube to ball to quaternion mappings
!> @date 8/01/13   MDG 1.2 added standard Lambert projection
!> @date 8/12/13   MDG 1.3 added inverse Lambert projections for Ball to Cube
!> @date 9/20/13   MDG 1.4 added ApplyLaueSymmetry
!> @date 08/29/15  MDG 1.5 small changes to hexagonal mapping routines; coordinate swap inside routines
!> @date 09/19/15  MDG 1.6 split off some routines for 3Drotations module
!--------------------------------------------------------------------------
module Lambert

use local
use constants
use quaternions

IMPLICIT NONE

!------------
! public functions and subroutines
!------------

! mappings from the 3D cubic grid to the 3D spherical grid
public :: LambertCubeToBall
interface LambertCubeToBall
        module procedure Lambert3DCubeForwardSingle
        module procedure Lambert3DCubeForwardDouble
end interface

public :: LambertBallToCube
interface LambertBallToCube
        module procedure Lambert3DCubeInverseSingle
        module procedure Lambert3DCubeInverseDouble
end interface

! auxiliary private functions for the cube to sphere mappings
private :: GetPyramidSingle
private :: GetPyramidDouble

contains


!--------------------------------------------------------------------------
! the functions below deal with the cubic grid to the 3D ball, and then from
! the 3D ball to the unit quaternion hemisphere projection
!
! all derivations and equations can be found in 
!
! D. Rosca, A. Morawiec, and M. De Graef. “A new method of constructing a grid 
! in the space of 3D rotations and its applications to texture analysis”. 
! Modeling and Simulations in Materials Science and Engineering 22, 075013 (2014).
!
!--------------------------------------------------------------------------


!--------------------------------------------------------------------------
!
! FUNCTION: Lambert3DCubeForwardSingle
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief map from 3D cubic grid to 3D ball 
!
!> @param xyzin 3D coordinates to be considered (single precision)  
!> @param ierr error flag 0 = OK, 1 = 
! 
!> @date 7/12/13    MDG 1.0 original
!> @date 7/7/14  MDG 2.0 correction to cube edge length check
!--------------------------------------------------------------------------
recursive function Lambert3DCubeForwardSingle(xyzin,ierr) result(res)

IMPLICIT NONE

real(kind=sgl),INTENT(IN)       :: xyzin(3)
integer(kind=irg),INTENT(INOUT):: ierr
real(kind=sgl)                  :: res(3)

real(kind=sgl)                  :: XYZ(3), sXYZ(3), T1, T2, c, s, q, LamXYZ(3)
integer(kind=irg)               :: p

ierr = 0
if (maxval(abs(xyzin)).gt.LPs%ap/2) then
  res = (/ 0.0, 0.0, 0.0 /)
  ierr = 1
  return
end if

! determine which pyramid pair the point lies in and copy coordinates in correct order (see paper)
p = GetPyramidSingle(xyzin)
select case (p)
 case (1,2)
  sXYZ = xyzin
 case (3,4)
  sXYZ = (/ xyzin(2), xyzin(3), xyzin(1) /)
 case (5,6)
  sXYZ = (/ xyzin(3), xyzin(1), xyzin(2) /)
end select

! scale by grid parameter ratio sc
XYZ = LPs%sc * sXYZ

! transform to the sphere grid via the curved square, and intercept the zero point
if (maxval(abs(XYZ)).eq.0.0) then
  LamXYZ = (/ 0.0, 0.0, 0.0 /)
else
! intercept all the points along the z-axis
  if (maxval(abs(XYZ(1:2))).eq.0.0) then
    LamXYZ = (/ 0.0, 0.0, sngl(LPs%pref) * XYZ(3) /)
  else  ! this is a general grid point
    if (abs(XYZ(2)).le.abs(XYZ(1))) then
      q = LPs%pi12 * XYZ(2)/XYZ(1)
      c = cos(q)
      s = sin(q)
      q = LPs%prek * XYZ(1) / sqrt(LPs%r2-c)
      T1 = (LPs%r2*c - 1.0) * q
      T2 = LPs%r2 * s * q
    else
      q = LPs%pi12 * XYZ(1)/XYZ(2)
      c = cos(q)
      s = sin(q)
      q = LPs%prek * XYZ(2) / sqrt(LPs%r2-c)
      T1 = LPs%r2 * s * q
      T2 = (LPs%r2*c - 1.0) * q
    end if

! transform to sphere grid (inverse Lambert)
! [note that there is no need to worry about dividing by zero, since XYZ(3) can not become zero]
    c = T1**2+T2**2
    s = LPs%Pi * c/(24.0*XYZ(3)**2)
    c = LPs%sPi * c / LPs%r24 / XYZ(3)
    q = sqrt( 1.0 - s )
    LamXYZ = (/ T1 * q, T2 * q, sngl(LPs%pref) * XYZ(3) - c /)
  end if
end if

! reverse the coordinates back to the regular order according to the original pyramid number
select case (p)
 case (1,2)
  res = LamXYZ
 case (3,4)
  res = (/ LamXYZ(3), LamXYZ(1), LamXYZ(2) /)
 case (5,6)
  res = (/ LamXYZ(2), LamXYZ(3), LamXYZ(1) /)
end select

end function Lambert3DCubeForwardSingle

!--------------------------------------------------------------------------
!
! FUNCTION: Lambert3DCubeForwardDouble
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief map from 3D cubic grid to 3D ball 
!
!> @param xyzin 3D coordinates to be considered (double precision)  
!> @param ierr error flag 0 = OK, 1 = outside of unit cube
! 
!> @date 7/12/13    MDG 1.0 original
!> @date 7/7/14  MDG 2.0 correction to cube edge length check
!--------------------------------------------------------------------------
recursive function Lambert3DCubeForwardDouble(xyzin,ierr) result(res)

IMPLICIT NONE

real(kind=dbl),INTENT(IN)       :: xyzin(3)
integer(kind=irg),INTENT(INOUT):: ierr
real(kind=dbl)                  :: res(3)

real(kind=dbl)                  :: XYZ(3), sXYZ(3), T1, T2, c, s, q, LamXYZ(3), eps
integer(kind=irg)               :: p

eps = 1.0D-8

ierr = 0
!if (maxval(dabs(xyzin)).gt.LPs%ap/2.D0) then
if (maxval(dabs(xyzin)).gt.(LPs%ap/2.D0+eps)) then
  res = (/ 0.D0, 0.D0, 0.D0 /)
  ierr = 1
  return
end if

! determine which pyramid pair the point lies in and copy coordinates in correct order (see paper)
p = GetPyramidDouble(xyzin)
select case (p)
 case (1,2)
  sXYZ = xyzin
 case (3,4)
  sXYZ = (/ xyzin(2), xyzin(3), xyzin(1) /)
 case (5,6)
  sXYZ = (/ xyzin(3), xyzin(1), xyzin(2) /)
end select

! scale by grid parameter ratio sc
XYZ = LPs%sc * sXYZ

! transform to the sphere grid via the curved square, and intercept the zero point
if (maxval(dabs(XYZ)).eq.0.D0) then
  LamXYZ = (/ 0.D0, 0.D0, 0.D0 /)
else
! intercept all the points along the z-axis
  if (maxval(dabs(XYZ(1:2))).eq.0.D0) then
    LamXYZ = (/ 0.D0, 0.D0, LPs%pref * XYZ(3) /)
  else  ! this is a general grid point
    if (dabs(XYZ(2)).le.dabs(XYZ(1))) then
      q = LPs%pi12 * XYZ(2)/XYZ(1)
      c = dcos(q)
      s = dsin(q)
      q = LPs%prek * XYZ(1) / dsqrt(LPs%r2-c)
      T1 = (LPs%r2*c - 1.D0) * q
      T2 = LPs%r2 * s * q
    else
      q = LPs%pi12 * XYZ(1)/XYZ(2)
      c = dcos(q)
      s = dsin(q)
      q = LPs%prek * XYZ(2) / dsqrt(LPs%r2-c)
      T1 = LPs%r2 * s * q
      T2 = (LPs%r2*c - 1.D0) * q
    end if

! transform to sphere grid (inverse Lambert)
! [note that there is no need to worry about dividing by zero, since XYZ(3) can not become zero]
    c = T1**2+T2**2
    s = LPs%Pi * c/(24.D0*XYZ(3)**2)
    c = LPs%sPi * c / LPs%r24 / XYZ(3)
    q = dsqrt( 1.0 - s )
    LamXYZ = (/ T1 * q, T2 * q, LPs%pref * XYZ(3) - c /)
  end if
end if

! reverse the coordinates back to the regular order according to the original pyramid number
select case (p)
 case (1,2)
  res = LamXYZ
 case (3,4)
  res = (/ LamXYZ(3), LamXYZ(1), LamXYZ(2) /)
 case (5,6)
  res = (/ LamXYZ(2), LamXYZ(3), LamXYZ(1) /)
end select

end function Lambert3DCubeForwardDouble

!--------------------------------------------------------------------------
!
! FUNCTION: Lambert3DCubeInverseSingle
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief map from 3D ball to 3D cubic grid  
!
!> @param xyz 3D coordinates to be considered (single precision)  
!> @param ierr error flag 0 = OK, 1 = 
! 
!> @date 7/12/13    MDG 1.0 original
!> @date 8/12/14    MDG 1.1 fixed acos() problem
!--------------------------------------------------------------------------
recursive function Lambert3DCubeInverseSingle(xyz,ierr) result(res)

IMPLICIT NONE

real(kind=sgl),INTENT(IN)       :: xyz(3)
integer(kind=irg),INTENT(INOUT):: ierr
real(kind=sgl)                  :: res(3)

real(kind=sgl)                  :: rs, xyz3(3), xyz2(3), qxy, q2xy, sq2xy, q, ac, T1inv, T2inv, &
                                   xyz1(3), sx, sy, qx2y, sqx2y, tt
        
integer(kind=irg)               :: p

ierr = 0

rs = sqrt(sum(xyz*xyz))
if (rs.gt.LPs%R1) then 
  res = (/ 0.0,0.0,0.0 /) 
  ierr = 1
  return
end if

if (maxval(abs(xyz)).eq.0.0) then 
  res = (/ 0.0,0.0,0.0 /) 
  return
end if

! determine pyramid
p = GetPyramidSingle(xyz)
select case (p)
 case (1,2)
  xyz3 = xyz
 case (3,4)
  xyz3 = (/ xyz(2), xyz(3), xyz(1) /)
 case (5,6)
  xyz3 = (/ xyz(3), xyz(1), xyz(2) /)
end select

! inverse M_3
q = sqrt( 2.0*rs/(rs+abs(xyz3(3))) )
xyz2 = (/ xyz3(1) * q, xyz3(2) * q, (abs(xyz3(3))/xyz3(3)) * rs / sngl(LPs%pref) /)

! inverse M_2
qxy = xyz2(1)*xyz2(1)+xyz2(2)*xyz2(2)
sx = 1.0
if (xyz2(1).ne.0.0)  sx = abs(xyz2(1))/xyz2(1) 
sy = 1.0
if (xyz2(2).ne.0.0)  sy = abs(xyz2(2))/xyz2(2)

if (qxy.ne.0.0) then 
 if (abs(xyz2(2)).le.abs(xyz2(1))) then 
  q2xy = qxy + xyz2(1)*xyz2(1)
  sq2xy = sqrt(q2xy)
  q = (LPs%beta/LPs%r2/LPs%R1) * sqrt(q2xy*qxy/(q2xy-abs(xyz2(1))*sq2xy))
  tt = (xyz2(2)*xyz2(2)+abs(xyz2(1))*sq2xy)/LPs%r2/qxy 
  if (tt.gt.1.0) tt = 1.0
  if (tt.lt.-1.0) tt = -1.0
  ac = acos(tt)
  T1inv = q * sx
  T2inv = q * sy * ac/LPs%pi12
 else 
  qx2y = qxy + xyz2(2)*xyz2(2)
  sqx2y = sqrt(qx2y)
  q = (LPs%beta/LPs%r2/LPs%R1) * sqrt(qx2y*qxy/(qx2y-abs(xyz2(2))*sqx2y))
  tt = (xyz2(1)*xyz2(1)+abs(xyz2(2))*sqx2y)/LPs%r2/qxy 
  if (tt.gt.1.0) tt = 1.0
  if (tt.lt.-1.0) tt = -1.0
  ac = acos(tt)
  T1inv = q * sx * ac/LPs%pi12
  T2inv = q * sy
 end if
else
 T1inv = 0.0
 T2inv = 0.0
end if

xyz1 = (/ T1inv, T2inv, xyz2(3) /)

! inverse M_1
xyz1 = xyz1 / LPs%sc

! reverst the coordinates back to the regular order according to the original pyramid number
select case (p)
 case (1,2)
  res = xyz1
 case (3,4)
  res = (/ xyz1(3), xyz1(1), xyz1(2) /)
 case (5,6)
  res = (/ xyz1(2), xyz1(3), xyz1(1) /)
end select

end function Lambert3DCubeInverseSingle

!--------------------------------------------------------------------------
!
! FUNCTION: Lambert3DCubeInverseDouble
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief map from 3D ball to 3D cubic grid  
!
!> @param xyz 3D coordinates to be considered (double precision)  
!> @param ierr error flag 0 = OK, 1 = 
! 
!> @date 7/12/13    MDG 1.0 original
!> @date 8/12/14    MDG 1.1 fixed dacos() problem
!--------------------------------------------------------------------------
recursive function Lambert3DCubeInverseDouble(xyz,ierr) result(res)

IMPLICIT NONE

real(kind=dbl),INTENT(IN)       :: xyz(3)
integer(kind=irg),INTENT(INOUT):: ierr
real(kind=dbl)                  :: res(3)

real(kind=dbl)                  :: rs, xyz3(3), xyz2(3), qxy, q2xy, sq2xy, q, ac, T1inv, T2inv, &
                                   xyz1(3), sx, sy, qx2y, sqx2y, tt
integer(kind=irg)               :: p

ierr = 0

rs = dsqrt(sum(xyz*xyz))
if (rs.gt.LPs%R1) then 
  res = (/ 0.D0,0.D0,0.D0 /) 
  ierr = 1
  return
end if

if (maxval(dabs(xyz)).eq.0.D0) then 
  res = (/ 0.D0,0.D0,0.D0 /) 
  return
end if

! determine pyramid
p = GetPyramidDouble(xyz)
select case (p)
 case (1,2)
  xyz3 = xyz
 case (3,4)
  xyz3 = (/ xyz(2), xyz(3), xyz(1) /)
 case (5,6)
  xyz3 = (/ xyz(3), xyz(1), xyz(2) /)
end select

! inverse M_3
q = dsqrt( 2.D0*rs/(rs+dabs(xyz3(3))) )
xyz2 = (/ xyz3(1) * q, xyz3(2) * q, (dabs(xyz3(3))/xyz3(3)) * rs / LPs%pref /)

! inverse M_2
qxy = xyz2(1)*xyz2(1)+xyz2(2)*xyz2(2)
sx = 1.D0
if (xyz2(1).ne.0.D0)  sx = dabs(xyz2(1))/xyz2(1) 
sy = 1.D0
if (xyz2(2).ne.0.D0)  sy = dabs(xyz2(2))/xyz2(2)

if (qxy.ne.0.D0) then
 if (dabs(xyz2(2)).le.dabs(xyz2(1))) then 
  q2xy = qxy + xyz2(1)*xyz2(1)
  sq2xy = dsqrt(q2xy)
  q = (LPs%beta/LPs%r2/LPs%R1) * dsqrt(q2xy*qxy/(q2xy-dabs(xyz2(1))*sq2xy))
  tt = (xyz2(2)*xyz2(2)+dabs(xyz2(1))*sq2xy)/LPs%r2/qxy 
  if (tt.gt.1.D0) tt = 1.D0
  if (tt.lt.-1.D0) tt = -1.D0
  ac = dacos(tt)
  T1inv = q * sx
  T2inv = q * sy * ac/LPs%pi12
 else 
  qx2y = qxy + xyz2(2)*xyz2(2)
  sqx2y = dsqrt(qx2y)
  q = (LPs%beta/LPs%r2/LPs%R1) * dsqrt(qx2y*qxy/(qx2y-dabs(xyz2(2))*sqx2y))
  tt = (xyz2(1)*xyz2(1)+dabs(xyz2(2))*sqx2y)/LPs%r2/qxy 
  if (tt.gt.1.D0) tt = 1.D0
  if (tt.lt.-1.D0) tt = -1.D0
  ac = dacos(tt)
  T1inv = q * sx * ac/LPs%pi12
  T2inv = q * sy
 end if
else
  T1inv = 0.D0
  T2inv = 0.D0
end if
xyz1 = (/ T1inv, T2inv, xyz2(3) /)

! inverse M_1
xyz1 = xyz1 / LPs%sc

! reverst the coordinates back to the regular order according to the original pyramid number
select case (p)
 case (1,2)
  res = xyz1
 case (3,4)
  res = (/ xyz1(3), xyz1(1), xyz1(2) /)
 case (5,6)
  res = (/ xyz1(2), xyz1(3), xyz1(1) /)
end select

end function Lambert3DCubeInverseDouble


!--------------------------------------------------------------------------
!
! FUNCTION: GetPyramidSingle
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief determine to which pyramid a point in a cubic grid belongs
!
!> @param xyz 3D coordinates to be considered (single precision)  
! 
!> @date 11/21/12    MDG 1.0 original
!--------------------------------------------------------------------------
recursive function GetPyramidSingle(xyz) result(res)

IMPLICIT NONE

real(kind=sgl),INTENT(IN)       :: xyz(3) 
integer(kind=irg)               :: res, p

logical                         :: next

next = .TRUE.
if ((abs(xyz(1)).le.xyz(3)).and.(abs(xyz(2)).le.xyz(3))) then
  p = 1                         ! pyramid 1
  next = .FALSE.
end if  
if (next) then 
 if ((abs(xyz(1)).le.-xyz(3)).and.(abs(xyz(2)).le.-xyz(3))) then
  p = 2                         ! pyramid 2
  next = .FALSE.
 end if   
end if

if (next) then
 if ((abs(xyz(3)).le.xyz(1)).and.(abs(xyz(2)).le.xyz(1))) then
  p = 3                         ! pyramid 3
  next = .FALSE.
 end if  
end if
if (next) then
 if ((abs(xyz(3)).le.-xyz(1)).and.(abs(xyz(2)).le.-xyz(1))) then
  p = 4                         ! pyramid 4
  next = .FALSE.
 end if  
end if

if (next) then
 if ((abs(xyz(1)).le.xyz(2)).and.(abs(xyz(3)).le.xyz(2))) then
  p = 5                         ! pyramid 5
  next = .FALSE.
 end if  
end if
if (next) then
 if ((abs(xyz(1)).le.-xyz(2)).and.(abs(xyz(3)).le.-xyz(2))) then
  p = 6                         ! pyramid 6
  next = .FALSE.
 end if  
end if
res = p

end function GetPyramidSingle

!--------------------------------------------------------------------------
!
! FUNCTION: GetPyramidDouble
!
!> @author Marc De Graef, Carnegie Mellon University
!
!> @brief determine to which pyramid a point in a cubic grid belongs
!
!> @param xyz 3D coordinates to be considered (double precision)  
! 
!> @date 11/21/12    MDG 1.0 original
!--------------------------------------------------------------------------
recursive function GetPyramidDouble(xyz) result(res)

IMPLICIT NONE

real(kind=dbl),INTENT(IN)       :: xyz(3) 
integer(kind=irg)               :: res, p

logical                         :: next

next = .TRUE.
if ((dabs(xyz(1)).le.xyz(3)).and.(dabs(xyz(2)).le.xyz(3))) then
  p = 1                         ! pyramid 1
  next = .FALSE.
end if  
if (next) then
 if ((dabs(xyz(1)).le.-xyz(3)).and.(dabs(xyz(2)).le.-xyz(3))) then
  p = 2                         ! pyramid 2
  next = .FALSE.
 end if   
end if

if (next) then
 if ((dabs(xyz(3)).le.xyz(1)).and.(dabs(xyz(2)).le.xyz(1))) then
  p = 3                         ! pyramid 3
  next = .FALSE.
 end if 
end if 
if (next) then
 if ((dabs(xyz(3)).le.-xyz(1)).and.(dabs(xyz(2)).le.-xyz(1))) then
  p = 4                         ! pyramid 4
  next = .FALSE.
 end if  
end if

if (next) then
 if ((dabs(xyz(1)).le.xyz(2)).and.(dabs(xyz(3)).le.xyz(2))) then
  p = 5                         ! pyramid 5
  next = .FALSE.
 end if  
end if
if (next) then
 if ((dabs(xyz(1)).le.-xyz(2)).and.(dabs(xyz(3)).le.-xyz(2))) then
  p = 6                         ! pyramid 6
  next = .FALSE.
 end if  
end if

res = p

end function GetPyramidDouble




end module Lambert
