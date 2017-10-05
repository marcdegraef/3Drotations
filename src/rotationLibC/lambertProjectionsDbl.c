#include "lambertProjectionsDbl.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
static const double M_2PI = (double) (M_PI * 2.0); //define 2*Pi
static const double eps = (double) 1.0e-12; // define a lower doubleing point precision

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


static int GetPyramid(double* xyz){
  int next, p;

  next = 1;

  if ( (fabs(xyz[0]) < xyz[2] ) && (fabs(xyz[1]) < xyz[2]) ){
    p = 1;
    next = 0;
  }

  if (next ==1){
    if ( (fabs(xyz[0]) < -xyz[2] ) && (fabs(xyz[1]) < -xyz[2]) ){
      p = 2;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabs(xyz[2]) < xyz[0] ) && (fabs(xyz[1]) < xyz[0]) ){
      p = 3;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabs(xyz[2]) < -xyz[0] ) && (fabs(xyz[1]) < -xyz[0]) ){
      p = 4;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabs(xyz[0]) < xyz[1] ) && (fabs(xyz[2]) < xyz[1]) ){
      p = 5;
      next = 0;
    }
  }

  if (next ==1){
    if ( (fabs(xyz[0]) < -xyz[1] ) && (fabs(xyz[2]) < -xyz[1]) ){
      p = 6;
      next = 0;
    }
  }

return p;
}

int Lambert3DCubeToBall(double* xyz, double* xyzba){
  double mx, sXYZ[3], absX, absY, x, y, z; 
  double  q, c, s, T1p, T2p, T1, T2;
  int p, i, xyswitch;

  mx = fabs(xyz[0]);
  for (i=1;i<3;i++){
    if(fabs(xyz[i]) > fabs(xyz[i-1])){
      mx = fabs(xyz[i]);
    }
  }

  if (mx > (LPs.ap/2.0+eps)){ // vector is out of range, return 0,0,0 and an error
    xyzba[0] = 0.0;
    xyzba[1] = 0.0;
    xyzba[2] = 0.0;
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
    sXYZ[0] = 0.0;
    sXYZ[1] = 0.0;
    sXYZ[2] = 0.0;
  } else {

    absX = fabs(sXYZ[0]);
    absY = fabs(sXYZ[1]);

    if ((absX < eps) && (absY < eps)) {
      sXYZ[0] = 0.0;
      sXYZ[1] = 0.0;
      sXYZ[2] = LPs.pref * sXYZ[2];


    } else {

      z = sXYZ[2];
      xyswitch = (long) (fabs(sXYZ[1]) <= fabs(sXYZ[0]));
      if (xyswitch == 1) {
        x = sXYZ[0];
        y = sXYZ[1];
      } else {
        x = sXYZ[1];
        y = sXYZ[0];
      }
      q = LPs.pi12 * y / x;
      c = cos(q);
      s = sin(q); 

      q = LPs.prek * x/ sqrt(LPs.r2 - c);
      T1p = (LPs.r2 * c - 1.0) * q;
      T2p = LPs.r2 * s * q;

      if (xyswitch == 1) {
        T1 = T1p;
        T2 = T2p;
      } else {
        T1 = T2p;
        T2 = T1p;
      }

      c = T1*T1 + T2*T2;
      s = M_PI * c / (24.0 * z * z); 

      c = LPs.sPi * c / LPs.r24 / z;
      q = sqrt(1.0 - s);

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

int Lambert3DBallToCube(double* xyz, double* xyzcu){
  double xyz3[3], xyz2[3], xyz1[3];
  double rs=0.0, q,sign, qxy;
  double x, y, q2xy, sq2xy, tt, ac, sx, sy;
  double T1inv, T2inv; 
  int i, p, xyswitch;

  for (i=0;i<3;i++){rs += xyz[i]*xyz[i];}

  rs = sqrt(rs);

  if (rs > (LPs.R1+eps)) { // vector is out of range, return 0,0,0 and an error
    xyzcu[0] = 0.0;
    xyzcu[1] = 0.0;
    xyzcu[2] = 0.0;
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

  q = sqrt(2.0 * rs/(rs + fabs(xyz3[2]) + eps));
  xyz2[0] = xyz3[0]*q;
  xyz2[1] = xyz3[1]*q;
  //sign = (double)(xyz3[2] >= 0.0) - (double)(xyz3[2] < 0.0);
  sign = ((xyz3[2] >= 0.0) ? 1.0 : -1.0);
  xyz2[2] = sign * rs/LPs.pref;

  qxy = 0.0;
  for (i=0;i<2;i++){qxy += xyz2[i]*xyz2[i];}

  
  if (qxy == 0.0){
    xyz1[0] = 0.0;
    xyz1[1] = 0.0;
  } else {
    xyswitch = (long) (fabs(xyz2[1]) <= fabs(xyz2[0]));
    if (xyswitch == 1) {
      x = xyz2[0];
      y = xyz2[1];
    } else {
      x = xyz2[1];
      y = xyz2[0];
    }

    q2xy = qxy + x*x;
    sq2xy = sqrt(q2xy);

    q = (LPs.beta/LPs.r2/LPs.R1) * sqrt(q2xy * qxy/(q2xy - fabs(x)*sq2xy));
    tt = (y*y + fabs(x)*sq2xy) / LPs.r2/qxy;
    if (tt > 1.0) {tt = 1.0;}
    if (tt < -1.0) {tt = -1.0;}

    ac = acos(tt);

    sx = (double)(x >= 0.0) - (double)(x < 0.0);
    sy = (double)(y >= 0.0) - (double)(y < 0.0);

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
  
  for (i=0;i<3;i++){xyz1[i] *= 1.0/LPs.sc;}

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



