; ###################################################################
; Copyright (c) 2013-2015, Marc De Graef/Carnegie Mellon University
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without modification, are 
; permitted provided that the following conditions are met:
;
;     - Redistributions of source code must retain the above copyright notice, this list 
;        of conditions and the following disclaimer.
;     - Redistributions in binary form must reproduce the above copyright notice, this 
;        list of conditions and the following disclaimer in the documentation and/or 
;        other materials provided with the distribution.
;     - Neither the names of Marc De Graef, Carnegie Mellon University nor the names 
;        of its contributors may be used to endorse or promote products derived from 
;        this software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
; ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
; LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
; USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; ###################################################################

;--------------------------------------------------------------------------
; init_rotations
; 
; routine must be executed first to initialize a bunch of parameters
;
; This routine is called with the parameter Pchoice, which is P from the 
; rotation tutorial paper.  See rotationlib.pro for more detailed information.
;--------------------------------------------------------------------------
pro init_rotationsc,Pchoice



If N_ELEMENTS(Pchoice) EQ 0 THEN Pchoice = 1
Pchoice = Long((Pchoice GE 0)) - LONG((Pchoice LT 0)) ; 
defsysv, '!rotlib', EXISTS = flag
If flag eq 0 then $
  defsysv, '!rotlib' , {p:long(Pchoice)} $
else !rotlib.p = long(Pchoice)

;COMMON rotationcommon, LPs, epsijk
;
;; maintian compatibiltiy with Marc's Library as well.
;epsijk = Pchoice
;
;; these are a bunch of constants used for Lambert and related projections; they are all in double precision
;LPs = {LambertParametersType, $
;  Pi:DOUBLE(3.141592653589793D0), $    ;  pi
;  iPi:DOUBLE(0.318309886183791D0), $   ;  1/pi
;  sPi:DOUBLE(1.772453850905516D0), $   ;  sqrt(pi)
;  sPio2:DOUBLE(1.253314137315500D0), $ ;  sqrt(pi/2)
;  sPi2:DOUBLE(0.886226925452758D0), $  ;  sqrt(pi)/2
;  srt:DOUBLE(0.866025403784439D0), $   ;  sqrt(3)/2
;  isrt:DOUBLE(0.577350269189626D0), $ ;  1/sqrt(3)
;  alpha:DOUBLE(1.346773687088598D0), $;  sqrt(pi)/3^(1/4)
;  rtt:DOUBLE(1.732050807568877D0), $   ;  sqrt(3)
;  prea:DOUBLE(0.525037567904332D0), $ ;  3^(1/4)/sqrt(2pi)
;  preb:DOUBLE(1.050075135808664D0), $  ;  3^(1/4)sqrt(2/pi)
;  prec:DOUBLE(0.906899682117109D0), $ ;  pi/2sqrt(3)
;  pred:DOUBLE(2.094395102393195D0), $  ;  2pi/3
;  pree:DOUBLE(0.759835685651593D0), $  ;  3^(-1/4)
;  pref:DOUBLE(1.381976597885342D0), $  ;  sqrt(6/pi)
;  ; the following constants are used for the cube to quaternion hemisphere mapping
;  a:DOUBLE(1.925749019958253D0), $     ; pi^(5/6)/6^(1/6)
;  ap:DOUBLE(2.145029397111025D0), $    ; pi^(2/3)
;  sc:DOUBLE(0.897772786961286D0), $    ; a/ap
;  beta:DOUBLE(0.962874509979126D0), $  ; pi^(5/6)/6^(1/6)/2
;  R1:DOUBLE(1.330670039491469D0), $    ; (3pi/4)^(1/3)
;  r2:DOUBLE(1.414213562373095D0), $    ; sqrt(2)
;  r22:DOUBLE(0.707106781186547D0), $   ; 1/sqrt(2)
;  pi12:DOUBLE(0.261799387799149D0), $  ; pi/12
;  pi8:DOUBLE(0.392699081698724D0), $   ; pi/8
;  prek:DOUBLE(1.643456402972504D0), $  ; R1 2^(1/4)/beta
;  r24:DOUBLE(4.898979485566356D0), $   ; sqrt(24)
;  tfit : DOUBLE([1.0000000000018852D0, -0.5000000002194847D0, $
;  -0.024999992127593126D0, - 0.003928701544781374D0, $
;  -0.0008152701535450438D0, - 0.0002009500426119712D0, $
;  -0.00002397986776071756D0, - 0.00008202868926605841D0, $
;  +0.00012448715042090092D0, - 0.0001749114214822577D0, $
;  +0.0001703481934140054D0, - 0.00012062065004116828D0, $
;  +0.000059719705868660826D0, - 0.00001980756723965647D0, $
;  +0.000003953714684212874D0, - 0.00000036555001439719544D0 ]) }



Rotationlibc
Quatlibc
end ;pro init_rotations
