/*###################################################################
 Copyright (c) 2015 David Rowenhorst/Naval Research Laboratoy
 All rights reserved. 

 Redistribution and use in source and binary forms, with or without modification, are
 permitted provided that the following conditions are met:

     - Redistributions of source code must retain the above copyright notice, this list
        of conditions and the following disclaimer.
     - Redistributions in binary form must reproduce the above copyright notice, this
        list of conditions and the following disclaimer in the documentation and/or
        other materials provided with the distribution.
     - Neither the names of David Rowenhorst, The U.S. Naval Research Laboratory nor the names
        of its contributors may be used to endorse or promote products derived from
        this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ################################################################### */
#ifndef _ROTLIBLOOPSD_H
#define _ROTLIBLOOPSD_H

int ax2cuLoop (double* ax, double* cu,  unsigned long long n, int p);
int ax2euLoop (double* ax, double* eu,  unsigned long long n, int p);
int ax2hoLoop (double* ax, double* ho,  unsigned long long n, int p);
int ax2omLoop (double* ax, double* om,  unsigned long long n, int p);
int ax2quLoop (double* ax, double* qu,  unsigned long long n, int p);
int ax2roLoop (double* ax, double* ro,  unsigned long long n, int p);
int cu2axLoop (double* cu, double* ax,  unsigned long long n, int p);
int cu2euLoop (double* cu, double* eu,  unsigned long long n, int p);
int cu2hoLoop (double* cu, double* ho,  unsigned long long n, int p);
int cu2omLoop (double* cu, double* om,  unsigned long long n, int p);
int cu2quLoop (double* cu, double* qu,  unsigned long long n, int p);
int cu2roLoop (double* cu, double* ro,  unsigned long long n, int p);
int eu2axLoop (double* eu, double* ax,  unsigned long long n, int p);
int eu2cuLoop (double* eu, double* cu,  unsigned long long n, int p);
int eu2hoLoop (double* eu, double* ho,  unsigned long long n, int p);
int eu2omLoop (double* eu, double* om,  unsigned long long n, int p);
int eu2quLoop (double* eu, double* qu,  unsigned long long n, int p);
int eu2roLoop (double* eu, double* ro,  unsigned long long n, int p);
int ho2axLoop (double* ho, double* ax,  unsigned long long n, int p);
int ho2cuLoop (double* ho, double* cu,  unsigned long long n, int p);
int ho2euLoop (double* ho, double* eu,  unsigned long long n, int p);
int ho2omLoop (double* ho, double* om,  unsigned long long n, int p);
int ho2quLoop (double* ho, double* qu,  unsigned long long n, int p);
int ho2roLoop (double* ho, double* ro,  unsigned long long n, int p);
int om2axLoop (double* om, double* ax,  unsigned long long n, int p);
int om2cuLoop (double* om, double* cu,  unsigned long long n, int p);
int om2euLoop (double* om, double* eu,  unsigned long long n, int p);
int om2hoLoop (double* om, double* ho,  unsigned long long n, int p);
int om2quLoop (double* om, double* qu,  unsigned long long n, int p);
int om2roLoop (double* om, double* ro,  unsigned long long n, int p);
int qu2axLoop (double* qu, double* ax,  unsigned long long n, int p);
int qu2cuLoop (double* qu, double* cu,  unsigned long long n, int p);
int qu2euLoop (double* qu, double* eu,  unsigned long long n, int p);
int qu2hoLoop (double* qu, double* ho,  unsigned long long n, int p);
int qu2omLoop (double* qu, double* om,  unsigned long long n, int p);
int qu2roLoop (double* qu, double* ro,  unsigned long long n, int p);
int ro2axLoop (double* ro, double* ax,  unsigned long long n, int p);
int ro2cuLoop (double* ro, double* cu,  unsigned long long n, int p);
int ro2euLoop (double* ro, double* eu,  unsigned long long n, int p);
int ro2hoLoop (double* ro, double* ho,  unsigned long long n, int p);
int ro2omLoop (double* ro, double* om,  unsigned long long n, int p);
int ro2quLoop (double* ro, double* qu,  unsigned long long n, int p);
#endif
