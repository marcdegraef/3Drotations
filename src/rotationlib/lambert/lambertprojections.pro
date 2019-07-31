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
; Original code: CTEMsoft2013:Lambert.f90
;--------------------------------------------------------------------------
;
; MODULE: Lambert
;
;> @author Marc De Graef, Carnegie Mellon University
;
;> @brief everything that has to do with the modified Lambert projections
;
;> @details This module contains a number of projection functions for the modified
;> Lambert projection between square lattice and 2D hemisphere, hexagonal lattice
;> and 2D hemisphere, as well as the more complex mapping between a 3D cubic grid
;> and the unit quaternion hemisphere with positive scalar comoonent.  In addition, there
;> are some other projections, such as the stereographic one.  Each function is named
;> by the projection, the dimensionality of the starting grid, and the forward or inverse
;> character.  For each function, there is also a single precision and a double precision
;> version, but we use the interface formalism to have only a single call.  The Forward
;> mapping is taken to be the one from the simple grid to the curved grid.  Since the module
;> deals with various grids, we also add a few functions/subroutines that apply symmetry
;> operations on those grids.
;>
;> To use any of these routines, one must first call the InitLambertParameters routine
;> to initialize a bunch of constants.
;
;> @date 7/10/13   MDG 1.0 original
;> @date 7/12/13   MDG 1.1 added forward cube to ball to quaternion mappings
;> @date 8/01/13   MDG 1.2 added standard Lambert projection
;> @date 8/12/13   MDG 1.3 added inverse Lambert projections for Ball to Cube
;> @date 9/20/13   MDG 1.4 added ApplyLaueSymmetry
;> @date 3/11/15   MDG 2.0 selected code converted to IDL
;> @date 4/28/15   DJR 2.1 Rewrote to work with IDL arrays
;--------------------------------------------------------------------------


;--------------------------------------------------------------------------
; the functions below deal with the cubic grid to the 3D ball projections
;
; all derivations and equations can be found in
;
; D. Rosca, A. Morawiec, and M. De Graef. “A new method of constructing a grid in the space of
; 3D rotations and its applications to texture analysis”. Modeling and Simulations in Materials
; Science and Engineering 22, 075013 (2014)
;--------------------------------------------------------------------------


;--------------------------------------------------------------------------
;
; FUNCTION: GetPyramid
;
;> @author Marc De Graef, Carnegie Mellon University
;
;> @brief determine to which pyramid a point in a cubic grid belongs
;
;> @param xyz 3D coordinates to be considered
;
;> @date 11/21/12 MDG 1.0 original
;> @date 03/11/15 MDG 2.0 IDL conversion
;--------------------------------------------------------------------------
FUNCTION LambertConstants

    LPs = {LambertParametersType, $
    Pi:DOUBLE(3.141592653589793D0), $    ;  pi
    iPi:DOUBLE(0.318309886183791D0), $   ;  1/pi
    sPi:DOUBLE(1.772453850905516D0), $   ;  sqrt(pi)
    sPio2:DOUBLE(1.253314137315500D0), $ ;  sqrt(pi/2)
    sPi2:DOUBLE(0.886226925452758D0), $  ;  sqrt(pi)/2
    srt:DOUBLE(0.866025403784439D0), $   ;  sqrt(3)/2
    isrt:DOUBLE(0.577350269189626D0), $ ;  1/sqrt(3)
    alpha:DOUBLE(1.346773687088598D0), $;  sqrt(pi)/3^(1/4)
    rtt:DOUBLE(1.732050807568877D0), $   ;  sqrt(3)
    prea:DOUBLE(0.525037567904332D0), $ ;  3^(1/4)/sqrt(2pi)
    preb:DOUBLE(1.050075135808664D0), $  ;  3^(1/4)sqrt(2/pi)
    prec:DOUBLE(0.906899682117109D0), $ ;  pi/2sqrt(3)
    pred:DOUBLE(2.094395102393195D0), $  ;  2pi/3
    pree:DOUBLE(0.759835685651593D0), $  ;  3^(-1/4)
    pref:DOUBLE(1.381976597885342D0), $  ;  sqrt(6/pi)
    ; the following constants are used for the cube to quaternion hemisphere mapping
    a:DOUBLE(1.925749019958253D0), $     ; pi^(5/6)/6^(1/6)
    ap:DOUBLE(2.145029397111025D0), $    ; pi^(2/3)
    sc:DOUBLE(0.897772786961286D0), $    ; a/ap
    beta:DOUBLE(0.962874509979126D0), $  ; pi^(5/6)/6^(1/6)/2
    R1:DOUBLE(1.330670039491469D0), $    ; (3pi/4)^(1/3)
    r2:DOUBLE(1.414213562373095D0), $    ; sqrt(2)
    r22:DOUBLE(0.707106781186547D0), $   ; 1/sqrt(2)
    pi12:DOUBLE(0.261799387799149D0), $  ; pi/12
    pi8:DOUBLE(0.392699081698724D0), $   ; pi/8
    prek:DOUBLE(1.643456402972504D0), $  ; R1 2^(1/4)/beta
    r24:DOUBLE(4.898979485566356D0), $   ; sqrt(24)
    tfit : DOUBLE([1.0000000000018852D0, -0.5000000002194847D0, $
    -0.024999992127593126D0, - 0.003928701544781374D0, $
    -0.0008152701535450438D0, - 0.0002009500426119712D0, $
    -0.00002397986776071756D0, - 0.00008202868926605841D0, $
    +0.00012448715042090092D0, - 0.0001749114214822577D0, $
    +0.0001703481934140054D0, - 0.00012062065004116828D0, $
    +0.000059719705868660826D0, - 0.00001980756723965647D0, $
    +0.000003953714684212874D0, - 0.00000036555001439719544D0 ]) }
    
    
    Return, LPs
END

FUNCTION Getpyramid,Xyz

  n = N_ELEMENTS(xyz)/3

  p = LONARR(n)

  p += 1 * ((ABS(xyz[0,*]) LE xyz[2,*]) AND (ABS(xyz[1,*]) LE xyz[2,*]))
  p += 2 * ((ABS(xyz[0,*]) LE -xyz[2,*]) AND (ABS(xyz[1,*]) LE -xyz[2,*]))
  p += 3 * ((ABS(xyz[2,*]) LE xyz[0,*]) AND (ABS(xyz[1,*]) LE xyz[0,*]))
  P += 4 * ((ABS(xyz[2,*]) LE -xyz[0,*]) AND (ABS(xyz[1,*]) LE -xyz[0,*]))
  p += 5 * ((ABS(xyz[0,*]) LE xyz[1,*]) AND (ABS(xyz[2,*]) LE xyz[1,*]))
  P += 6 * ((ABS(xyz[0,*]) LE -xyz[1,*]) AND (ABS(xyz[2,*]) LE -xyz[1,*]))

  RETURN, p

END ;function GetPyramid

;--------------------------------------------------------------------------
;
; FUNCTION: Lambert3DCubeToBall
;
;> @author Marc De Graef, Carnegie Mellon University
;
;> @brief map from 3D cubic grid to 3D ball
;
;> @param xyzin 3D coordinates to be considered
;> @param ierr error flag 0 = OK, 1 =
;
;> @date 7/12/13  MDG 1.0 original
;> @date 7/07/14  MDG 2.0 correction to cube edge length check
;> @date 3/11/15  MDG 3.0 IDL conversion
;--------------------------------------------------------------------------
FUNCTION Lambert3dcubetoball,xyzin,ierr

  ;COMMON rotationcommon, LPs, epsijk
  LPs = LambertConstants()
  
  n = N_ELEMENTS(xyzin)/3
  
  lamXYZ = DBLARR(3, n)

  eps = 1.D-8
  ierr = 0


  IF (MAX(ABS(xyzin)) GT (LPS.ap/2.D0+eps)) THEN BEGIN
    res = REPLICATE(0.D0,3)
    ierr = 1
    RETURN,res
  END

  ; determine which pyramid pair the point lies in and copy coordinates in correct order (see paper)

  p = Getpyramid(xyzin)
  shiftindx = [[0,1,2], [1,2,0], [2, 0, 1]]
  p = (LONG(p) + 1)/2 -1 ; +/- z -> 0, +/-x -> 1, +/- y -> 2
  indx = REBIN(LINDGEN(1,n)*3, 3, n)
  indxIn = indx+shiftindx[*,p]
  indxIn = REFORM(indxIn, n*3l)
  sXYZ = xyzin[indxIn]
  sXYZ = reform(sXYZ, 3, n)
  ;IF ((p EQ 1) OR (p EQ 2)) THEN sXYZ = xyzin
  ;IF ((p EQ 3) OR (p EQ 4)) THEN sXYZ = SHIFT(xyzin,-1)
  ;IF ((p EQ 5) OR (p EQ 6)) THEN sXYZ = SHIFT(xyzin,+1)

  ; scale by grid parameter ratio sc
  XYZ = LPs.sc * sXYZ

  whZero = WHERE(  MAX(ABS(XYZ[0:1, *]), dim = 1) EQ 0.0, count, complement=whNZero, ncomplement = ncount)

  IF count GT 0 THEN $
    lamXYZ[2, whZero] = LPs.pref * XYZ[2, whZero]

  IF ncount GT 0 THEN BEGIN
   
    test = ABS(XYZ[1,whNZero]) LE  ABS(XYZ[0,whNZero])
    ntest = Double(test EQ 0)
    test = Double(test)
    x = XYZ[0,whNZero] * test + XYZ[1,whNZero] * ntest
    y = XYZ[1,whNZero] * test + XYZ[0,whNZero] * ntest
    z = XYZ[2,whNZero]
      
    q = LPs.pi12 * y/x
    c = COS(q)
    s = SIN(q)
    
    q = LPs.prek * x / sqrt(LPs.r2 - c)
    T1p = (LPs.r2 * c - 1.0D) * q
    T2p = LPs.r2 * s * q

    T1 = T1p*test + T2p*ntest
    T2 = T2p*test + T1p*ntest
    
    c = T1^2+T2^2
    s = !DPi * c/(24.D0*z^2)
 
    c = LPs.sPi * c / LPs.r24 / z
    q = SQRT( 1.D0 - s )
    
    lamXYZ[0,whNZero] =  T1 * q
    lamXYZ[1,whNZero] = T2 * q
    lamXYZ[2,whNZero] = LPs.pref * z - c 

  ENDIF

  ;;;;;;

  ; reverse the coordinates back to the regular order according to the original pyramid number
  shiftindx2 = [[0,1,2], [2, 0, 1], [1,2,0]]
  indxOut = indx+shiftindx2[*,p]
  indxOut = REFORM(indxOut, n*3l)
  lamXYZ = lamXYZ[indxOut]
  lamXYZ = reform(lamXYZ, 3, n)

  RETURN, lamXYZ
END ;function Lambert3DCubeToBall

;--------------------------------------------------------------------------
;
; FUNCTION: Lambert3DBallToCube
;
;> @author Marc De Graef, Carnegie Mellon University
;
;> @brief map from 3D ball to 3D cubic grid
;
;> @param xyz 3D coordinates to be considered (single precision)
;> @param ierr error flag 0 = OK, 1 =
;
;> @date 7/12/13  MDG 1.0 original
;> @date 8/12/14  MDG 1.1 fixed acos() problem
;> @date 3/11/15  MDG 2.0 IDL conversion
;--------------------------------------------------------------------------
FUNCTION Lambert3dballtocube,xyz,ierr

  ;COMMON rotationcommon, LPs, epsijk
  LPs = LambertConstants()
  
  ierr = 0
  eps = 1.d-12
  n = N_ELEMENTS(xyz)/3

  rs = SQRT(TOTAL(xyz*xyz, 1, /double))
  
  IF (max(rs) GT LPs.R1) THEN BEGIN
    res = REPLICATE(0.D0,3)
    ierr = 1
    RETURN,res
  END

  ;IF (MAX(ABS(xyz)) EQ 0.D0) THEN BEGIN
  ;  res = REPLICATE(0.D0,3)
  ;  RETURN, res
  ;END

  ; determine pyramid
  p = Getpyramid(xyz)
  shiftindx = [[0,1,2], [1,2,0], [2, 0, 1]]
  p = (LONG(p) + 1)/2 -1 ; +/- z -> 0, +/-x -> 1, +/- y -> 2
  indx = REBIN(LINDGEN(1,n)*3, 3, n)
  indxIn = indx+shiftindx[*,p]
  indxIn = REFORM(indxIn, n*3l)
  xyz3 = xyz[indxIn]
  xyz3 = REFORM(xyz3, 3, n)
  
  ;IF ((p EQ 1) OR (p EQ 2)) THEN xyz3 = xyz
  ;IF ((p EQ 3) OR (p EQ 4)) THEN xyz3 = SHIFT(xyz,-1)
  ;IF ((p EQ 5) OR (p EQ 6)) THEN xyz3 = SHIFT(xyz,+1)

  ; inverse M_3
  
  
  q = SQRT( 2.D0*rs/(rs+ABS(xyz3[2,*]) + eps) )
  xyz2 = double(xyz3)
  xyz2[0,*] = xyz3[0, *] * q
  xyz2[1,*] = xyz3[1, *] * q
  xyz2[2,*] =  (double(xyz3[2,*] GE 0) - double(xyz3[2,*] LT 0)) * rs / LPs.pref 

  ; inverse M_2
  qxy = total(xyz2[0:1,*]^2, 1, /double)
  
  whZero = WHERE( qxy EQ 0.0, count, complement=whNZero, ncomplement = ncount)
  ;T1inv = dblarr(n)
  ;T2inv = dblarr(n)
  xyz1 = dblarr(3, n)
  If count GT 0 THEN Begin
    xyz1[0:1,whZero] = 0.0D
  Endif
  
  If ncount GT 0 THEN BEGIN
    test = (ABS(xyz2[1,whNZero]) LE ABS(xyz2[0,whNZero]))
    ntest = double(test EQ 0)
    test = double(test)
    x = test*xyz2[0,whNZero] + ntest*xyz2[1,whNZero]
    y = test*xyz2[1,whNZero] + ntest*xyz2[0,whNZero]
    
    q2xy = qxy[whNZero] + x*x
    sq2xy = sqrt(q2xy)
    
    q = (LPs.beta/LPs.r2/LPs.R1) * SQRT( q2xy*qxy[whNZero]/(q2xy - ABS(x)*sq2xy ))
    tt = (y*y + ABS(x)*sq2xy)/LPs.r2/qxy[whNZero]
    tt <= 1.0d
    tt >= -1.0d
    ac = ACOS(tt)
    
    sx = DOUBLE(x GE 0.0d) - DOUBLE(x LT 0.0d)
    sy = DOUBLE(y GE 0.0d) - DOUBLE(y LT 0.0d)
    
    T1inv_p = q * sx
    T2inv_p = q * sy * ac/LPs.pi12
    
    T1inv = T1inv_p*test + T2inv_p * ntest
    T2inv = T2inv_p*test + T1inv_p * ntest
    xyz1[0,whNZero] = T1inv
    xyz1[1,whNZero] = T2inv
  Endif
  
  xyz1[2,*] = xyz2[2,*]
;  ;;;;;;;;;;;;;;;;;;;;
;    IF (ABS(xyz2[1]) LE ABS(xyz2[0])) THEN BEGIN
;      q2xy = qxy + xyz2[0]*xyz2[0]
;      sq2xy = SQRT(q2xy)
;      q = (LPs.beta/LPs.r2/LPs.R1) * SQRT(q2xy*qxy/(q2xy-ABS(xyz2[0])*sq2xy))
;      tt = (xyz2[1]*xyz2[1]+ABS(xyz2[0])*sq2xy)/LPs.r2/qxy
;      IF (tt GT 1.D0) THEN tt = 1.D0
;      IF (tt LT -1.D0) THEN tt = -1.D0
;      ac = ACOS(tt)
;      T1inv = q * sx
;      T2inv = q * sy * ac/LPs.pi12
;    END ELSE BEGIN
;      qx2y = qxy + xyz2[1]*xyz2[1]
;      sqx2y = SQRT(qx2y)
;      q = (LPs.beta/LPs.r2/LPs.R1) * SQRT(qx2y*qxy/(qx2y-ABS(xyz2[1])*sqx2y))
;      tt = (xyz2[0]*xyz2[0]+ABS(xyz2[1])*sqx2y)/LPs.r2/qxy
;      IF (tt GT 1.D0) THEN tt = 1.D0
;      IF (tt LT -1.D0) THEN tt = -1.D0
;      ac = ACOS(tt)
;      T1inv = q * sx * ac/LPs.pi12
;      T2inv = q * sy
;    END


  ; inverse M_1
  xyz1 /= LPs.sc

  ; reverst the coordinates back to the regular order according to the original pyramid number
  shiftindx2 = [[0,1,2], [2, 0, 1], [1,2,0]]
  indxOut = indx+shiftindx2[*,p]
  indxOut = REFORM(indxOut, n*3l)
  xyz1 = xyz1[indxOut]
  xyz1 = REFORM(xyz1, 3, n)
  
  
  ;IF ((p EQ 1) OR (p EQ 2)) THEN res = xyz1
  ;IF ((p EQ 3) OR (p EQ 4)) THEN res = SHIFT(xyz1,+1)
  ;IF ((p EQ 5) OR (p EQ 6)) THEN res = SHIFT(xyz1,-1)

  RETURN,xyz1
END ;function Lambert3DBallToCube


PRO Lambertprojections,dummy

END
