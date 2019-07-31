
#ifndef _QUATLIBF_H
#define _QUATLIBF_H

int quatMultiplyf ( float *q1, float *q2, float *q1q2, int p);
int quatVectorf( float  *q1, float *v, float *q1v, int p);
int quatInverse ( float *q, float *qout);
int quatNormalize ( float *q, float *qout);

#endif