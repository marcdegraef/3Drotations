function quatMultiply, q1, q2,P=P
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz1 = SIZE(q1)
  sz2 = SIZE(q2)
  type = LONG(sz1[-2]) > LONG(sz2[-2])
  n1 = ULONG64(sz1[-1]/sz1[1])
  n2 = ULONG64(sz2[-1]/sz2[1])

  n = n1 > n2
  If n1 Eq 1 Then Begin
    n = n2
  Endif
  If n2 Eq 1 Then Begin
    n = n1
  Endif

  q1q2 = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("quatMultiply", /either))

  If (sz1[-2] EQ sz2[-2]) then begin
    trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "quatMultIDLWrap", $
      q1, q2, q1q2, n1, n2, pfac, type)
  ENDIF ELSE IF(sz1[-2] GT sz2[-2]) THEN begin
    trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "quatMultIDLWrap", $
      q1, double(q2), q1q2, n1, n2, pfac, type)
  ENDIF ELSE IF (sz1[-2] LT sz2[-2]) THEN begin 
    trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "quatMultIDLWrap", $
      double(q1), q2, q1q2, n1, n2, pfac, type)
  ENDIF

  return, q1q2
end

pro quatlibunload
  path = FILE_DIRNAME(ROUTINE_FILEPATH("quatMultiply", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"quatLibC.dylib", "quatLibUnload", /unload)
end
