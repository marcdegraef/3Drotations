pro idlrotlibCprogramwriter

  path =  FILE_DIRNAME(ROUTINE_FILEPATH('idlrotlibCprogramwriter'))
  cd, path
  lf = string(10b)
  tab = string('  ')

  rt = ['ax', 'cu', 'eu', 'ho', 'om', 'qu', 'ro'] ; rotation type
  rl= Strtrim([  4 ,   3 ,   3 ,   3 ,    9,   4,    4],2) ; rotation length

  close, 1
  close, 2
  close, 3
  close, 4
  close, 5
  close, 6
  close, 7
  
  openw, 1, 'rotLibIDLWrap.c'
  openw, 2, 'rotLibIDLWrap.h'
  openw, 3, 'rotLibIDLLoopsFlt.c'
  openw, 4, 'rotLibIDLLoopsFlt.h'
  OPENW, 5, 'rotLibIDLLoopsDbl.c'
  OPENW, 6, 'rotLibIDLLoopsDbl.h'
  
  openw, 7, 'rotationlibc.pro'
  
  openmp = '#ifdef _OPENMP' + lf + $
           '  #include <omp.h>' +  lf + $
           '  #define OPENMPLIMIT 100000l' + lf + $
           '#endif'
 
  
  
  copyright ='/*###################################################################' + lf + $
             ' Copyright (c) 2015 David Rowenhorst/Naval Research Laboratoy' + lf + $
             ' All rights reserved. ' + lf + $
             '' + lf + $
             ' Redistribution and use in source and binary forms, with or without modification, are' + lf + $
             ' permitted provided that the following conditions are met:' + lf + $
             '' + lf + $
             '     - Redistributions of source code must retain the above copyright notice, this list' + lf + $
             '        of conditions and the following disclaimer.' + lf + $
             '     - Redistributions in binary form must reproduce the above copyright notice, this' + lf + $
             '        list of conditions and the following disclaimer in the documentation and/or' + lf + $
             '        other materials provided with the distribution.' + lf + $
             '     - Neither the names of David Rowenhorst, The U.S. Naval Research Laboratory nor the names' + lf + $
             '        of its contributors may be used to endorse or promote products derived from' + lf + $
             '        this software without specific prior written permission.' + lf + $
             '' + lf + $
             ' THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"' + lf + $
             ' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE' + lf + $
             ' IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE' + lf + $
             ' ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE' + lf + $
             ' LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL' + lf + $
             ' DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR' + lf + $
             ' SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER' + lf + $
             ' CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,' + lf + $
             ' OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE' + lf + $
             ' USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.' + lf + $
             ' ################################################################### */'
  
           ; set up preambles for all the files.

  PRINTF, 1, '#include "rotLibIDLWrap.h"'
  PRINTf, 1, '#include <stdlib.h> '+lf+' #include <stdio.h>' + lf + '#include <math.h>'
  PRINTF, 1, ''
  PRINTF, 1, '#include "idl_export.h"'
  PRINTF, 1, '#include "rotLibIDLLoopsFlt.h"'
  PRINTF, 1, '#include "rotLibIDLLoopsDbl.h"'
  PRINTF, 1, ''
  PRINTF, 1, ''

  printf, 2, copyright
  printf, 2, '/*   ' + lf + $
             ' Author: David Rowenhorst' + lf + $
             ' date: 5 May 2015'+ lf + $
             ' brief: Interface between the c rotationlib and IDL.  This just converts from the IDL variables to'+ lf + $ 
             ' a function that will loop through the array of variables. */'
 printf, 2, '#ifndef _ROTLIBCIDLWRAP_H'
 printf, 2, '#define _ROTLIBCIDLWRAP_H'
 printf, 2, ''
 
 printf, 3, '# include "rotLibIDLLoopsFlt.h"'
 printf, 3, '#include <stdlib.h> '+lf+' #include <stdio.h>' + lf + '#include <math.h>'
 printf, 3, ''
 printf, 3, openmp
 printf, 3, '#include "rotationLibCDbl.h"
 printf, 3, ''
 printf, 3, ''
 
 printf, 4, copyright
 printf, 4, '#ifndef _ROTLIBLOOPSF_H'
 printf, 4, '#define _ROTLIBLOOPSF_H'
 printf, 4, ''
 
 PRINTF, 5, '#include "rotLibIDLLoopsDbl.h"'
 PRINTF, 5, '#include <stdlib.h> '+lf+' #include <stdio.h>' + lf + '#include <math.h>'
 PRINTF, 5, ''
 PRINTF, 5, openmp
 PRINTF, 5, '#include "rotationLibCDbl.h"
 PRINTF, 5, ''
 PRINTF, 5, ''

 PRINTF, 6, copyright
 PRINTF, 6, '#ifndef _ROTLIBLOOPSD_H'
 PRINTF, 6, '#define _ROTLIBLOOPSD_H'
 PRINTF, 6, ''        
 
 unload = '' 
 ;unload = ', /unload'
  
  
 for i = 0, n_elements(rt)-1 Do Begin
    for j = 0, n_elements(rt)-1 Do Begin
      if i NE j then begin
    
        printf, 1, 'int ' + rt[i] + '2'+rt[j] +'IDLWrap (int argc, void* argv[]){'
        printf, 1, '  int p, type;'
        printf, 1, '  unsigned long long n;
        printf, 1, '  IDL_LONG *pIn,  *typeIn;'
        printf, 1, '  IDL_ULONG64 *nIn;
        printf, 1, ''
        printf, 1, '  nIn = (IDL_ULONG64*) argv[2];'
        printf, 1, '  n = (unsigned long long) (*nIn);'
        printf, 1, '  pIn = (IDL_LONG*) argv[3];'
        printf, 1, '  p = (int) (*pIn);'
        printf, 1, '  typeIn = (IDL_LONG*) argv[4];'
        printf, 1, '  type = (int) (*typeIn);'
        printf, 1, ''
        printf, 1, '  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)'
        printf, 1, '    return ' + rt[i]+'2' + rt[j] + 'Loopf ( (float*) argv[0], (float*) argv[1], n, p);'
        printf, 1, '  } else { // double calculation and storage'
        printf, 1, '     return ' + rt[i]+'2' + rt[j] + 'Loop ( (double*) argv[0], (double*) argv[1], n, p);
        printf, 1, '  }' + lf + '}'+ lf+ lf + lf


        printf, 2, 'int ' + rt[i] + '2'+rt[j] +'IDLWrap (int argc, void* argv[]);'
        
        printf, 3, 'int ' + rt[i] + '2'+rt[j] +'Loopf (float* ' + rt[i] + ', float* '+rt[j]+',  unsigned long long n, int p){'
        printf, 3, '  int trash; 
        printf, 3, '  unsigned long long j, i, iIn, iOut, ' + rt[i]+'step = '+rl[i] + ', ' + rt[j]+'step = '+rl[j] +';'
        printf, 3, '  double ' + rt[i] +'Flt[' + rl[i] + '], '+ rt[j] +'Flt[' + rl[j] + '];'
        printf, 3, ''
        printf, 3, '#ifdef _OPENMP'
        printf, 3, '  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}'
        printf, 3, '#endif'
        printf, 3, ''
        ;printf, 3, '#pragma omp parallel \'
        ;printf, 3, '  default(shared) private( j,i,iIn, iOut, trash, '+rt[i]+'step, '+rt[j]+'step, '+rt[i] +'Flt, '+rt[j] +'Flt)'+lf+' {'
        ;printf, 3, '  firstprivate('+rt[i]+'step, '+rt[j]+'step)'+lf+'{'
        ;printf, 3, '  '+ rt[i]+'step = '+rl[i]+';' + lf +'  ' + rt[j]+'step = '+rl[j] +';'
        ;printf, 3, '#pragma opm for schedule (static)
        
        PRINTF, 3, '#pragma omp parallel for \'
        PRINTF, 3, '  default(shared) private( j,i,iIn, iOut, trash, '+rt[i] +'Flt, '+rt[j] +'Flt)' +' firstprivate('+rt[i]+'step, '+rt[j]+'step) schedule (static)'
        printf, 3, '  for (i=0;i<n;i++){ '
        printf, 3, '    iIn = i*'  + rt[i]+'step;'
        printf, 3, '    iOut = i*'  + rt[j]+'step;'
        printf, 3, '     for (j=0;j<'+ rt[i]+'step; j++){'+rt[i] +'Flt[j] = (double)'+ rt[i] + '[iIn+j];}'
        printf, 3, '     trash = '+ rt[i] + '2'+rt[j]+'('+rt[i] +'Flt, ' +rt[j] +'Flt, p);'
        printf, 3, '     for (j=0;j<'+ rt[j]+'step; j++){'+rt[j] +'[iOut + j] = (float)' + rt[j]+'Flt[j];}'
        ;printf, 3, '    trash = '+ rt[i] + '2'+rt[j]+'f(&('+rt[i] +'[iIn]), &(' +rt[j] +'[iOut]), p);'
        printf, 3, '  }' + lf + 'return 1;' + lf + '}' + lf + lf

        printf, 4, 'int ' + rt[i] + '2'+rt[j] +'Loopf (float* ' + rt[i] + ', float* '+rt[j]+',  unsigned long long n, int p);'

        printf, 5, 'int ' + rt[i] + '2'+rt[j] +'Loop (double* ' + rt[i] + ', double* '+rt[j]+', unsigned long long n, int p){'
        printf, 5, '  int trash;
        printf, 5, '  unsigned long long i, iIn, iOut, ' + rt[i]+'step = '+rl[i] + ', ' + rt[j]+'step = '+rl[j] +';'
        printf, 5, ''
        printf, 5, '#ifdef _OPENMP'
        printf, 5, '  if (n >= OPENMPLIMIT) {omp_set_num_threads(omp_get_num_procs());} else  {omp_set_num_threads(1);}'
        printf, 5, '#endif'
        printf, 5, ''
        printf, 5, '#pragma omp parallel for \'
        printf, 5, '  default(shared) private( i,iIn, iOut, trash) firstprivate('+rt[i]+'step, '+rt[j]+'step) schedule (static)'
        printf, 5, '  for (i=0;i<n;i++){ '
        printf, 5, '    iIn = i * '  + rt[i]+'step;'
        printf, 5, '    iOut = i * '  + rt[j]+'step;'
        printf, 5, '     
        printf, 5, '    trash = '+ rt[i] + '2'+rt[j]+'(&('+rt[i] +'[iIn]), &(' +rt[j] +'[iOut]), p);'
        printf, 5, '     
        printf, 5, '  }' + lf + 'return 1;' + lf + '}' + lf + lf + lf

        printf, 6, 'int ' + rt[i] + '2'+rt[j] +'Loop (double* ' + rt[i] + ', double* '+rt[j]+',  unsigned long long n, int p);'

        printf, 7, 'function '  + rt[i] + '2'+rt[j] + ', '+ rt[i] +',P=P'
        printf, 7, 'COMPILE_OPT HIDDEN'
        printf, 7, '  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)'
        printf, 7, '  sz = SIZE(' + rt[i] + ')
        printf, 7, '  type = LONG(sz[-2])'
        If rt[i] NE 'om' THEN $
          printf, 7, '  n = ULONG64(sz[-1]/sz[1])' $
        ELSE $
          printf, 7, '  n = ULONG64(sz[-1]/9l)
          
        IF rt[j] NE 'om' THEN $
          printf, 7, '  ' + rt[j]+' = MAKE_ARRAY('+ rl[j] + ',n, TYPE = type)' $
        ELSE $
          printf, 7, '  om = MAKE_ARRAY(3,3,n, TYPE = type)'
        
        printf, 7, '  path = FILE_DIRNAME(ROUTINE_FILEPATH("' + rt[i] + '2'+rt[j]+ '", /either))'
        printf, 7, '  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "'+rt[i] + '2'+rt[j]+ 'IDLWrap", $'
        printf, 7, '    '+rt[i]+', '+rt[j]+', n, pfac, type'+unload+')'
        printf, 7, ''
        printf, 7, '  return, '+rt[j]
        printf, 7, 'end'+lf+lf+lf
     
        
        

      endif
    endfor
endfor

; set up a dummy function to unload the library for testing purposes.  

printf, 1, 'int IDLRotLibUnload (int argc, void* argv[]){' + lf + 'return 1;' + lf + '}' 
printf, 2, 'int IDLRotLibUnload (int argc, void* argv[]);'
printf, 2, '#endif'
printf, 4, '#endif'
printf, 6, '#endif'
printf, 7, 'pro rotationlibcunload' + lf + 'path = FILE_DIRNAME(ROUTINE_FILEPATH("rotationlibcunload", /either))'
printf, 7, 'trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "IDLRotLibUnload", /unload)'
printf, 7, 'end'
printf, 7, 'pro rotationlibc'+lf+';dummy proceedure'+lf+'end'

for i = 1, 7 do close, i

end






