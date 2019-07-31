# include "rotLibIDLLoopsFlt.h"
#include <stdlib.h> 
 #include <stdio.h>
#include <math.h>

#ifdef _OPENMP
  #include <omp.h>
  #define OPENMPLIMIT 100000l
#endif
#include "rotationLibCDbl.h"


int ax2cuLoopf (float* ax, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, custep = 3;
  double axFlt[4], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, cuFlt) firstprivate(axstep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*custep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2cu(axFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int ax2euLoopf (float* ax, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, eustep = 3;
  double axFlt[4], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, euFlt) firstprivate(axstep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*eustep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2eu(axFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int ax2hoLoopf (float* ax, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, hostep = 3;
  double axFlt[4], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, hoFlt) firstprivate(axstep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*hostep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2ho(axFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int ax2omLoopf (float* ax, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, omstep = 9;
  double axFlt[4], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, omFlt) firstprivate(axstep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*omstep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2om(axFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int ax2quLoopf (float* ax, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, qustep = 4;
  double axFlt[4], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, quFlt) firstprivate(axstep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*qustep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2qu(axFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


int ax2roLoopf (float* ax, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, axstep = 4, rostep = 4;
  double axFlt[4], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, axFlt, roFlt) firstprivate(axstep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*axstep;
    iOut = i*rostep;
     for (j=0;j<axstep; j++){axFlt[j] = (double)ax[iIn+j];}
     trash = ax2ro(axFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int cu2axLoopf (float* cu, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, axstep = 4;
  double cuFlt[3], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, axFlt) firstprivate(custep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*axstep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2ax(cuFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int cu2euLoopf (float* cu, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, eustep = 3;
  double cuFlt[3], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, euFlt) firstprivate(custep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*eustep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2eu(cuFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int cu2hoLoopf (float* cu, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, hostep = 3;
  double cuFlt[3], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, hoFlt) firstprivate(custep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*hostep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2ho(cuFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int cu2omLoopf (float* cu, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, omstep = 9;
  double cuFlt[3], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, omFlt) firstprivate(custep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*omstep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2om(cuFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int cu2quLoopf (float* cu, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, qustep = 4;
  double cuFlt[3], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, quFlt) firstprivate(custep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*qustep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2qu(cuFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


int cu2roLoopf (float* cu, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, custep = 3, rostep = 4;
  double cuFlt[3], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, cuFlt, roFlt) firstprivate(custep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*custep;
    iOut = i*rostep;
     for (j=0;j<custep; j++){cuFlt[j] = (double)cu[iIn+j];}
     trash = cu2ro(cuFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int eu2axLoopf (float* eu, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, axstep = 4;
  double euFlt[3], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, axFlt) firstprivate(eustep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*axstep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2ax(euFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int eu2cuLoopf (float* eu, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, custep = 3;
  double euFlt[3], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, cuFlt) firstprivate(eustep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*custep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2cu(euFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int eu2hoLoopf (float* eu, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, hostep = 3;
  double euFlt[3], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, hoFlt) firstprivate(eustep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*hostep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2ho(euFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int eu2omLoopf (float* eu, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, omstep = 9;
  double euFlt[3], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, omFlt) firstprivate(eustep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*omstep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2om(euFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int eu2quLoopf (float* eu, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, qustep = 4;
  double euFlt[3], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, quFlt) firstprivate(eustep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*qustep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2qu(euFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


int eu2roLoopf (float* eu, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, eustep = 3, rostep = 4;
  double euFlt[3], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, euFlt, roFlt) firstprivate(eustep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*eustep;
    iOut = i*rostep;
     for (j=0;j<eustep; j++){euFlt[j] = (double)eu[iIn+j];}
     trash = eu2ro(euFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int ho2axLoopf (float* ho, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, axstep = 4;
  double hoFlt[3], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, axFlt) firstprivate(hostep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*axstep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2ax(hoFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int ho2cuLoopf (float* ho, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, custep = 3;
  double hoFlt[3], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, cuFlt) firstprivate(hostep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*custep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2cu(hoFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int ho2euLoopf (float* ho, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, eustep = 3;
  double hoFlt[3], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, euFlt) firstprivate(hostep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*eustep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2eu(hoFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int ho2omLoopf (float* ho, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, omstep = 9;
  double hoFlt[3], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, omFlt) firstprivate(hostep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*omstep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2om(hoFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int ho2quLoopf (float* ho, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, qustep = 4;
  double hoFlt[3], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, quFlt) firstprivate(hostep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*qustep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2qu(hoFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


int ho2roLoopf (float* ho, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, hostep = 3, rostep = 4;
  double hoFlt[3], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, hoFlt, roFlt) firstprivate(hostep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*hostep;
    iOut = i*rostep;
     for (j=0;j<hostep; j++){hoFlt[j] = (double)ho[iIn+j];}
     trash = ho2ro(hoFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int om2axLoopf (float* om, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, axstep = 4;
  double omFlt[9], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, axFlt) firstprivate(omstep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*axstep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2ax(omFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int om2cuLoopf (float* om, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, custep = 3;
  double omFlt[9], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, cuFlt) firstprivate(omstep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*custep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2cu(omFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int om2euLoopf (float* om, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, eustep = 3;
  double omFlt[9], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, euFlt) firstprivate(omstep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*eustep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2eu(omFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int om2hoLoopf (float* om, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, hostep = 3;
  double omFlt[9], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, hoFlt) firstprivate(omstep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*hostep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2ho(omFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int om2quLoopf (float* om, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, qustep = 4;
  double omFlt[9], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, quFlt) firstprivate(omstep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*qustep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2qu(omFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


int om2roLoopf (float* om, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, omstep = 9, rostep = 4;
  double omFlt[9], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, omFlt, roFlt) firstprivate(omstep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*omstep;
    iOut = i*rostep;
     for (j=0;j<omstep; j++){omFlt[j] = (double)om[iIn+j];}
     trash = om2ro(omFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int qu2axLoopf (float* qu, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, axstep = 4;
  double quFlt[4], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, axFlt) firstprivate(qustep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*axstep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2ax(quFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int qu2cuLoopf (float* qu, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, custep = 3;
  double quFlt[4], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, cuFlt) firstprivate(qustep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*custep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2cu(quFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int qu2euLoopf (float* qu, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, eustep = 3;
  double quFlt[4], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, euFlt) firstprivate(qustep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*eustep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2eu(quFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int qu2hoLoopf (float* qu, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, hostep = 3;
  double quFlt[4], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, hoFlt) firstprivate(qustep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*hostep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2ho(quFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int qu2omLoopf (float* qu, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, omstep = 9;
  double quFlt[4], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, omFlt) firstprivate(qustep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*omstep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2om(quFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int qu2roLoopf (float* qu, float* ro,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, qustep = 4, rostep = 4;
  double quFlt[4], roFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, quFlt, roFlt) firstprivate(qustep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*qustep;
    iOut = i*rostep;
     for (j=0;j<qustep; j++){quFlt[j] = (double)qu[iIn+j];}
     trash = qu2ro(quFlt, roFlt, p);
     for (j=0;j<rostep; j++){ro[iOut + j] = (float)roFlt[j];}
  }
return 1;
}


int ro2axLoopf (float* ro, float* ax,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, axstep = 4;
  double roFlt[4], axFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, axFlt) firstprivate(rostep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*axstep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2ax(roFlt, axFlt, p);
     for (j=0;j<axstep; j++){ax[iOut + j] = (float)axFlt[j];}
  }
return 1;
}


int ro2cuLoopf (float* ro, float* cu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, custep = 3;
  double roFlt[4], cuFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, cuFlt) firstprivate(rostep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*custep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2cu(roFlt, cuFlt, p);
     for (j=0;j<custep; j++){cu[iOut + j] = (float)cuFlt[j];}
  }
return 1;
}


int ro2euLoopf (float* ro, float* eu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, eustep = 3;
  double roFlt[4], euFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, euFlt) firstprivate(rostep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*eustep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2eu(roFlt, euFlt, p);
     for (j=0;j<eustep; j++){eu[iOut + j] = (float)euFlt[j];}
  }
return 1;
}


int ro2hoLoopf (float* ro, float* ho,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, hostep = 3;
  double roFlt[4], hoFlt[3];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, hoFlt) firstprivate(rostep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*hostep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2ho(roFlt, hoFlt, p);
     for (j=0;j<hostep; j++){ho[iOut + j] = (float)hoFlt[j];}
  }
return 1;
}


int ro2omLoopf (float* ro, float* om,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, omstep = 9;
  double roFlt[4], omFlt[9];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, omFlt) firstprivate(rostep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*omstep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2om(roFlt, omFlt, p);
     for (j=0;j<omstep; j++){om[iOut + j] = (float)omFlt[j];}
  }
return 1;
}


int ro2quLoopf (float* ro, float* qu,  unsigned long long n, int p){
  int trash; 
  unsigned long long j, i, iIn, iOut, rostep = 4, qustep = 4;
  double roFlt[4], quFlt[4];

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( j,i,iIn, iOut, trash, roFlt, quFlt) firstprivate(rostep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i*rostep;
    iOut = i*qustep;
     for (j=0;j<rostep; j++){roFlt[j] = (double)ro[iIn+j];}
     trash = ro2qu(roFlt, quFlt, p);
     for (j=0;j<qustep; j++){qu[iOut + j] = (float)quFlt[j];}
  }
return 1;
}


