#include "rotationLibCDbl.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lambertProjectionsDbl.h"

static const double M_2PI = (double) (M_PI * 2.0); //define 2*Pi
static const double eps = (double) 1.0e-12; // define a lower doubleing point precision

int eu2om (double* eu, double* om, int p){
  double c1, c2, c3, s1, s2, s3;
  int i;
  double omTemp[9];
  double epsijk;
  
  epsijk = (double) p;

  c1 = cos(eu[0]);
  c2 = cos(eu[1]);
  c3 = cos(eu[2]);
  s1 = sin(eu[0]);
  s2 = sin(eu[1]);
  s3 = sin(eu[2]);

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

int eu2ax (double* eu, double* ax, int p){
  double t, sig, ssig, del, tau, alpha;
  int i;
  double epsijk;
  
  epsijk = (double) p;

  t = tan(eu[1] * 0.50);
  sig = 0.50*(eu[0]+eu[2]);
  ssig = sin(sig);
  del = 0.50*(eu[0]-eu[2]);
  tau =  sqrt(t*t+ssig*ssig);

  if (fabs(sig -(double) M_PI_2) < eps) {
    alpha = (double) M_PI;
  } else {
    alpha = 2.0 * atan(tau/cos(sig));
  }

  if (fabs(alpha) < eps ) {
    ax[0] = 0.0;
    ax[1] = 0.0;
    ax[2] = -1.0*epsijk;
    ax[3] = 0.0;
  } else {
    ax[0] = -1.0 * epsijk * t * cos(del) / tau;
    ax[1] = -1.0 * epsijk * t * sin(del) / tau;
    ax[2] = -1.0 * epsijk * ssig / tau;
    ax[3] = alpha;
  }

  if (alpha < 0.0) {
    for (i = 0;i < 4;i++){ ax[i] *= -1.0; }
  }

  return 1;
}




int eu2qu ( double* eu, double* q, int p){
  double phi1, phi, phi2, dphi1phi2,sphi1phi2, cphi, sphi, sign=0.0;
  double epsijk;
  epsijk = (double) p; 
  /* 
   A function that converts a set of bunge euler angles 
   to a quaternion to bunge euler angles 
   */

  phi1 = eu[0]/2.0;
  phi =  eu[1]/2.0;  
  phi2 = eu[2]/2.0;
  
  dphi1phi2 = phi1-phi2;
  sphi1phi2 = phi1+phi2;
  cphi = cos(phi);
  sphi = -1.0*sin(phi);
  
  q[0] = cphi*cos(sphi1phi2)+0.0;
  //sign = ((q[0] >= 0.0) ? 1.0 : 0.0) - ((q[0] < 0.0) ? 1.0: 0.0);
  sign = ((q[0] >= 0.0) ? 1.0 : -1.0);
  q[0] *= sign;
  q[1] = epsijk*sign * sphi*cos(dphi1phi2)+0.0;
  q[2] = epsijk*sign * sphi*sin(dphi1phi2)+0.0;
  q[3] = -1.0*epsijk*sign*cphi*sin(sphi1phi2)+0.0;
  
  return 1;
}

int om2eu (double* om, double* eu, int p){
  double zeta;
  double epsijk;
  epsijk = (double) p;

  if ((1.0 - fabs(om[8])) > eps){
    eu[1] = acos(om[8]);
    zeta = 1.0/(sqrt(1.0 - om[8]*om[8]));
    eu[0] = atan2(om[6] * zeta, -1.0*om[7]*zeta);
    eu[2] = atan2(om[2] * zeta, om[5]*zeta);
  } else {
    if ((fabs(om[8] - 1.0)) < eps) {
      eu[0] = atan2(om[1], om[0]);
      eu[1] = 0.0;
      eu[2] = 0.0;
    } else {
      eu[0] = -atan2(om[1], om[0]);
      eu[1] = (double) M_PI;
      eu[2] = 0.0; 
    }
  }

  eu[0] += 100.0*M_PI;
  eu[0] = fmod(eu[0], M_2PI);
  eu[2] += 100.0*M_PI;
  eu[2] = fmod(eu[2], M_2PI);
  return 1; 
}

int ax2om (double* ax, double* om, int p){
  double c, s, omc, q, om_temp[9];
  int i,j;
  double epsijk;
  epsijk = (double) p;

  c = cos(ax[3]);
  s = sin(ax[3]);
  omc = 1.0 - c;

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


int qu2eu (double* q, double* eu, int p ){
  double  q03, q12, chi, q0, sum, diff;
  double epsijk;
  epsijk = (double) p;
  
  q0 = epsijk * q[0];
  q03 = q0*q0 + q[3]*q[3];
  q12 = q[1]*q[1] + q[2]*q[2];
  chi = sqrt(q03*q12);

  if (chi == 0.0) {
    if (q12 == 0.0) {
      eu[2] = 0.0;
      eu[1] = 0.0;
      eu[0] = atan2(-2.0 * q0*q[3], q0*q0 - q[3]*q[3]);
    } else {
      eu[2] = 0.0;
      eu[1] = (double) M_PI;
      eu[0] = atan2( 2.0 * q[1]*q[2], q[1]*q[1] - q[2]*q[2]);
    }
  } else {
    eu[1] = atan2(2.0 * chi, q03 - q12);
    //chi = 1.0 / chi;
    diff = atan2(-q[2], -q[1] );
    sum  = atan2(-q[3], q0);
    eu[0] = diff + sum; 
    eu[2] = sum - diff;
  }

  eu[0] += M_2PI;
  eu[0] = fmod(eu[0], M_2PI);
  eu[2] += M_2PI;
  eu[2] = fmod(eu[2], M_2PI);

  return 1; 
}

int ax2ho (double* ax, double* ho, int p){
  double f;
  int i;
  double epsijk;
  epsijk = (double) p;

  f = 0.75f * (ax[3] - sin(ax[3]));
  f = pow(f, 1.0/3.0);

  for (i=0; i<3; i++){
    ho[i] = f * ax[i];
  }
  return 1;
}

int ho2ax (double* h, double* ax, int p){
  double hmag =0.0, hm, sqrthm, hn[3], s;
  static const double tfit[16] =  {1.0000000000018852, -0.5000000002194847,  
               -0.024999992127593126, - 0.003928701544781374,  
               -0.0008152701535450438, - 0.0002009500426119712,  
               -0.00002397986776071756, - 0.00008202868926605841,  
               +0.00012448715042090092, - 0.0001749114214822577,  
               +0.0001703481934140054, - 0.00012062065004116828, 
               +0.000059719705868660826, - 0.00001980756723965647,  
               +0.000003953714684212874, - 0.00000036555001439719544 };
  int i;
  double epsijk;
  epsijk = (double) p;

  
  for (i=0; i<3; i++){ hmag += h[i]*h[i]; }

  if (hmag < eps) {
    ax[0] = 0.0;
    ax[1] = 0.0;
    ax[2] = -1.0*epsijk;
    ax[3] = 0.0;
  } else {
    hm = hmag;
    sqrthm = sqrt(hm);
    for (i=0; i<3; i++){ hn[i] = h[i]/sqrthm; }

    s = tfit[0] + tfit[1] * hmag;
    for (i=2; i<16; i++){
      hm *= hmag;
      s += tfit[i] * hm;  
    }
  
  if (s >  1.0) { s =  1.0; }
  if (s < -1.0) { s = -1.0; }

  s = 2.0 * acos(s);
  for (i=0; i<3; i++){ ax[i] = hn[i]; }
  if (fabs(s - (double) M_PI) < eps) {
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

int om2axold (double* om, double* ax, int p){
  double tr, t, mag=0.0, d[3];  
  double *sortPtr[3];
  int sortIndx[3]; 
  int i;
  double epsijk;
  epsijk = (double) p;

  tr = om[0] + om[4] + om[8];
  t = 0.50 * (tr - 1.0);
  if (t >  1.0) { t =  1.0;}
  if (t < -1.0) { t = -1.0;}

  ax[3] = acos(t);

  if ((1.0 - fabs(t)) > eps) { // normal case.  
    ax[2] = epsijk * (om[3] - om[1]);
    ax[1] = epsijk * (om[2] - om[6]);
    ax[0] = epsijk * (om[7] - om[5]);
    
    

  } else {// degenerate case, either 0 or Pi rotation.  
    if (t > 0.0) { // identity rotation.  arbitrarily assign the axis to (001)
      ax[0] = 0.0;
      ax[1] = 0.0; 
      ax[2] = -1.0 * epsijk; 
      ax[3] = 0.0; 
  
    } else { // 180* rotataion.  Need to find the axis.  
      for (i=0; i<3; i++) {
        d[i] = sqrt(0.50*(om[i+3*i]+1.0));
        sortPtr[i] = &(d[i]);
      }
      // get the index ordering of d
      // first sort the pointers
      qsort(sortPtr, 3, sizeof(sortPtr[0]), cmpFunc );
      // now get the indices in order of largest to smallest.  
      for ( i = 0; i < 3; ++i) {
        sortIndx[i] = (int) (2 - (sortPtr[i] - &(d[0])));
      }

      d[sortIndx[1]] = om[3*sortIndx[0] + sortIndx[1]] / (2.0 * d[sortIndx[0]]);
      d[sortIndx[2]] = om[3*sortIndx[0] + sortIndx[2]] / (2.0 * d[sortIndx[0]]);

      for (i=0; i<3;i++){ ax[i] = d[i];}

    }


  }

  // normalize the axis 
  for (i=0; i<3;i++){
    mag += ax[i]*ax[i];
  }
    
  mag = 1.0/sqrt(mag);
  for (i=0; i<3;i++){
    ax[i] *= mag;
  }

  return 1;
}


int ro2ax (double* ro, double* ax, int p){
  double ta, ang;
  int i;
  double epsijk;
  
  epsijk = (double) p;

  ta = ro[3];
  if (ta < eps) {
    ax[0] = 0.0;
    ax[1] = 0.0;
    ax[2] = -1.0 * epsijk;
    ax[3] = 0.0;
  } else {
    if (ta == INFINITY) {
      ax[0] = ro[0];
      ax[1] = ro[1];
      ax[2] = ro[2];
      ax[3] = (double) M_PI;
    } else {
      ax[3] = 2.0 * atan(ta);
      ta = 0.0;
      for (i=0;i<3;i++) {ta += ro[i]*ro[i];}
      ta = 1.0 / sqrt(ta);
      for (i=0;i<3;i++) {ax[i] = ro[i]*ta;}
    }
  }
  return 1;
}



int ax2ro (double* ax, double* ro, int p){
  int i;
  double epsijk;
  
  epsijk = (double) p;


  if (ax[3] == 0.0) {
    ro[0] = 0.0;
    ro[1] = 0.0;
    ro[2] = -1.0*epsijk;
    ro[3] = 0.0;
  } else {
    for (i=0; i<3; ++i) {ro[i] = ax[i];}
    if ((M_PI - ax[3]) < eps) {
      ro[3] = INFINITY;
    } else {
      ro[3] = tan(ax[3]*0.50);
    }
  }
  return 1;
}

int ax2qu (double* ax, double* qu, int p){
  double  s, mag=0.0;
  int i;
  double epsijk;
  epsijk = (double) p;

  if (ax[3] < eps){
    qu[0] = 1.0;
    qu[1] = 0.0;
    qu[2] = 0.0;
    qu[3] = 0.0;
  } else {
    qu[0] = cos(ax[3]*0.50);
    for (i=0;i<3;i++){mag += ax[i]*ax[i];}

    s = sin(ax[3]*0.50)/mag;
    for (i=0;i<3;i++){qu[i+1] = ax[i]*s;}
  
  }


  return 1;
}

int ro2ho (double* ro, double* ho, int p){
  double mag = 0.0, f, t;
  int i;
  double epsijk;
  epsijk = (double) p;

  mag = ro[3];
  if (mag < eps) {
  
    for (i=0;i<3;i++){ho[i] = 0.0;} 
  
  } else {
    if (isinf(ro[3])) {
      f = (double) 0.750 * M_PI;
    } else {
      t = 2.0 * atan(ro[3]);
      f = 0.750 * (t - sin(t));
    }

    f = pow(f, (1.0 / 3.0));
  
    for (i=0;i<3;i++){ ho[i] = ro[i]*f;}

  }
  return 1;
}


int qu2om (double* qu, double* om, int p){
  double sign, qq, qo[4];
  int i;
  double epsijk;
  epsijk = (double) p;

  //sign = (double) (qu[0] >= 0.0) - (double) (qu[0] < 0.0);
  sign = ((qu[0] >= 0.0) ? 1.0 : -1.0);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}
  qo[0] *= epsijk; // easier than trasnposing at the end.  

  qq = qo[0]*qo[0] - (qo[1]*qo[1] + qo[2]*qo[2] + qo[3]*qo[3]);

  *(om)  = qq + 2.0 * qo[1]*qo[1];            // om[0][0]
  *(om+1)= 2.0 * (qo[1]*qo[2] - qo[0]*qo[3]); //  om[0][1]
  *(om+2)= 2.0 * (qo[1]*qo[3] + qo[0]*qo[2]); //  om[0][2]
  *(om+3)= 2.0 * (qo[2]*qo[1] + qo[0]*qo[3]); //  om[1][0]
  *(om+4)= qq + 2.0 * qo[2]*qo[2];            //  om[1][1]
  *(om+5)= 2.0 * (qo[2]*qo[3] - qo[0]*qo[1]); //  om[1][2]
  *(om+6)= 2.0 * (qo[3]*qo[1] - qo[0]*qo[2]); //  om[2][0]
  *(om+7)= 2.0 * (qo[3]*qo[2] + qo[0]*qo[1]); //  om[2][1]
  *(om+8)= qq + 2.0 * qo[3]*qo[3];            //  om[2][2]

  return 1;

}

int om2qu (double* om, double* qu, int p){
  double sign, s, s1, s2, s3;
  int i;
  double epsijk;
  epsijk = (double) p;

  s = om[0] + om[4] + om[8] + 1.0;
  if (fabs(s) < eps) {s = 0.0;}
  s = sqrt(s);
  qu[0] = epsijk * s * 0.50;

  s1 = om[0] - om[4] - om[8] + 1.0;
  if (fabs(s1) < eps) {s1 = 0.0;}
  s1 = sqrt(s1);
  qu[1] = s1* 0.50;

  s2 = -om[0] + om[4] - om[8] + 1.0;
  if (fabs(s2) < eps) {s2 = 0.0;}
  s2 = sqrt(s2);
  qu[2] = s2* 0.50;

  s3 = -om[0] - om[4] + om[8] + 1.0;
  if (fabs(s3) < eps) {s3 = 0.0;}
  s3 = sqrt(s3);
  qu[3] = s3* 0.50;

  if (om[7] < om[5]) {qu[1] *= -1.0;}
  if (om[2] < om[6]) {qu[2] *= -1.0;}
  if (om[3] < om[1]) {qu[3] *= -1.0;}

  sign = ((qu[0] >= 0.0) ? 1.0 : -1.0);
  for (i=0;i<4;i++){qu[i] *= sign;}


  return 1;
}



int qu2ax (double* qu, double* ax, int p){
  double sign, omega, mag = 0.0, qo[4];
  int i;
  double epsijk;
  epsijk = (double) p;

  // make sure q[0] is >= 0.0
  //sign = (double) (qu[0] >= 0.0) - (double) (qu[0] < 0.0);
  sign = ((qu[0] >= 0.0) ? 1.0 : -1.0);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}

  omega = 2.0*acos(qo[0]);
  if (omega < eps){
    ax[0] = 0.0;
    ax[1] = 0.0;
    ax[2] = -1.0 * epsijk;
    ax[3] = 0.0;
  } else {

    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    mag = 1.0 / sqrt(mag);
    for (i=0;i<3;i++){ax[i] = qo[i+1]*mag;}
    ax[3] = omega;
  }
  
  return 1;
}

int qu2ro (double* qu, double* ro, int p){
  double sign, omega, mag = 0.0, qo[4];
  int i;
  double epsijk;
  epsijk = (double) p;

  // make sure q[0] is >= 0.0
  for (i=0;i<4;i++){qo[i] = qu[i];}
  //sign = ((double) (qo[0] >= 0.0)) - ((double) (qo[0] < 0.0));
  sign = ((qo[0] >= 0.0) ? 1.0 : -1.0);
  for (i=0;i<4;i++){qo[i] *= sign;}
  
  if (qo[0] < eps){
    
    ro[3] = INFINITY; 
    for (i=0;i<3;i++){ro[i] = qo[i+1];}

  } else {
    
    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    if (mag < eps){
      ro[0] = 0.0;
      ro[1] = 0.0;
      ro[2] = -epsijk;
      ro[3] = 0.0;
    
    } else {
      ro[3] = tan(acos(qo[0]));
      mag = 1.0 / sqrt(mag);
      for (i=0;i<3;i++){ro[i] = qo[i+1]*mag;}
    
    }
  }
    return 1;
}


int qu2ho (double* qu, double* ho, int p){
  double sign, omega, mag = 0.0, qo[4], f;
  int i;
  double epsijk;
  epsijk = (double) p;

  // make sure q[0] is >= 0.0
  //sign = (double) (qu[0] >= 0.0) - (double) (qu[0] < 0.0);
  sign = ((qu[0] >= 0.0) ? 1.0 : -1.0);
  for (i=0;i<4;i++){qo[i] = sign*qu[i];}

  omega = 2.0*acos(qo[0]);
  if (omega < eps){
    ho[0] = 0.0;
    ho[1] = 0.0;
    ho[2] = 0.0;
  } else {

    for (i=1;i<4;i++){mag += qo[i]*qo[i];}
    f = 0.750 * (omega - sin(omega));
    f = pow(f, (1.0 / 3.0));
    mag = f / sqrt(mag);

    for (i=0;i<3;i++){ho[i] = qo[i+1]*mag;}
  
  }
  return 1;
}

int ho2cu (double* ho, double* cu, int p){
  int trash;
  double epsijk;
  
  epsijk = (double) p;

  trash = Lambert3DBallToCube(ho, cu);
  return 1;
}

int cu2ho (double* cu, double* ho, int p){
  int trash;
  double epsijk;
  
  epsijk = (double) p;

  trash = Lambert3DCubeToBall(cu, ho);
  return 1;
}

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Dependant Codes Start Here
////////////////////////////////////////////////////////////////

int eu2ro (double* eu, double* ro, int p){
  double t,  ax[4];
  int trash, i;
  double epsijk;
  
  epsijk = (double) p;
  

  trash = eu2ax(eu, ax, p);
  trash = ax2ro(ax, ro, p); 


  /*t = ax[3];
  for (i = 0;i < 3;i++){ ro[i] = ax[i]; }

  if (fabs(t - 2.0*M_PI) < eps) {
    ro[3] = INFINITY;
  } else {
    if (t == 0.0) {
      ro[0] = 0.0;
      ro[1] = 0.0;
      ro[2] = -epsijk;
      ro[3] = 0.0;
    } else {
      ro[3] = tan(t * 0.5);
    }
  }*/
  

  return 1;
}



int ro2om (double* ro, double* om, int p){
  double ax[4];
  int trash;

  trash = ro2ax(ro, ax, p);
  trash = ax2om(ax, om, p);

  return 1;

}

int ro2eu (double* ro, double* eu, int p){
  double om[9];
  int trash;

  trash = ro2om(ro, om, p);
  trash = om2eu(om, eu, p);
  return 1;

}

int eu2ho (double* eu, double* ho, int p){
  double ax[4];
  int trash;

  trash = eu2ax(eu, ax, p);
  trash = ax2ho(ax, ho, p);
  return 1;

}

int om2ax (double* om, double* ax, int p){
  double qu[4];
  int trash;

  trash = om2qu(om, qu, p);
  trash = qu2ax(qu, ax, p);
  return 1;

}

int om2ro (double* om, double* ro, int p){
  double eu[3];
  int trash;

  trash = om2eu(om, eu, p);
  trash = eu2ro(eu, ro, p);
  return 1;

}


int om2ho (double* om, double* ho, int p){
  double ax[4];
  int trash;

  trash = om2ax(om, ax, p);
  trash = ax2ho(ax, ho, p);
  return 1;

}

int ax2eu (double* ax, double* eu, int p){
  double om[9];
  int trash;

  trash = ax2om(ax, om, p);
  trash = om2eu(om, eu, p);
  return 1;

}

int ro2qu (double* ro, double* qu, int p){
  double ax[4];
  int trash;

  trash = ro2ax(ro, ax, p);
  trash = ax2qu(ax, qu, p);
  return 1;

}

int ho2eu (double* ho, double* eu, int p){
  double ax[4];
  int trash;

  trash = ho2ax(ho, ax, p);
  trash = ax2eu(ax, eu, p);
  return 1;

}

int ho2om (double* ho, double* om, int p){
  double ax[4];
  int trash;

  trash = ho2ax(ho, ax, p);
  trash = ax2om(ax, om, p);
  return 1;

}

int ho2ro (double* ho, double* ro, int p){
  double ax[4];
  int trash;

  trash = ho2ax(ho, ax, p);
  trash = ax2ro(ax, ro, p);
  return 1;

}

int ho2qu (double* ho, double* qu, int p){
  double ax[4];
  int trash;

  trash = ho2ax(ho, ax, p);
  trash = ax2qu(ax, qu, p);
  return 1;
}

int eu2cu (double* eu, double* cu, int p){
  double ho[3];
  int trash;

  trash = eu2ho(eu, ho, p);
  trash = ho2cu(ho, cu, p);
  return 1;
}

int om2cu (double* om, double* cu, int p){
  double ho[3];
  int trash;

  trash = om2ho(om, ho, p);
  trash = ho2cu(ho, cu, p);
  return 1;
}

int ax2cu (double* ax, double* cu, int p){
  double ho[3];
  int trash;

  trash = ax2ho(ax, ho, p);
  trash = ho2cu(ho, cu, p);
  return 1;

}

int ro2cu (double* ro, double* cu, int p){
  double ho[3];
  int trash;

  trash = ro2ho(ro, ho, p);
  trash = ho2cu(ho, cu, p);
  return 1;
}

int qu2cu (double* qu, double* cu, int p){
  double ho[3];
  int trash;

  trash = qu2ho(qu, ho, p);
  trash = ho2cu(ho, cu, p);
  return 1;
}

int cu2eu (double* cu, double* eu, int p){
  double ho[3];
  int trash;

  trash = cu2ho(cu, ho, p);
  trash = ho2eu(ho, eu, p);
  return 1;
}


int cu2om (double* cu, double* om, int p){
  double ho[3];
  int trash;

  trash = cu2ho(cu, ho, p);
  trash = ho2om(ho, om, p);
  return 1;
}

int cu2ax (double* cu, double* ax, int p){
  double ho[3];
  int trash;

  trash = cu2ho(cu, ho, p);
  trash = ho2ax(ho, ax, p);
  return 1;
}


int cu2ro (double* cu, double* ro, int p){
  double ho[3];
  int trash;

  trash = cu2ho(cu, ho, p);
  trash = ho2ro(ho, ro, p);
  return 1;
}

int cu2qu (double* cu, double* qu, int p){
  double ho[3];
  int trash;

  trash = cu2ho(cu, ho, p);
  trash = ho2qu(ho, qu, p);
  return 1;
}







