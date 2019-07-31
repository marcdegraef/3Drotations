function quatMultiply, q1, q2,P=P
  IF KEYWORD_SET(P) THEN pfac = LONG(P GE 0) - LONG(P LT 0) ELSE pfac = LONG(!ROTLIB.p)
  sz1 = SIZE(q1)
  sz2 = SIZE(q2)
  type = LONG(sz1[-2]) > LONG(sz2[-2]) ; check float or double
  n1 = ULONG64(sz1[-1]/sz1[1])
  n2 = ULONG64(sz2[-1]/sz2[1])

  n = n1 > n2
  If n1 Eq 1 Then Begin
    n = n2
  Endif
  If n2 Eq 1 Then Begin
    n = n1
  Endif

  If n1 Eq 1 Then Begin
    q1 = REBIN(q1, 4, n)
  Endif

  If n2 Eq 1 Then Begin
    q2 = REBIN(q2, 4, n)
  Endif

  q1q2 = MAKE_ARRAY(4,n, TYPE = type)

  q1q2[0,*] = q1[0,*]*q2[0,*]-(TOTAL(q1[1:3,*]*q2[1:3,*], 1))
  q1q2[1:3,*]  = REBIN(q1[0,*], 3, n)*q2[1:3,*]
  q1q2[1:3,*] += REBIN(q2[0,*], 3, n)*q1[1:3,*]


  q1q2[1:3,*] += pfac*[ q1[2,*]*q2[3,*] - q1[3,*]*q2[2,*], $
    q1[3,*]*q2[1,*] - q1[1,*]*q2[3,*], $
    q1[1,*]*q2[2,*] - q1[2,*]*q2[1,*]]


  q1 = q1[*, 0:n1-1]
  q2 = q2[*, 0:n2-1]

  RETURN, q1q2
end

