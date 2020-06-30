import numpy as np
from timeit import default_timer as timer
from rotlib import *
#from rotations import *
from rotlib import quatnorm, quatconj, quat_multiply

pi = np.pi
RADDEG = 180.0/pi
# I had some issues with the periodic boundaries in cubochoric/homochoric/quaternion spaces, so I am using
# quaternion misorientation to evaluate the error.

def testrotlib(float32=False, return_quat=False, seed = 1):
  n = np.int(1e6)
  np.random.seed(seed)
  qu = (np.random.random((n,4))*2.0-1)
  if float32 is True:
    qu = qu.astype(np.float32)
  qu = quatnorm(qu)
  qu[0, :] = np.array([1.0, 0.0, 0.0, 0.0])
  qu[1, :] = np.array([0.0,0.0,0.0,-1.0])
  qu[2, :] = np.array([0.0,  0.4264014489670335 , -0.6396021436482270, -0.6396021436482270])

  totaltime = 0.0
  print( "qu2: ")
  tic = timer()
  qu1 = ax2qu(qu2ax(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ax: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = cu2qu(qu2cu(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    cu: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ho2qu(qu2ho(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ho: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = om2qu(qu2om(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    om: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = eu2qu(qu2eu(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    eu: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ro2qu(qu2ro(qu))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ", str(mx.max()), str(mx.mean()) )
  print("        Time to execute: ", t1)

  eu = qu2eu(qu)
  print("eu2: ")
  tic = timer()
  qu1 = eu2qu(ax2eu(eu2ax(eu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ax: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = eu2qu(cu2eu(eu2cu(eu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    cu: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = eu2qu(ho2eu(eu2ho(eu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ho: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = eu2qu(om2eu(eu2om(eu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    om: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = eu2qu(ro2eu(eu2ro(eu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)

  ax = qu2ax(qu)
  print("ax2: ")
  tic = timer()
  qu1 = ax2qu(cu2ax(ax2cu(ax)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    cu: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ax2qu(ho2ax(ax2ho(ax)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ho: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ax2qu(om2ax(ax2om(ax)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    om: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ax2qu(ro2ax(ax2ro(ax)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)

  cu = qu2cu(qu)
  print("cu2: ")
  tic = timer()
  qu1 = cu2qu(ho2cu(cu2ho(cu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ho: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = cu2qu(om2cu(cu2om(cu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    om: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = cu2qu(ro2cu(cu2ro(cu)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)

  ho = qu2ho(qu)
  print("ho2: ")
  tic = timer()
  qu1 = ho2qu(om2ho(ho2om(ho)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    om: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)  
  tic = timer()
  qu1 = ho2qu(ro2ho(ho2ro(ho)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)

  om = qu2om(qu)
  print("om2: ")
  tic = timer()
  qu1 = om2qu(ro2om(om2ro(om)))
  t1 = timer() - tic
  totaltime += t1
  mx = np.arccos(quatnorm(quat_multiply(qu,quatconj(qu1)))[:,0]) * 2*RADDEG
  print("    ro: ",str(mx.max()), str(mx.mean()))
  print("        Time to execute: ", t1)

  print("Total execution time:", totaltime)

  if return_quat is True:
    return qu
