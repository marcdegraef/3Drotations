function ax2cu, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2cuIDLWrap", $
    ax, cu, n, pfac, type)

  return, cu
end



function ax2eu, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2euIDLWrap", $
    ax, eu, n, pfac, type)

  return, eu
end



function ax2ho, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2hoIDLWrap", $
    ax, ho, n, pfac, type)

  return, ho
end



function ax2om, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2omIDLWrap", $
    ax, om, n, pfac, type)

  return, om
end



function ax2qu, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2quIDLWrap", $
    ax, qu, n, pfac, type)

  return, qu
end



function ax2ro, ax,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ax)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ax2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ax2roIDLWrap", $
    ax, ro, n, pfac, type)

  return, ro
end



function cu2ax, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2axIDLWrap", $
    cu, ax, n, pfac, type)

  return, ax
end



function cu2eu, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2euIDLWrap", $
    cu, eu, n, pfac, type)

  return, eu
end



function cu2ho, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2hoIDLWrap", $
    cu, ho, n, pfac, type)

  return, ho
end



function cu2om, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2omIDLWrap", $
    cu, om, n, pfac, type)

  return, om
end



function cu2qu, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2quIDLWrap", $
    cu, qu, n, pfac, type)

  return, qu
end



function cu2ro, cu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(cu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("cu2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "cu2roIDLWrap", $
    cu, ro, n, pfac, type)

  return, ro
end



function eu2ax, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2axIDLWrap", $
    eu, ax, n, pfac, type)

  return, ax
end



function eu2cu, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2cuIDLWrap", $
    eu, cu, n, pfac, type)

  return, cu
end



function eu2ho, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2hoIDLWrap", $
    eu, ho, n, pfac, type)

  return, ho
end



function eu2om, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2omIDLWrap", $
    eu, om, n, pfac, type)

  return, om
end



function eu2qu, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2quIDLWrap", $
    eu, qu, n, pfac, type)

  return, qu
end



function eu2ro, eu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(eu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("eu2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "eu2roIDLWrap", $
    eu, ro, n, pfac, type)

  return, ro
end



function ho2ax, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2axIDLWrap", $
    ho, ax, n, pfac, type)

  return, ax
end



function ho2cu, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2cuIDLWrap", $
    ho, cu, n, pfac, type)

  return, cu
end



function ho2eu, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2euIDLWrap", $
    ho, eu, n, pfac, type)

  return, eu
end



function ho2om, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2omIDLWrap", $
    ho, om, n, pfac, type)

  return, om
end



function ho2qu, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2quIDLWrap", $
    ho, qu, n, pfac, type)

  return, qu
end



function ho2ro, ho,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ho)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ho2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ho2roIDLWrap", $
    ho, ro, n, pfac, type)

  return, ro
end



function om2ax, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2axIDLWrap", $
    om, ax, n, pfac, type)

  return, ax
end



function om2cu, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2cuIDLWrap", $
    om, cu, n, pfac, type)

  return, cu
end



function om2eu, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2euIDLWrap", $
    om, eu, n, pfac, type)

  return, eu
end



function om2ho, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2hoIDLWrap", $
    om, ho, n, pfac, type)

  return, ho
end



function om2qu, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2quIDLWrap", $
    om, qu, n, pfac, type)

  return, qu
end



function om2ro, om,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(om)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/9l)
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("om2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "om2roIDLWrap", $
    om, ro, n, pfac, type)

  return, ro
end



function qu2ax, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2axIDLWrap", $
    qu, ax, n, pfac, type)

  return, ax
end



function qu2cu, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2cuIDLWrap", $
    qu, cu, n, pfac, type)

  return, cu
end



function qu2eu, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2euIDLWrap", $
    qu, eu, n, pfac, type)

  return, eu
end



function qu2ho, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2hoIDLWrap", $
    qu, ho, n, pfac, type)

  return, ho
end



function qu2om, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2omIDLWrap", $
    qu, om, n, pfac, type)

  return, om
end



function qu2ro, qu,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(qu)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ro = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("qu2ro", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "qu2roIDLWrap", $
    qu, ro, n, pfac, type)

  return, ro
end



function ro2ax, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ax = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2ax", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2axIDLWrap", $
    ro, ax, n, pfac, type)

  return, ax
end



function ro2cu, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  cu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2cu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2cuIDLWrap", $
    ro, cu, n, pfac, type)

  return, cu
end



function ro2eu, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  eu = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2eu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2euIDLWrap", $
    ro, eu, n, pfac, type)

  return, eu
end



function ro2ho, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  ho = MAKE_ARRAY(3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2ho", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2hoIDLWrap", $
    ro, ho, n, pfac, type)

  return, ho
end



function ro2om, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  om = MAKE_ARRAY(3,3,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2om", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2omIDLWrap", $
    ro, om, n, pfac, type)

  return, om
end



function ro2qu, ro,P=P
COMPILE_OPT HIDDEN
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz = SIZE(ro)
  type = LONG(sz[-2])
  n = ULONG64(sz[-1]/sz[1])
  qu = MAKE_ARRAY(4,n, TYPE = type)
  path = FILE_DIRNAME(ROUTINE_FILEPATH("ro2qu", /either))
  trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "ro2quIDLWrap", $
    ro, qu, n, pfac, type)

  return, qu
end



pro rotationlibcunload
path = FILE_DIRNAME(ROUTINE_FILEPATH("rotationlibcunload", /either))
trash =  CALL_EXTERNAL(path+path_sep()+"rotationLibC.dylib", "IDLRotLibUnload", /unload)
end
pro rotationlibc
;dummy proceedure
end
