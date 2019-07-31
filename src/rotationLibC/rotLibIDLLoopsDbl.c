#include "rotLibIDLLoopsDbl.h"
#include <stdlib.h> 
 #include <stdio.h>
#include <math.h>

#ifdef _OPENMP
  #include <omp.h>
  #define OPENMPLIMIT 100000l
#endif
#include "rotationLibCDbl.h"


int ax2cuLoop (double* ax, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * custep;
     
    trash = ax2cu(&(ax[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int ax2euLoop (double* ax, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * eustep;
     
    trash = ax2eu(&(ax[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int ax2hoLoop (double* ax, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * hostep;
     
    trash = ax2ho(&(ax[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int ax2omLoop (double* ax, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * omstep;
     
    trash = ax2om(&(ax[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int ax2quLoop (double* ax, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * qustep;
     
    trash = ax2qu(&(ax[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



int ax2roLoop (double* ax, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, axstep = 4, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(axstep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * axstep;
    iOut = i * rostep;
     
    trash = ax2ro(&(ax[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int cu2axLoop (double* cu, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * axstep;
     
    trash = cu2ax(&(cu[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int cu2euLoop (double* cu, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * eustep;
     
    trash = cu2eu(&(cu[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int cu2hoLoop (double* cu, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * hostep;
     
    trash = cu2ho(&(cu[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int cu2omLoop (double* cu, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * omstep;
     
    trash = cu2om(&(cu[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int cu2quLoop (double* cu, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * qustep;
     
    trash = cu2qu(&(cu[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



int cu2roLoop (double* cu, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, custep = 3, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(custep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * custep;
    iOut = i * rostep;
     
    trash = cu2ro(&(cu[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int eu2axLoop (double* eu, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * axstep;
     
    trash = eu2ax(&(eu[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int eu2cuLoop (double* eu, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * custep;
     
    trash = eu2cu(&(eu[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int eu2hoLoop (double* eu, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * hostep;
     
    trash = eu2ho(&(eu[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int eu2omLoop (double* eu, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * omstep;
     
    trash = eu2om(&(eu[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int eu2quLoop (double* eu, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * qustep;
     
    trash = eu2qu(&(eu[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



int eu2roLoop (double* eu, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, eustep = 3, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(eustep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * eustep;
    iOut = i * rostep;
     
    trash = eu2ro(&(eu[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int ho2axLoop (double* ho, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * axstep;
     
    trash = ho2ax(&(ho[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int ho2cuLoop (double* ho, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * custep;
     
    trash = ho2cu(&(ho[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int ho2euLoop (double* ho, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * eustep;
     
    trash = ho2eu(&(ho[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int ho2omLoop (double* ho, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * omstep;
     
    trash = ho2om(&(ho[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int ho2quLoop (double* ho, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * qustep;
     
    trash = ho2qu(&(ho[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



int ho2roLoop (double* ho, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, hostep = 3, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(hostep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * hostep;
    iOut = i * rostep;
     
    trash = ho2ro(&(ho[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int om2axLoop (double* om, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * axstep;
     
    trash = om2ax(&(om[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int om2cuLoop (double* om, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * custep;
     
    trash = om2cu(&(om[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int om2euLoop (double* om, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * eustep;
     
    trash = om2eu(&(om[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int om2hoLoop (double* om, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * hostep;
     
    trash = om2ho(&(om[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int om2quLoop (double* om, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * qustep;
     
    trash = om2qu(&(om[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



int om2roLoop (double* om, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, omstep = 9, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(omstep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * omstep;
    iOut = i * rostep;
     
    trash = om2ro(&(om[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int qu2axLoop (double* qu, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * axstep;
     
    trash = qu2ax(&(qu[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int qu2cuLoop (double* qu, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * custep;
     
    trash = qu2cu(&(qu[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int qu2euLoop (double* qu, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * eustep;
     
    trash = qu2eu(&(qu[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int qu2hoLoop (double* qu, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * hostep;
     
    trash = qu2ho(&(qu[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int qu2omLoop (double* qu, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * omstep;
     
    trash = qu2om(&(qu[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int qu2roLoop (double* qu, double* ro, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, qustep = 4, rostep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(qustep, rostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * qustep;
    iOut = i * rostep;
     
    trash = qu2ro(&(qu[iIn]), &(ro[iOut]), p);
     
  }
return 1;
}



int ro2axLoop (double* ro, double* ax, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, axstep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, axstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * axstep;
     
    trash = ro2ax(&(ro[iIn]), &(ax[iOut]), p);
     
  }
return 1;
}



int ro2cuLoop (double* ro, double* cu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, custep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, custep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * custep;
     
    trash = ro2cu(&(ro[iIn]), &(cu[iOut]), p);
     
  }
return 1;
}



int ro2euLoop (double* ro, double* eu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, eustep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, eustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * eustep;
     
    trash = ro2eu(&(ro[iIn]), &(eu[iOut]), p);
     
  }
return 1;
}



int ro2hoLoop (double* ro, double* ho, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, hostep = 3;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, hostep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * hostep;
     
    trash = ro2ho(&(ro[iIn]), &(ho[iOut]), p);
     
  }
return 1;
}



int ro2omLoop (double* ro, double* om, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, omstep = 9;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, omstep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * omstep;
     
    trash = ro2om(&(ro[iIn]), &(om[iOut]), p);
     
  }
return 1;
}



int ro2quLoop (double* ro, double* qu, unsigned long long n, int p){
  int trash;
  unsigned long long i, iIn, iOut, rostep = 4, qustep = 4;

#ifdef _OPENMP
  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}
#endif

#pragma omp parallel for \
  default(shared) private( i,iIn, iOut, trash) firstprivate(rostep, qustep) schedule (static)
  for (i=0;i<n;i++){ 
    iIn = i * rostep;
    iOut = i * qustep;
     
    trash = ro2qu(&(ro[iIn]), &(qu[iOut]), p);
     
  }
return 1;
}



