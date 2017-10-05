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
#ifndef _ROTLIBLOOPSF_H
#define _ROTLIBLOOPSF_H

int ax2cuLoopf (float* ax, float* cu,  unsigned long long n, int p);
int ax2euLoopf (float* ax, float* eu,  unsigned long long n, int p);
int ax2hoLoopf (float* ax, float* ho,  unsigned long long n, int p);
int ax2omLoopf (float* ax, float* om,  unsigned long long n, int p);
int ax2quLoopf (float* ax, float* qu,  unsigned long long n, int p);
int ax2roLoopf (float* ax, float* ro,  unsigned long long n, int p);
int cu2axLoopf (float* cu, float* ax,  unsigned long long n, int p);
int cu2euLoopf (float* cu, float* eu,  unsigned long long n, int p);
int cu2hoLoopf (float* cu, float* ho,  unsigned long long n, int p);
int cu2omLoopf (float* cu, float* om,  unsigned long long n, int p);
int cu2quLoopf (float* cu, float* qu,  unsigned long long n, int p);
int cu2roLoopf (float* cu, float* ro,  unsigned long long n, int p);
int eu2axLoopf (float* eu, float* ax,  unsigned long long n, int p);
int eu2cuLoopf (float* eu, float* cu,  unsigned long long n, int p);
int eu2hoLoopf (float* eu, float* ho,  unsigned long long n, int p);
int eu2omLoopf (float* eu, float* om,  unsigned long long n, int p);
int eu2quLoopf (float* eu, float* qu,  unsigned long long n, int p);
int eu2roLoopf (float* eu, float* ro,  unsigned long long n, int p);
int ho2axLoopf (float* ho, float* ax,  unsigned long long n, int p);
int ho2cuLoopf (float* ho, float* cu,  unsigned long long n, int p);
int ho2euLoopf (float* ho, float* eu,  unsigned long long n, int p);
int ho2omLoopf (float* ho, float* om,  unsigned long long n, int p);
int ho2quLoopf (float* ho, float* qu,  unsigned long long n, int p);
int ho2roLoopf (float* ho, float* ro,  unsigned long long n, int p);
int om2axLoopf (float* om, float* ax,  unsigned long long n, int p);
int om2cuLoopf (float* om, float* cu,  unsigned long long n, int p);
int om2euLoopf (float* om, float* eu,  unsigned long long n, int p);
int om2hoLoopf (float* om, float* ho,  unsigned long long n, int p);
int om2quLoopf (float* om, float* qu,  unsigned long long n, int p);
int om2roLoopf (float* om, float* ro,  unsigned long long n, int p);
int qu2axLoopf (float* qu, float* ax,  unsigned long long n, int p);
int qu2cuLoopf (float* qu, float* cu,  unsigned long long n, int p);
int qu2euLoopf (float* qu, float* eu,  unsigned long long n, int p);
int qu2hoLoopf (float* qu, float* ho,  unsigned long long n, int p);
int qu2omLoopf (float* qu, float* om,  unsigned long long n, int p);
int qu2roLoopf (float* qu, float* ro,  unsigned long long n, int p);
int ro2axLoopf (float* ro, float* ax,  unsigned long long n, int p);
int ro2cuLoopf (float* ro, float* cu,  unsigned long long n, int p);
int ro2euLoopf (float* ro, float* eu,  unsigned long long n, int p);
int ro2hoLoopf (float* ro, float* ho,  unsigned long long n, int p);
int ro2omLoopf (float* ro, float* om,  unsigned long long n, int p);
int ro2quLoopf (float* ro, float* qu,  unsigned long long n, int p);
#endif
