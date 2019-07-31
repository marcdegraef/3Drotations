/*
 *  cquat.c
 *  cquat_multiply
 *
 *  Created by dave on 3/30/11.
 *  Copyright 2011 Naval Research Lab. All rights reserved.
 *
 */



#include "quatLibIDLWrap.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "idl_export.h"
#include "quatlib.h"

#ifdef _OPENMP
    #include <omp.h>
    #define OPENMPLIMIT 10000000l
#endif


/* #########################################################################################################################
This is a set of functions for linking the quaternion multiplication.  It includes reading in the arguements from 
IDL, casting the argc, *argv[] to their proper types. It then sends the arrays off to the proper loops, either using double 
or float.  In the case of float, each quaternion is temporarily cast to a doulbe, the multiplication occurs in double
then the result is cast back to a float.   

Everything is mutithreaded with openMP.  

#########################################################################################################################*/

int quatMultLoop ( double* q1, double* q2 ,double* q1q2, unsigned long long nq1, unsigned long long nq2, int p){
	unsigned long long i, q1step, q2step, q1q2step, nq;
  int trash;

	/*
	 A function that multiplies two quaterions (or many quaterions)
	 openmp is used to multi-thread the operation
	 */

q1q2step = 4;
q1step = (nq1 == 1) ? 0 : 4;
q2step = (nq2 == 1) ? 0 : 4;

if ((nq1 > 1) && (nq2 > 1)){
  nq = (nq1 <= nq2) ? nq1 : nq2;
} else {
  nq = (nq1 >= nq2) ? nq1 : nq2;
}


#ifdef _OPENMP
	if (nq >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
  //omp_set_num_threads(1)
#endif

#pragma omp parallel shared(q1, q2, q1q2) private(i, trash) firstprivate(q1step, q2step, q1q2step, nq, p) 
  {
#pragma omp for schedule (static) nowait 
	  for (i = 0;i < nq;i++){
      trash = quatMultiply( &(q1[i*q1step]), &(q2[i*q2step]), &(q1q2[i*q1q2step]), p );
	  }
  }	
	return 1;
}


int quatMultLoopf ( float* q1, float* q2 ,float* q1q2, unsigned long long nq1, unsigned long long nq2, int p){
  unsigned long long i,j, q1step, q2step, q1q2step, nq, istep;
  int trash;
  double q1temp[4], q2temp[4], q1q2temp[4]; 

  /*
   A function that multiplies two quaterions (or many quaterions)
   openmp is used to multi-thread the operation
   */

q1q2step = 4;
q1step = (nq1 == 1) ? 0 : 4;
q2step = (nq2 == 1) ? 0 : 4;

if ((nq1 > 1) && (nq2 > 1)){
  nq = (nq1 <= nq2) ? nq1 : nq2;
} else {
  nq = (nq1 >= nq2) ? nq1 : nq2;
}


#ifdef _OPENMP
  if (nq >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
  //omp_set_num_threads(1)
#endif

if ((nq1 == 1) && (nq > 1)) {
  #pragma omp parallel shared(q1, q2, q1q2) private(i,j, trash, q1temp, q2temp, q1q2temp) \
    firstprivate(q1step, q2step, q1q2step, nq, p) 
  {
  
  for (j=0; j<4; j++) q1temp[j] = (double) q1[j];

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < nq;i++){

      for (j=0; j<4; j++) q2temp[j] = (double) q2[i*q2step+j];   
      trash = quatMultiply( q1temp, q2temp, q1q2temp, p );
      for (j=0;j<4;j++) q1q2[i*q1q2step+j] = (float) q1q2temp[j];
    }
  } 

} else if ((nq2 == 1) && nq > 1) {
  #pragma omp parallel shared(q1, q2, q1q2) private(i,j, trash, q1temp, q2temp, q1q2temp) \
    firstprivate(q1step, q2step, q1q2step, nq, p) 
  {
  
  for (j=0; j<4; j++) q2temp[j] = (double) q2[j];

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < nq;i++){

      for (j=0; j<4; j++) q1temp[j] = (double) q1[i*q1step+j];   
      trash = quatMultiply( q1temp, q2temp, q1q2temp, p );
      for (j=0;j<4;j++) q1q2[i*q1q2step+j] = (float) q1q2temp[j];
    }
  }
  } else {
    #pragma omp parallel shared(q1, q2, q1q2) private(i,j, trash, q1temp, q2temp, q1q2temp) \
      firstprivate(q1step, q2step, q1q2step, nq, p) 
   {

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < nq;i++){
      for (j=0; j<4; j++){ 
        q2temp[j] = (double) q2[i*q2step+j];
        q1temp[j] = (double) q1[i*q1step+j]; 
        }  
      trash = quatMultiply( q1temp, q2temp, q1q2temp, p );
      for (j=0;j<4;j++) q1q2[i*q1q2step+j] = (float) q1q2temp[j];
    }

    }
  }
  return 1;
}


int quatMultIDLWrap (int argc, void* argv[]) {
	/* Wrapper function for a quaterion mulitplication function for passing to IDL
	 * quaterions are defined with (real, imaginary x y z) notation
	 *
	 * argc must equal 7
	 * argv[0] pointer to q1
	 * argv[1] pointer to q2
	 * argv[2] pointer to q1q2 - output
	 * argv[3] number of quaterions in q1 
   * argv[4] number of quaterions in q2 
   * argv[5] p factor for passive/active switch
   * argv[6] IDL type code for float (4) or double (5).  
	 */
  IDL_ULONG64 *nq1In, *nq2In;
  IDL_LONG *typeIn, *pIn;
  unsigned long long nq1, nq2;
  int type, p;
	
  nq1In = (IDL_ULONG64*) argv[3];
  nq1 = (unsigned long long) (*nq1In);
  nq2In = (IDL_ULONG64*) argv[4];
  nq2 = (unsigned long long) (*nq2In); 

  pIn = (IDL_LONG*) argv[5];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[6];
  type = (int) (*typeIn);


 if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return quatMultLoopf ( (float*) argv[0], (float*) argv[1],(float*) argv[2], nq1, nq2, p);
  } else { // double calculation and storage
    return quatMultLoop ( (double*) argv[0], (double*) argv[1],(double*) argv[2], nq1, nq2, p);
  }

}


/* #########################################################################################################################
This is a set of functions for linking the quaternion vector operator.  It includes reading in the arguements from 
IDL, casting the argc, *argv[] to their proper types. It then sends the arrays off to the proper loops, either using double 
or float.  In the case of float, each quaternion is temporarily cast to a doulbe, the quat/vector operation occurs in double
then the result is cast back to a float.   

Everything is mutithreaded with openMP.  

#########################################################################################################################*/


int quatVectLoop ( double* q, double* v ,double* vout, unsigned long long nq, unsigned long long nv, int p){
  unsigned long long i, qstep, vstep, voutstep, n;
  int trash;

  /*
   A function that multiplies two quaterions (or many quaterions)
   openmp is used to multi-thread the operation
   */

voutstep = 3;
qstep = (nq == 1) ? 0 : 4;
vstep = (nv == 1) ? 0 : 3;

if ((nq > 1) && (nv > 1)){
  n = (nq <= nv) ? nq : nv;
} else {
  n = (nq >= nv) ? nq : nv;
}


#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
  //omp_set_num_threads(1)
#endif

#pragma omp parallel shared(q, v, vout) private(i, trash) firstprivate(qstep, vstep, voutstep, n,p) 
  {
#pragma omp for schedule (static) nowait 
    for (i = 0;i < n;i++){
      trash = quatVector( &(q[i*qstep]), &(v[i*vstep]), &(vout[i*voutstep]), p );
    }
  } 
  return 1;
}


int quatVectLoopf ( float* q, float* v ,float* vout, unsigned long long nq, unsigned long long nv, int p){
  unsigned long long i,j, qstep, vstep, voutstep, n, istep;
  int trash;
  double qtemp[4], vtemp[3], vouttemp[3]; 

  /*
   A function that multiplies two quaterions (or many quaterions)
   openmp is used to multi-thread the operation
   */

voutstep = 3;
qstep = (nq == 1) ? 0 : 4;
vstep = (nv == 1) ? 0 : 3;

if ((nq > 1) && (nv > 1)){
  n = (nq <= nv) ? nq : nv;
} else {
  n = (nq >= nv) ? nq : nv;
}


#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
  //omp_set_num_threads(1)
#endif

if ((nq == 1) && (n > 1)) {
  #pragma omp parallel shared(q, v, vout) private(i,j, trash, qtemp, vtemp, vouttemp) \
    firstprivate(qstep, vstep, voutstep, n, p) 
  {
  
  for (j=0; j<4; j++) qtemp[j] = (double) q[j];

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < n;i++){

      for (j=0; j<3; j++) vtemp[j] = (double) v[i*vstep+j];   
      trash = quatVector( qtemp, vtemp, vouttemp, p );
      for (j=0;j<3;j++) vout[i*voutstep+j] = (float) vouttemp[j];
    }
  } 

} else if ((nv == 1) && n > 1) {
  #pragma omp parallel shared(q, v, vout) private(i,j, trash, qtemp, vtemp, vouttemp) \
    firstprivate(qstep, vstep, voutstep, n, p) 
  {
  
  for (j=0; j<3; j++) vtemp[j] = (double) v[j];

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < n;i++){

      for (j=0; j<4; j++) qtemp[j] = (double) q[i*qstep+j];   
      trash = quatVector( qtemp, vtemp, vouttemp, p );
      for (j=0;j<3;j++) vout[i*voutstep+j] = (float) vouttemp[j];
    }
  }
  } else {
    #pragma omp parallel shared(q, v, vout) private(i,j, trash, qtemp, vtemp, vouttemp) \
      firstprivate(qstep, vstep, voutstep, n, p) 
   {

  #pragma omp for schedule (static) nowait 
    for (i = 0;i < n;i++){
      for (j=0; j<3; j++){ 
        vtemp[j] = (double) v[i*vstep+j];
      }
      for (j=0; j<4; j++){  
        qtemp[j] = (double) q[i*qstep+j]; 
        }  
      trash = quatVector( qtemp, vtemp, vouttemp, p );
      for (j=0;j<3;j++) vout[i*voutstep+j] = (float) vouttemp[j];
    }

    }
  }
  return 1;
}






int quatVectIDLWrap (int argc, void* argv[]) {
  /* Wrapper function for a quaterion mulitplication function for passing to IDL
   * quaterions are defined with (real, imaginary x y z) notation
   *
   * argc must equal 7
   * argv[0] pointer to q
   * argv[1] pointer to v (the vector/s)
   * argv[2] pointer to vout - output
   * argv[3] number of quaterions in q 
   * argv[4] number of vectors in v 
   * argv[5] p factor for passive/active switch
   * argv[6] IDL type code for float (4) or double (5).  
   */
  IDL_ULONG64 *nqIn, *nvIn;
  IDL_LONG *typeIn, *pIn;
  unsigned long long nq, nv;
  int type, p;
  
  nqIn = (IDL_ULONG64*) argv[3];
  nq = (unsigned long long) (*nqIn);
  nvIn = (IDL_ULONG64*) argv[4];
  nv = (unsigned long long) (*nvIn); 

  pIn = (IDL_LONG*) argv[5];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[6];
  type = (int) (*typeIn);


 if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return quatVectLoopf ( (float*) argv[0], (float*) argv[1],(float*) argv[2], nq, nv, p);
  } else { // double calculation and storage
    return quatVectLoop ( (double*) argv[0], (double*) argv[1],(double*) argv[2], nq, nv, p);
  }

}

int quatLibUnload (int argc, void* argv[]) {
  return 1;
}




