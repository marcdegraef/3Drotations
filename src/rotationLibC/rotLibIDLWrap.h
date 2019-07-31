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
/*   
 Author: David Rowenhorst
 date: 5 May 2015
 brief: Interface between the c rotationlib and IDL.  This just converts from the IDL variables to
 a function that will loop through the array of variables. */
#ifndef _ROTLIBCIDLWRAP_H
#define _ROTLIBCIDLWRAP_H

int ax2cuIDLWrap (int argc, void* argv[]);
int ax2euIDLWrap (int argc, void* argv[]);
int ax2hoIDLWrap (int argc, void* argv[]);
int ax2omIDLWrap (int argc, void* argv[]);
int ax2quIDLWrap (int argc, void* argv[]);
int ax2roIDLWrap (int argc, void* argv[]);
int cu2axIDLWrap (int argc, void* argv[]);
int cu2euIDLWrap (int argc, void* argv[]);
int cu2hoIDLWrap (int argc, void* argv[]);
int cu2omIDLWrap (int argc, void* argv[]);
int cu2quIDLWrap (int argc, void* argv[]);
int cu2roIDLWrap (int argc, void* argv[]);
int eu2axIDLWrap (int argc, void* argv[]);
int eu2cuIDLWrap (int argc, void* argv[]);
int eu2hoIDLWrap (int argc, void* argv[]);
int eu2omIDLWrap (int argc, void* argv[]);
int eu2quIDLWrap (int argc, void* argv[]);
int eu2roIDLWrap (int argc, void* argv[]);
int ho2axIDLWrap (int argc, void* argv[]);
int ho2cuIDLWrap (int argc, void* argv[]);
int ho2euIDLWrap (int argc, void* argv[]);
int ho2omIDLWrap (int argc, void* argv[]);
int ho2quIDLWrap (int argc, void* argv[]);
int ho2roIDLWrap (int argc, void* argv[]);
int om2axIDLWrap (int argc, void* argv[]);
int om2cuIDLWrap (int argc, void* argv[]);
int om2euIDLWrap (int argc, void* argv[]);
int om2hoIDLWrap (int argc, void* argv[]);
int om2quIDLWrap (int argc, void* argv[]);
int om2roIDLWrap (int argc, void* argv[]);
int qu2axIDLWrap (int argc, void* argv[]);
int qu2cuIDLWrap (int argc, void* argv[]);
int qu2euIDLWrap (int argc, void* argv[]);
int qu2hoIDLWrap (int argc, void* argv[]);
int qu2omIDLWrap (int argc, void* argv[]);
int qu2roIDLWrap (int argc, void* argv[]);
int ro2axIDLWrap (int argc, void* argv[]);
int ro2cuIDLWrap (int argc, void* argv[]);
int ro2euIDLWrap (int argc, void* argv[]);
int ro2hoIDLWrap (int argc, void* argv[]);
int ro2omIDLWrap (int argc, void* argv[]);
int ro2quIDLWrap (int argc, void* argv[]);
int IDLRotLibUnload (int argc, void* argv[]);
#endif
