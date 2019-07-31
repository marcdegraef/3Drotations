
#ifndef _QUATLIB_H
#define _QUATLIB_H

int quatMultiply ( double *q1, double *q2, double *q1q2, int p);
int quatVector( double  *q1, double *v, double *q1v, int p);
int quatInverse ( double *q, double *qout);
int quatNormalize ( double *q, double *qout);

#endif