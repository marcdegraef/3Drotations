#include "lambertProjectionsFlt.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
static const float M_2PI = (float) (M_PI * 2.0); //define 2*Pi
static const float eps = (float) 1.0e-6; // define a lower floating point precision

struct lambertconstants{ // define a structure to hold all the constants for the 
     // lambert projections
         double   Pi ;   //  pi
         double  iPi ;  //  1/pi
         double  sPi ;  //  sqrt(pi)
         double sPio2; //  sqrt(pi/2)
         double sPi2 ; //  sqrt(pi)/2
         double  srt ;  //  sqrt(3)/2
         double isrt ;//  1/sqrt(3)
         double alpha;//  sqrt(pi)/3^(1/4)
         double  rtt ;  //  sqrt(3)
         double prea ;//  3^(1/4)/sqrt(2pi)
         double preb ; //  3^(1/4)sqrt(2/pi)
         double prec ;//  pi/2sqrt(3)
         double pred ; //  2pi/3
         double pree ; //  3^(-1/4)
         double pref ; //  sqrt(6/pi)
   // the following c the cube to quaternion hemisphere mapping
          double    a;     // pi^(5/6)/6^(1/6)
          double   ap;    // pi^(2/3)
          double   sc;    // a/ap
          double beta;  // pi^(5/6)/6^(1/6)/2
          double   R1;    // (3pi/4)^(1/3)
          double   r2;    // sqrt(2)
          double  r22;   // 1/sqrt(2)
          double pi12;  // pi/12
          double  pi8;   // pi/8
          double prek;  // R1 2^(1/4)/beta
          double  r24;
          double tfit[16]; 
   };

static struct lambertconstants LPs = {
                  3.141592653589793, 
                  0.318309886183791, 
                  1.772453850905516, 
                  1.253314137315500,
                  0.886226925452758, 
                  0.866025403784439, 
                  0.577350269189626, 
                  1.346773687088598,
                  1.732050807568877, 
                  0.525037567904332, 
                  1.050075135808664, 
                  0.906899682117109, 
                  2.094395102393195, 
                  0.759835685651593, 
                  1.381976597885342, 
                  1.925749019958253,
                  2.145029397111025,
                  0.897772786961286,
                  0.962874509979126,
                  1.330670039491469,
                  1.414213562373095,
                  0.707106781186547,
                  0.261799387799149,
                  0.392699081698724,
                  1.643456402972504,
                  4.898979485566356,
                  {1.0000000000018852, -0.5000000002194847,  
                  -0.024999992127593126, - 0.003928701544781374, 
                  -0.0008152701535450438, - 0.0002009500426119712,  
                  -0.00002397986776071756, - 0.00008202868926605841,  
                  +0.00012448715042090092, - 0.0001749114214822577,  
                  +0.0001703481934140054, - 0.00012062065004116828,  
                  +0.000059719705868660826, - 0.00001980756723965647,  
                  +0.000003953714684212874, - 0.00000036555001439719544}
               };


static int GetPyramid(float* xyz){
  int next, p;

  next = 1;

  if ( (fabsf(xyz[0]) < xyz[2] ) && (fabsf(xyz[1]) < xyz[2]) ){
    p = 1;
    next = 0;
  }

  if (next ==1){
    if ( (fabsf(xyz[0]) < -xyz[2] ) && (fabsf(xyz[1]) < -xyz[2]) ){
      p = 2;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabsf(xyz[2]) < xyz[0] ) && (fabsf(xyz[1]) < xyz[0]) ){
      p = 3;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabsf(xyz[2]) < -xyz[0] ) && (fabsf(xyz[1]) < -xyz[0]) ){
      p = 4;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabsf(xyz[0]) < xyz[1] ) && (fabsf(xyz[2]) < xyz[1]) ){
      p = 5;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabsf(xyz[0]) < -xyz[1] ) && (fabsf(xyz[2]) < -xyz[1]) ){
      p = 6;
      next = 0;
    }
  }

return p;
}

int Lambert3DCubeToBallf(float* xyz, float* xyzba){
  float mx, sXYZ[3], absX, absY, x, y, z; 
  float  q, c, s, T1p, T2p, T1, T2;
  int p, i, xyswitch;

  mx = fabsf(xyz[0]);
  for (i=1;i<3;i++){
    if(fabsf(xyz[i]) > fabsf(xyz[i-1])){
      mx = fabsf(xyz[i]);
    }
  }

  if (mx > (LPs.ap/2.0f+eps)){ // vector is out of range, return 0,0,0 and an error
    xyzba[0] = 0.0f;
    xyzba[1] = 0.0f;
    xyzba[2] = 0.0f;
    return 0; 
  }

  p = GetPyramid(xyz);
  if ((p == 1) || (p ==2)) {
    sXYZ[0] = xyz[0];
    sXYZ[1] = xyz[1];
    sXYZ[2] = xyz[2];
  }
  if ((p == 3) || (p ==4)) {
    sXYZ[0] = xyz[1];
    sXYZ[1] = xyz[2];
    sXYZ[2] = xyz[0];

  }
  if ((p == 5) || (p ==6)) {
    sXYZ[0] = xyz[2];
    sXYZ[1] = xyz[0];
    sXYZ[2] = xyz[1];

    
  }

  for (i=0;i<3;i++){
    sXYZ[i] *= LPs.sc;
  }

  if (mx < eps){
    sXYZ[0] = 0.0f;
    sXYZ[1] = 0.0f;
    sXYZ[2] = 0.0f;
  } else {

    absX = fabsf(sXYZ[0]);
    absY = fabsf(sXYZ[1]);

    if ((absX < eps) && (absY < eps)) {
      sXYZ[0] = 0.0f;
      sXYZ[1] = 0.0f;
      sXYZ[2] = LPs.pref * sXYZ[2];


    } else {

      z = sXYZ[2];
      xyswitch = (long) (fabsf(sXYZ[1]) <= fabsf(sXYZ[0]));
      if (xyswitch == 1) {
        x = sXYZ[0];
        y = sXYZ[1];
      } else {
        x = sXYZ[1];
        y = sXYZ[0];
      }
      q = LPs.pi12 * y / x;
      c = cosf(q);
      s = sinf(q); 

      q = LPs.prek * x/ sqrtf(LPs.r2 - c);
      T1p = (LPs.r2 * c - 1.0f) * q;
      T2p = LPs.r2 * s * q;

      if (xyswitch == 1) {
        T1 = T1p;
        T2 = T2p;
      } else {
        T1 = T2p;
        T2 = T1p;
      }

      c = T1*T1 + T2*T2;
      s = M_PI * c / (24.0f * z * z); 

      c = LPs.sPi * c / LPs.r24 / z;
      q = sqrtf(1.0f - s);

      sXYZ[0] = T1 * q;
      sXYZ[1] = T2 * q;
      sXYZ[2] = LPs.pref * z - c; 
      
    }
  }
 // put the points back in the proper order
  if ((p == 1) || (p ==2)) {
    xyzba[0] = sXYZ[0];
    xyzba[1] = sXYZ[1];
    xyzba[2] = sXYZ[2];
  }
  if ((p == 3) || (p ==4)) {
    xyzba[0] = sXYZ[2];
    xyzba[1] = sXYZ[0];
    xyzba[2] = sXYZ[1];
  }
  if ((p == 5) || (p ==6)) {
    xyzba[0] = sXYZ[1];
    xyzba[1] = sXYZ[2];
    xyzba[2] = sXYZ[0];
  }


  return 1;

}

int Lambert3DBallToCubef(float* xyz, float* xyzcu){
  float xyz3[3], xyz2[3], xyz1[3];
  float rs=0.0f, q,sign, qxy;
  float x, y, q2xy, sq2xy, tt, ac, sx, sy;
  float T1inv, T2inv; 
  int i, p, xyswitch;

  for (i=0;i<3;i++){rs += xyz[i]*xyz[i];}

  rs = sqrtf(rs);

  if (rs > (LPs.R1+eps)) { // vector is out of range, return 0,0,0 and an error
    xyzcu[0] = 0.0f;
    xyzcu[1] = 0.0f;
    xyzcu[2] = 0.0f;
    return 0;
  }

  p = GetPyramid(xyz);
  if ((p == 1) || (p == 2)) {
    xyz3[0] = xyz[0];
    xyz3[1] = xyz[1];
    xyz3[2] = xyz[2];
  }
  if ((p == 3) || (p == 4)) {
    xyz3[0] = xyz[1];
    xyz3[1] = xyz[2];
    xyz3[2] = xyz[0];

  }
  if ((p == 5) || (p == 6)) {
    xyz3[0] = xyz[2];
    xyz3[1] = xyz[0];
    xyz3[2] = xyz[1];

    
  }

  q = sqrtf(2.0f * rs/(rs + fabsf(xyz3[2]) + eps));
  xyz2[0] = xyz3[0]*q;
  xyz2[1] = xyz3[1]*q;
  //sign = (float)(xyz3[2] >= 0.0f) - (float)(xyz3[2] < 0.0f);
  sign = ((xyz3[2] >= 0.0) ? 1.0f : -1.0f);
  xyz2[2] = sign * rs/LPs.pref;

  qxy = 0.0f;
  for (i=0;i<2;i++){qxy += xyz2[i]*xyz2[i];}

  
  if (qxy == 0.0f){
    xyz1[0] = 0.0f;
    xyz1[1] = 0.0f;
  } else {
    xyswitch = (long) (fabsf(xyz2[1]) <= fabsf(xyz2[0]));
    if (xyswitch == 1) {
      x = xyz2[0];
      y = xyz2[1];
    } else {
      x = xyz2[1];
      y = xyz2[0];
    }

    q2xy = qxy + x*x;
    sq2xy = sqrtf(q2xy);

    q = (LPs.beta/LPs.r2/LPs.R1) * sqrtf(q2xy * qxy/(q2xy - fabsf(x)*sq2xy));
    tt = (y*y + fabsf(x)*sq2xy) / LPs.r2/qxy;
    if (tt > 1.0f) {tt = 1.0f;}
    if (tt < -1.0f) {tt = -1.0f;}

    ac = acosf(tt);

    sx = (float)(x >= 0.0f) - (float)(x < 0.0f);
    sy = (float)(y >= 0.0f) - (float)(y < 0.0f);

    T1inv = q * sx;
    T2inv = q * sy * ac/LPs.pi12;

    if (xyswitch == 1) {
      xyz1[0] = T1inv;
      xyz1[1] = T2inv;
    } else {
      xyz1[0] = T2inv;
      xyz1[1] = T1inv;
    }
  } 

  xyz1[2] = xyz2[2];
  
  for (i=0;i<3;i++){xyz1[i] *= 1.0f/LPs.sc;}

  // put the points back in the proper order
  if ((p == 1) || (p == 2)) {
    xyzcu[0] = xyz1[0];
    xyzcu[1] = xyz1[1];
    xyzcu[2] = xyz1[2];
  }
  if ((p == 3) || (p == 4)) {
    xyzcu[0] = xyz1[2];
    xyzcu[1] = xyz1[0];
    xyzcu[2] = xyz1[1];
  }
  if ((p == 5) || (p == 6)) {
    xyzcu[0] = xyz1[1];
    xyzcu[1] = xyz1[2];
    xyzcu[2] = xyz1[0];
  }
      

  
return 1;

}



