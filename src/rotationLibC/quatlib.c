#include <stdlib.h>
#include <stdio.h>
#include <math.h>




static int crossp( double *v1, double *v2, double *v1v2){
    v1v2[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v1v2[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v1v2[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return 1;
    
}

int quatMultiply ( double *q1, double *q2, double *q1q2, int p){
  /*
  fundamental quaterion mutiplication
  */
  double sign, epsijk;

  epsijk = (double) p;

  q1q2[0] = q1[0] * q2[0] -
      (q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3]);
  
  q1q2[1] = q1[0] * q2[1] + q2[0] * q1[1] +
      epsijk * (q1[2] * q2[3] - q1[3] * q2[2]);

  q1q2[2] = q1[0] * q2[2] + q2[0] * q1[2] +
      epsijk * (q1[3] * q2[1] - q1[1] * q2[3]);

  q1q2[3] = q1[0] * q2[3] + q2[0] * q1[3] +
      epsijk * (q1[1] * q2[2] - q1[2] * q2[1]);   

  //set it so that every quaterion has a positive first term
  /* decided it would be best to put this in a quat_normalize function  
  sign  = (double) (q1q2[0] >= 0) - (double) (q1q2[0] < 0);    
  for (int i = 0; i < 4; ++i)
  {
    q1q2[i] *= sign;
  }
  */

  return 1; 
}





int quatVector( double  *q1, double *v, double *q1v, int p){
    int j, trash;
    double vtemp[3], temp[3], r[3], w, temp2[3], epsijk;

    epsijk = (double) p;
    /* 
     A fundamental quaterion vector multiplication
     */
           
     w    = q1[0];
     r[0] = epsijk * q1[1];
     r[1] = epsijk * q1[2];
     r[2] = epsijk * q1[3];
     
     for (j=0; j<3; j++) {
         vtemp[j] = v[j];
     }
     
     trash = crossp( r, vtemp, temp );
     
     for (j=0; j<3; j++) {
         temp[j] += w * vtemp[j];
     }
     
     trash = crossp( r, temp, temp2 );
     
     for (j=0; j<3; j++) {
         q1v[j] = 2.0*temp2[j]+vtemp[j];
     }
    
    return 1;
}


int quatInverse ( double *q, double *qout){
  int i; 
  /* 
   A function that provides the inverse of a quaternion
   */

   qout[0] = q[0];
   for ( i = 1; i < 4; ++i)
   {
     qout[i] = -1.0*q[i]+0.0;
   }
  
  return 1;
}


int quatNormalize (double *q, double *qout){
  // a function that normalizes the quaternion to length one, and makes sure it is in 
  // the positive hemisphere. 

  double mag=0.0, sign, eps = 1.e-12;
  int i;

  //sign = (double)(q[0] >= 0.0) - (double)(q[0] < 0.0);
  sign = ((q[0] >= 0.0) ? 1.0 : -1.0);
  for ( i = 0; i < 4; ++i)
   {
     mag += q[i]*q[i];
     qout[i] = q[i];
   }

   mag = sign/sqrt(mag+eps);

   for ( i = 0; i < 4; ++i)
   {
     qout[i] *= mag;
   }


}



