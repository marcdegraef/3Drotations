#include "rotationLibCFloat.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lambertProjectionsFlt.h"

static const float M_2PI = (float) (M_PI * 2.0); //define 2*Pi
static const float eps = (float) 1.0e-6; // define a lower floating point precision

int eu2omf (float* eu, float* om, int p){
  float c1, c2, c3, s1, s2, s3;
  int i;
  float omTemp[9];
  float epsijk;
  
  epsijk = (float) p;

  c1 = cosf(eu[0]);
  c2 = cosf(eu[1]);
  c3 = cosf(eu[2]);
  s1 = sinf(eu[0]);
  s2 = sinf(eu[1]);
  s3 = sinf(eu[2]);

  *(omTemp)    = c1*c3 - s1*s3*c2;// omTemp[0][0]
  *(omTemp +1) = s1*c3+c1*s3*c2;  // omTemp[0][1]
  *(omTemp +2) = s3*s2;           //omTemp[0][2]
  *(omTemp +3) = -c1*s3-s1*c3*c2; //omTemp[1][0]
  *(omTemp +4) = -s1*s3+c1*c3*c2; //omTemp[1][1]
  *(omTemp +5)= c3*s2;            //omTemp[1][2]
  *(omTemp +6)= s1*s2;            //omTemp[2][0]
  *(omTemp +7)= -c1*s2;           //omTemp[2][1]
  *(omTemp +8)= c2 ;              //omTemp[2][2]

  for (i=0; i < 9; i++){
    om[i] =  omTemp[i];
  }

  return 1;
}

int eu2axf (float* eu, float* ax, int p){
  float t, sig, ssig, del, tau, alpha;
  int i;
  float epsijk;
  
  epsijk = (float) p;

  t = tanf(eu[1] * 0.50f);
  sig = 0.50f*(eu[0]+eu[2]);
  ssig = sinf(sig);
  del = 0.50f*(eu[0]-eu[2]);
  tau =  sqrtf(t*t+ssig*ssig);

  if (sig == (float) M_PI_2) {
    alpha = (float) M_PI;
  } else {
    alpha = 2.0f * atanf(tau/cosf(sig));
  }

  if (fabsf(alpha) < eps ) {
    ax[0] = 0.0f;
    ax[1] = 0.0f;
    ax[2] = -1.0f*epsijk;
    ax[3] = 0.0f;
  } else {
    ax[0] = -1.0f * epsijk * t * cosf(del) / tau;
    ax[1] = -1.0f * epsijk * t * sinf(del) / tau;
    ax[2] = -1.0f * epsijk * ssig / tau;
    ax[3] = alpha;
  }

  if (alpha < 0.0f) {
    for (i = 0;i < 4;i++){ ax[i] *= -1.0f; }
  }

  return 1;
}




int eu2quf ( float* eu, float* q, int p){
  float phi1, phi, phi2, dphi1phi2,sphi1phi2, cphi, sphi, sign=0.0f;
  float epsijk;
  epsijk = (float) p; 
  /* 
   A function that converts a set of bunge euler angles 
   to a quaternion to bunge euler angles 
   */

  phi1 = eu[0]/2.0f;
  phi =  eu[1]/2.0f;  
  phi2 = eu[2]/2.0f;
  
  dphi1phi2 = phi1-phi2;
  sphi1phi2 = phi1+phi2;
  cphi = cosf(phi);
  sphi = -1.0f*sinf(phi);
  
  q[0] = cphi*cosf(sphi1phi2)+0.0f;
  //sign = (float) (q[0] >= 0.0f) - (float) (q[0] < 0.0f);
  sign = ((q[0] >= 0.0) ? 1.0f : -1.0f);
  q[0] *= sign;
  q[1] = epsijk*sign * sphi*cosf(dphi1phi2)+0.0f;
  q[2] = epsijk*sign * sphi*sinf(dphi1phi2)+0.0f;
  q[3] = -1.0f*epsijk*sign*cphi*sinf(sphi1phi2)+0.0f;
  
  return 1;
}

int om2euf (float* om, float* eu, int p){
  float zeta;
  float epsijk;
  epsijk = (float) p;

  if (fabsf(fabsf(om[8])-1.0f) > eps){
    eu[1] = acosf(om[8]);
    zeta = 1.0f/(sqrtf(1.0f - om[8]*om[8]));
    eu[0] = atan2f(om[6] * zeta, -1.0f*om[7]*zeta);
    eu[2] = atan2f(om[2] * zeta, om[5]*zeta);
  } else {
    if (fabsf(om[8] - 1.0f) < eps) {
      eu[0] = atan2f(om[1], om[0]);
      eu[1] = 0.0f;
      eu[2] = 0.0f;
    } else {
      eu[0] = -atan2f(om[1], om[0]);
      eu[1] = (float) M_PI;
      eu[2] = 0.0f; 
    }
  }

  eu[0] += 10.0f*M_2PI;
  eu[0] = fmodf(eu[0], M_2PI);
  eu[2] += 10.0f*M_2PI;
  eu[2] = fmodf(eu[2], M_2PI);
  return 1; 
}

int ax2omf (float* ax, float* om, int p){
  float c, s, omc, q, om_temp[9];
  int i,j;
  float epsijk;
  epsijk = (float) p;

  c = cosf(ax[3]);
  s = sinf(ax[3]);
  omc = 1.0f - c;

  for (i=0;i<3;i++){
    *(om + i +3*i) = ax[i]*ax[i]*omc + c;
  }
  q = omc*ax[0]*ax[1];
  *(om+3) = q + s*ax[2]; // om[1][0]
  *(om+1) = q - s*ax[2]; // om[0][1]
  
  q = omc*ax[1]*ax[2];
  *(om+7) = q + s*ax[0]; //om[2][1]
  *(om+5) = q - s*ax[0]; //om[1][2]

  q = omc*ax[2]*ax[0];
  *(om+2) = q + s*ax[1]; //om[0][2]
  *(om+6) = q - s*ax[1]; //om[2][0]

  if (p < 0) { //tranpose the array if p = -1
    for (i=0; i<9; i++){om_temp[i] = om[i];}
    for (i=0;i<3;i++){
      for (j=0; j<3; j++){
        om[i+3*j] = om_temp[3*i+j];
      }
    }
  }

  return 1;
}


int qu2euf (float* q, float* eu, int p ){
  float  q03, q12, chi, q0, sum, diff;
  float epsijk;
  epsijk = (float) p;
  
  q0 = epsijk * q[0];
  q03 = q0*q0 + q[3]*q[3];
  q12 = q[1]*q[1] + q[2]*q[2];
  chi = sqrtf(q03*q12);

  if (chi == 0.0f) {
    if (q12 == 0.0f) {
      eu[2] = 0.0f;
      eu[1] = 0.0f;
      eu[0] = atan2f(-2.0f * q0*q[3], q0*q0 - q[3]*q[3]);
    } else {
      eu[2] = 0.0f;
      eu[1] = (float) M_PI;
      eu[0] = atan2f( 2.0f * q[1]*q[2], q[1]*q[1] - q[2]*q[2]);
    }
  } else {
    eu[1] = atan2f(2.0f * chi, q03 - q12);
    //chi = 1.0f / chi;
    diff = atan2f(-q[2], -q[1] );
    sum  = atan2f(-q[3], q0);
    eu[0] = diff + sum; 
    eu[2] = sum - diff;
  }

  eu[0] += M_2PI;
  eu[0] = fmodf(eu[0], M_2PI);
  eu[2] += M_2PI;
  eu[2] = fmodf(eu[2], M_2PI);

  return 1; 
}

int ax2hof (float* ax, float* ho, int p){
  float f;
  int i;
  float epsijk;
  epsijk = (float) p;

  f = 0.75f * (ax[3] - sinf(ax[3]));
  f = powf(f, 1.0f/3.0f);

  for (i=0; i<3; i++){
    ho[i] = f * ax[i];
  }
  return 1;
}

int ho2axf (float* h, float* ax, int p){
  float hmag =0.0f, hm, sqrthm, hn[3], s;
  static const float tfit[16] =  {1.0000000000018852, -0.5000000002194847,  
               -0.024999992127593126, - 0.003928701544781374,  
               -0.0008152701535450438, - 0.0002009500426119712,  
               -0.00002397986776071756, - 0.00008202868926605841,  
               +0.00012448715042090092, - 0.0001749114214822577,  
               +0.0001703481934140054, - 0.00012062065004116828, 
               +0.000059719705868660826, - 0.00001980756723965647,  
               +0.000003953714684212874, - 0.00000036555001439719544 };
  int i;
  float epsijk;
  epsijk = (float) p;

  
  for (i=0; i<3; i++){ hmag += h[i]*h[i]; }

  if (hmag < eps) {
    ax[0] = 0.0f;
    ax[1] = 0.0f;
    ax[2] = 1.0f;
    ax[3] = 0.0f;
  } else {
    hm = hmag;
    sqrthm = sqrtf(hm);
    for (i=0; i<3; i++){ hn[i] = h[i]/sqrthm; }

    s = tfit[0] + tfit[1] * hmag;
    for (i=2; i<16; i++){
      hm *= hmag;
      s += tfit[i] * hm;  
    }
  
  if (s >  1.0f) { s =  1.0f; }
  if (s < -1.0f) { s = -1.0f; }

  s = 2.0f * acosf(s);
  for (i=0; i<3; i++){ ax[i] = hn[i]; }
  if (fabsf(s - (float) M_PI) < eps) {
    ax[3] = M_PI;
  } else {
    ax[3] = s;
  }

  }

  

  return 1;
}


// need a comparator function for sorting. 
// An array of pointers to the values should be input

static int cmpFunc(const void *v1, const void *v2){
  double i1 = **(const double **)v1; //dereference the pointer to a pointer 
  double i2 = **(const double **)v2;
  if(i1 > i2) return 1;              // first item is bigger than the second one -> return 1
  else
    if(i1 == i2) return  0;         // equality -> return 0
    else         return -1;         // second item is bigger than the first one -> return -1

}

int om2axf (float* om, float* ax, int p){
  float tr, t, mag=0.0f, d[3];  
  float *sortPtr[3];
  int sortIndx[3]; 
  int i;
  float epsijk;
  epsijk = (float) p;

  tr = om[0] + om[4] + om[8];
  t = 0.50f * (tr - 1.0f);
  if (t >  1.0f) { t =  1.0f;}
  if (t < -1.0f) { t = -1.0f;}

  ax[3] = acosf(t);

  if ((1.0f - fabsf(t)) > eps) { // normal case.  
    ax[2] = epsijk * (om[3] - om[1]);
    ax[1] = epsijk * (om[2] - om[6]);
    ax[0] = epsijk * (om[7] - om[5]);
    
    

  } else {// degenerate case, either 0 or Pi rotation.  
    if (t > 0.0f) { // identity rotation.  arbitrarily assign the axis to (001)
      ax[0] = 0.0f;
      ax[1] = 0.0f; 
      ax[2] = 1.0f; 
      ax[3] = 0.0f; 
  
    } else { // 180* rotataion.  Need to find the axis.  
      for (i=0; i<3; i++) {
        d[i] = sqrtf(0.50f*(om[i+3*i]+1.0f));
        sortPtr[i] = &(d[i]);
      }
      // get the index ordering of d
      // first sort the pointers
      qsort(sortPtr, 3, sizeof(sortPtr[0]), cmpFunc );
      // now get the indices in order of largest to smallest.  
      for ( i = 0; i < 3; ++i) {
        sortIndx[i] = (int) (2 - (sortPtr[i] - &(d[0])));
      }

      d[sortIndx[1]] = om[3*sortIndx[0] + sortIndx[1]] / (2.0f * d[sortIndx[0]]);
      d[sortIndx[2]] = om[3*sortIndx[0] + sortIndx[2]] / (2.0f * d[sortIndx[0]]);

      for (i=0; i<3;i++){ ax[i] = d[i];}

    }


  }

  // normalize the axis 
  for (i=0; i<3;i++){
    mag += ax[i]*ax[i];
  }
    
  mag = 1.0f/sqrtf(mag);
  for (i=0; i<3;i++){
    ax[i] *= mag;
  }

  return 1;
}


int ro2axf (float* ro, float* ax, int p){
  float ta, ang;
  int i;
  float epsijk;
  
  epsijk = (float) p;

  ta = ro[3];
  if (ta < eps) {
    ax[0] = 0.0f;
    ax[1] = 0.0f;
    ax[2] = 1.0f;
    ax[3] = 0.0f;
  } else {
    if (ta == INFINITY) {
      ax[0] = ro[0];
      ax[1] = ro[1];
      ax[2] = ro[2];
      ax[3] = (float) M_PI;
    } else {
      ax[3] = 2.0f * atanf(ta);
      ta = 0.0f;
      for (i=0;i<3;i++) {ta += ro[i]*ro[i];}
      ta = 1.0f / sqrtf(ta);
      for (i=0;i<3;i++) {ax[i] = ro[i]*ta;}
    }
  }
  return 1;
}



int ax2rof (float* ax, float* ro, int p){
  int i;
  float epsijk;
  
  epsijk = (float) p;


  if (ax[3] == 0.0f) {
    ro[0] = 0.0f;
    ro[1] = 0.0f;
    ro[2] = -1.0f*epsijk;
    ro[3] = 0.0f;
  } else {
    for (i=0; i<3; ++i) {ro[i] = ax[i];}
    if (fabsf(ax[3] - (float) M_PI) < eps) {
      ro[3] = INFINITY;
    } else {
      ro[3] = tanf(ax[3]*0.50f);
    }
  }
  return 1;
}

int ax2quf (float* ax, float* qu, int p){
  float  s, mag=0.0f;
  int i;
  float epsijk;
  epsijk = (float) p;

  if (ax[3] < eps){
    qu[0] = 1.0f;
    qu[1] = 0.0f;
    qu[2] = 0.0f;
    qu[3] = 0.0f;
  } else {
    qu[0] = cosf(ax[3]*0.50f);
    for (i=0;i<3;i++){mag += ax[i]*ax[i];}

    s = sinf(ax[3]*0.50f)/mag;
    for (i=0;i<3;i++){qu[i+1] = ax[i]*s;}
  
  }


  return 1;
}

int ro2hof (float* ro, float* ho, int p){
  float mag = 0.0f, f, t;
  int i;
  float epsijk;
  epsijk = (float) p;

  mag = ro[3];
  if (mag < eps) {
  
    for (i=0;i<3;i++){ho[i] = 0.0f;} 
  
  } else {
    if (isinf(ro[3])) {
      f = (float) 0.750f * M_PI;
    } else {
      t = 2.0f * atanf(ro[3]);
      f = 0.750f * (t - sinf(t));
    }

    f = powf(f, (1.0f / 3.0f));
  
    for (i=0;i<3;i++){ ho[i] = ro[i]*f;}

  }
  return 1;
}


int qu2omf (float* qu, float* om, int p){
  float sign, qq, qo[4];
  int i;
  float epsijk;
  epsijk = (float) p;

  //sign = (float) (qu[0] >= 0.0f) - (float) (qu[0] < 0.0f);
  sign = ((qu[0] >= 0.0) ? 1.0f : -1.0f);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}
  qo[0] *= epsijk; // easier than trasnposing at the end.  

  qq = qo[0]*qo[0] - (qo[1]*qo[1] + qo[2]*qo[2] + qo[3]*qo[3]);

  *(om)  = qq + 2.0f * qo[1]*qo[1];            // om[0][0]
  *(om+1)= 2.0f * (qo[1]*qo[2] - qo[0]*qo[3]); //  om[0][1]
  *(om+2)= 2.0f * (qo[1]*qo[3] + qo[0]*qo[2]); //  om[0][2]
  *(om+3)= 2.0f * (qo[2]*qo[1] + qo[0]*qo[3]); //  om[1][0]
  *(om+4)= qq + 2.0f * qo[2]*qo[2];            //  om[1][1]
  *(om+5)= 2.0f * (qo[2]*qo[3] - qo[0]*qo[1]); //  om[1][2]
  *(om+6)= 2.0f * (qo[3]*qo[1] - qo[0]*qo[2]); //  om[2][0]
  *(om+7)= 2.0f * (qo[3]*qo[2] + qo[0]*qo[1]); //  om[2][1]
  *(om+8)= qq + 2.0f * qo[3]*qo[3];            //  om[2][2]

  return 1;

}

int om2quf (float* om, float* qu, int p){
  float sign, s, s1, s2, s3;
  int i;
  float epsijk;
  epsijk = (float) p;

  s = om[0] + om[4] + om[8] + 1.0f;
  if (fabsf(s) < eps) {s = 0.0f;}
  s = sqrtf(s);
  qu[0] = epsijk * s * 0.50f;

  s1 = om[0] - om[4] - om[8] + 1.0f;
  if (fabsf(s1) < eps) {s1 = 0.0f;}
  s1 = sqrtf(s1);
  qu[1] = s1* 0.50f;

  s2 = -om[0] + om[4] - om[8] + 1.0f;
  if (fabsf(s2) < eps) {s2 = 0.0f;}
  s2 = sqrtf(s2);
  qu[2] = s2* 0.50f;

  s3 = -om[0] - om[4] + om[8] + 1.0f;
  if (fabsf(s3) < eps) {s3 = 0.0f;}
  s3 = sqrtf(s3);
  qu[3] = s3* 0.50f;

  if (om[7] < om[5]) {qu[1] *= -1.0f;}
  if (om[2] < om[6]) {qu[2] *= -1.0f;}
  if (om[3] < om[1]) {qu[3] *= -1.0f;}

  //sign = (float) (qu[0] >= 0.0f) - (float) (qu[0] < 0.0f);
  sign = ((qu[0] >= 0.0) ? 1.0f : -1.0f);
  for (i=0;i<4;i++){qu[i] *= sign;}


  return 1;
}



int qu2axf (float* qu, float* ax, int p){
  float sign, omega, mag = 0.0, qo[4];
  int i;
  float epsijk;
  epsijk = (float) p;

  // make sure q[0] is >= 0.0
  //sign = (float) (qu[0] >= 0.0f) - (float) (qu[0] < 0.0f);
  sign = ((qu[0] >= 0.0) ? 1.0f : -1.0f);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}

  omega = 2.0*acosf(qo[0]);
  if (omega < eps){
    ax[0] = 0.0f;
    ax[1] = 0.0f;
    ax[2] = 1.0f;
    ax[3] = 0.0f;
  } else {

    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    mag = 1.0f / sqrtf(mag);
    for (i=0;i<3;i++){ax[i] = qo[i+1]*mag;}
    ax[3] = omega;
  }
  
  return 1;
}

int qu2rof (float* qu, float* ro, int p){
  float sign, omega, mag = 0.0, qo[4];
  int i;
  float epsijk;
  epsijk = (float) p;

  // make sure q[0] is >= 0.0
  //sign = (float) (qu[0] >= 0.0f) - (float) (qu[0] < 0.0f);
  sign = ((qu[0] >= 0.0) ? 1.0f : -1.0f);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}

  if (qo[0] < eps){
    
    ro[3] = INFINITY; 
    for (i=0;i<3;i++){ro[i] = qo[i+1];}

  } else {
    
    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    if (mag < eps){
      ro[0] = 0.0f;
      ro[1] = 0.0f;
      ro[2] = 1.0f;
      ro[3] = 0.0f;
    
    } else {
      ro[3] = tanf(acosf(qo[0]));
      mag = 1.0f / sqrtf(mag);
      for (i=0;i<3;i++){ro[i] = qo[i+1]*mag;}
    
    }
  }
    return 1;
}


int qu2hof (float* qu, float* ho, int p){
  float sign, omega, mag = 0.0, qo[4], f;
  int i;
  float epsijk;
  epsijk = (float) p;

  // make sure q[0] is >= 0.0
  //sign = (float) (qu[0] >= 0.0f) - (float) (qu[0] < 0.0f);
  sign = ((qu[0] >= 0.0) ? 1.0f : -1.0f);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}

  omega = 2.0*acosf(qo[0]);
  if (omega < eps){
    ho[0] = 0.0f;
    ho[1] = 0.0f;
    ho[2] = 0.0f;
  } else {

    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    f = 0.750f * (omega - sinf(omega));
    f = pow(f, (1.0f / 3.0f));
    mag = f / sqrtf(mag);

    for (i=0;i<3;i++){ho[i] = qo[i+1]*mag;}
  
  }
  return 1;
}

int ho2cuf (float* ho, float* cu, int p){
  int trash;
  float epsijk;
  
  epsijk = (float) p;

  trash = Lambert3DBallToCubef(ho, cu);
  return 1;
}

int cu2hof (float* cu, float* ho, int p){
  int trash;
  float epsijk;
  
  epsijk = (float) p;

  trash = Lambert3DCubeToBallf(cu, ho);
  return 1;
}

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Dependant Codes Start Here
////////////////////////////////////////////////////////////////

int eu2rof (float* eu, float* ro, int p){
  float t,  ax[4];
  int trash, i;
  float epsijk;
  
  epsijk = (float) p;
  

  trash = eu2axf (eu, ax, p);
  trash = ax2rof (ax, ro, p); 


  /*t = ax[3];
  for (i = 0;i < 3;i++){ ro[i] = ax[i]; }

  if (fabsf(t - 2.0f*M_PI) < eps) {
    ro[3] = INFINITY;
  } else {
    if (t == 0.0f) {
      ro[0] = 0.0f;
      ro[1] = 0.0f;
      ro[2] = epsijk;
      ro[3] = 0.0f;
    } else {
      ro[3] = tanf(t * 0.5);
    }
  }*/
  

  return 1;
}



int ro2omf (float* ro, float* om, int p){
  float ax[4];
  int trash;

  trash = ro2axf(ro, ax, p);
  trash = ax2omf(ax, om, p);

  return 1;

}

int ro2euf (float* ro, float* eu, int p){
  float om[9];
  int trash;

  trash = ro2omf(ro, om, p);
  trash = om2euf(om, eu, p);
  return 1;

}

int eu2hof (float* eu, float* ho, int p){
  float ax[4];
  int trash;

  trash = eu2axf(eu, ax, p);
  trash = ax2hof(ax, ho, p);
  return 1;

}

int om2rof (float* om, float* ro, int p){
  float eu[3];
  int trash;

  trash = om2euf(om, eu, p);
  trash = eu2rof(eu, ro, p);
  return 1;

}


int om2hof (float* om, float* ho, int p){
  float ax[4];
  int trash;

  trash = om2axf(om, ax, p);
  trash = ax2hof(ax, ho, p);
  return 1;

}

int ax2euf (float* ax, float* eu, int p){
  float om[9];
  int trash;

  trash = ax2omf(ax, om, p);
  trash = om2euf(om, eu, p);
  return 1;

}

int ro2quf (float* ro, float* qu, int p){
  float ax[4];
  int trash;

  trash = ro2axf(ro, ax, p);
  trash = ax2quf(ax, qu, p);
  return 1;

}

int ho2euf (float* ho, float* eu, int p){
  float ax[4];
  int trash;

  trash = ho2axf(ho, ax, p);
  trash = ax2euf(ax, eu, p);
  return 1;

}

int ho2omf (float* ho, float* om, int p){
  float ax[4];
  int trash;

  trash = ho2axf(ho, ax, p);
  trash = ax2omf(ax, om, p);
  return 1;

}

int ho2rof (float* ho, float* ro, int p){
  float ax[4];
  int trash;

  trash = ho2axf(ho, ax, p);
  trash = ax2rof(ax, ro, p);
  return 1;

}

int ho2quf (float* ho, float* qu, int p){
  float ax[4];
  int trash;

  trash = ho2axf(ho, ax, p);
  trash = ax2quf(ax, qu, p);
  return 1;
}

int eu2cuf (float* eu, float* cu, int p){
  float ho[3];
  int trash;

  trash = eu2hof(eu, ho, p);
  trash = ho2cuf(ho, cu, p);
  return 1;
}

int om2cuf (float* om, float* cu, int p){
  float ho[3];
  int trash;

  trash = om2hof(om, ho, p);
  trash = ho2cuf(ho, cu, p);
  return 1;
}

int ax2cuf (float* ax, float* cu, int p){
  float ho[3];
  int trash;

  trash = ax2hof(ax, ho, p);
  trash = ho2cuf(ho, cu, p);
  return 1;

}

int ro2cuf (float* ro, float* cu, int p){
  float ho[3];
  int trash;

  trash = ro2hof(ro, ho, p);
  trash = ho2cuf(ho, cu, p);
  return 1;
}

int qu2cuf (float* qu, float* cu, int p){
  float ho[3];
  int trash;

  trash = qu2hof(qu, ho, p);
  trash = ho2cuf(ho, cu, p);
  return 1;
}

int cu2euf (float* cu, float* eu, int p){
  float ho[3];
  int trash;

  trash = cu2hof(cu, ho, p);
  trash = ho2euf(ho, eu, p);
  return 1;
}


int cu2omf (float* cu, float* om, int p){
  float ho[3];
  int trash;

  trash = cu2hof(cu, ho, p);
  trash = ho2omf(ho, om, p);
  return 1;
}

int cu2axf (float* cu, float* ax, int p){
  float ho[3];
  int trash;

  trash = cu2hof(cu, ho, p);
  trash = ho2axf(ho, ax, p);
  return 1;
}


int cu2rof (float* cu, float* ro, int p){
  float ho[3];
  int trash;

  trash = cu2hof(cu, ho, p);
  trash = ho2rof(ho, ro, p);
  return 1;
}

int cu2quf (float* cu, float* qu, int p){
  float ho[3];
  int trash;

  trash = cu2hof(cu, ho, p);
  trash = ho2quf(ho, qu, p);
  return 1;
}







