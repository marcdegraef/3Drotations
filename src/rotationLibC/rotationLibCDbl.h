
#pragma once

#ifndef _ROTLIBCDBL_H
#define _ROTLIBCDBL_H





int eu2om (double* eu, double* om, int p);
int eu2ax (double* eu, double* ax, int p);
int eu2qu (double* eu, double* q,  int p);
int om2eu (double* om, double* eu, int p);
int ax2om (double* ax, double* om, int p);
int qu2eu (double* q,  double* eu, int p);
int ax2ho (double* ax, double* ho, int p);
int ho2ax (double* h,  double* ax, int p);
int om2ax (double* om, double* ax, int p);
int ro2ax (double* ro, double* ax, int p);
int ax2ro (double* ax, double* ro, int p);
int ax2qu (double* ax, double* qu, int p);
int ro2ho (double* ro, double* ho, int p);
int qu2om (double* qu, double* om, int p);
int om2qu (double* om, double* qu, int p);
int qu2ax (double* qu, double* ax, int p);
int qu2ro (double* qu, double* ro, int p);
int qu2ho (double* qu, double* ho, int p);
int cu2ho (double* ho, double* cu, int p);
int ho2cu (double* ho, double* cu, int p);
///testing

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Dependant Codes Start Here
////////////////////////////////////////////////////////////////


int eu2ro (double* eu, double* ro, int p);
int ro2om (double* ro, double* om, int p);
int ro2eu (double* ro, double* eu, int p);
int eu2ho (double* eu, double* ho, int p);
int om2ro (double* om, double* ro, int p);
int om2ho (double* om, double* ho, int p);
int ax2eu (double* ax, double* eu, int p);
int ro2qu (double* ro, double* qu, int p);
int ho2eu (double* ho, double* eu, int p);
int ho2om (double* ho, double* om, int p);
int ho2ro (double* ho, double* ro, int p);
int ho2qu (double* ho, double* qu, int p);
int eu2cu (double* eu, double* cu, int p);
int om2cu (double* om, double* cu, int p);
int ax2cu (double* ax, double* cu, int p);
int ro2cu (double* ro, double* cu, int p);
int qu2cu (double* qu, double* cu, int p);
int cu2eu (double* cu, double* eu, int p);
int cu2om (double* cu, double* om, int p);
int cu2ax (double* cu, double* ax, int p);
int cu2ro (double* cu, double* ro, int p);
int cu2qu (double* cu, double* qu, int p);


#endif