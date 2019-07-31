function quatVector, q, v,P=P
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz1 = SIZE(q)
  sz2 = SIZE(v)
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

  vout = MAKE_ARRAY(3,n, TYPE = type)

  If n1 Eq 1 Then Begin
    q = REBIN(q, 4, n)
  Endif

  If n2 Eq 1 Then Begin
    v = REBIN(v, 3, n)
  Endif

  qvect = q[1:3,*]

  temp = pfac*Crossp_multi( qvect, v)
  temp += REBIN(q[0,*], 3, n)*v
  vout = pfac*Crossp_multi(2.0*qvect, temp)
  vout += v

  q = q[*,0:n1-1]
  v = v[*, 0:n2-1]

  return, vout
end

