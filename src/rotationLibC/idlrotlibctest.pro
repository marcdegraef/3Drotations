Pro Idlrotlibctest

  Init_rotations, 1
  rt = ['ax', 'cu', 'eu', 'ho', 'om', 'qu', 'ro'] ; rotation type
  rl= STRTRIM([  4 ,   3 ,   3 ,   3 ,    9,   4,    4],2) ; rotation length
  seed = 5
  n = LONG(1e6)
  eu = RANDOMU(seed, 3, n, /double)*REBIN([2., 1, 2.]*!DPI*0.99, 3, n)+1e-5
  special_eu = DOUBLE([[0.d, 0.d, 0.d],[!dpi,0,0],[3.7961900794466779d,       1.7749140899322542d,       5.6285878813227015d] ] )
  ; -0.4721362888813019,       0.6151739358901978,       0.6313860416412354,       3.1415926535897931
  ;
  eu = [[eu],[special_eu]]
  ;eu = special_eu
  ;eu = FLOAT(eu)

  ;RESOLVE_ROUTINE, 'rotationlibc', /compile_full, /either
  t = SYSTIME(1)
  PRINT, "eu2: "
  mx = MAX(ABS(Ax2eu(Eu2ax(eu)) - eu))
  PRINT, "    ax: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Cu2eu(Eu2cu(eu)) - eu))
  PRINT, "    cu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ho2eu(Eu2ho(eu)) - eu))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Om2eu(Eu2om(eu)) - eu))
  PRINT, "    om: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Qu2eu(Eu2qu(eu)) - eu))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ro2eu(Eu2ro(eu)) - eu))
  PRINT, "    ro: ", STRTRIM(mx, 2)

  cu = Eu2cu(eu)
  PRINT, "cu2: "
  mx = MAX(ABS(Ax2cu(Cu2ax(cu)) - cu))
  PRINT, "    ax: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ho2cu(Cu2ho(cu)) - cu))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Om2cu(Cu2om(cu)) - cu))
  PRINT, "    om: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Qu2cu(Cu2qu(cu)) - cu))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ro2cu(Cu2ro(cu)) - cu))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  cu = 0
  ax = Eu2ax(eu)
  PRINT, "ax2: "
  mx = MAX(ABS(Ho2ax(Ax2ho(ax)) - ax))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Om2ax(Ax2om(ax)) - ax))
  PRINT, "    om: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Qu2ax(Ax2qu(ax)) - ax))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ro2ax(Ax2ro(ax)) - ax))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  ax = 0
  ho = Eu2ho(eu)
  PRINT, "ho2: "
  mx = MAX(ABS(Om2ho(Ho2om(ho)) - ho))
  PRINT, "    om: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Qu2ho(Ho2qu(ho)) - ho))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ro2ho(Ho2ro(ho)) - ho))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  ho = 0
  om = Eu2om(eu)
  PRINT, "om2: "
  mx = MAX(ABS(Qu2om(Om2qu(om)) - om))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  mx = MAX(ABS(Ro2om(Om2ro(om)) - om))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  om =0
  qu = Eu2qu(eu)

  PRINT, "qu2: "
  mx = MAX(ABS(Ro2qu(Qu2ro(qu)) - qu))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  PRINT, "Time to complete: ", STRTRIM(SYSTIME(1)-t,2)
stop
End

pro marctest 

  ;Init_rotations
  rt = ['ax', 'cu', 'eu', 'ho', 'om', 'qu', 'ro'] ; rotation type
  rl= STRTRIM([  4 ,   3 ,   3 ,   3 ,    9,   4,    4],2) ; rotation length
  seed = 5
  n = LONG(1e5)
  eu = RANDOMU(seed, 3, n, /double)*REBIN([2., 1, 2.]*!DPI*0.99, 3, n)+1e-5
  special_eu = DOUBLE([[0.d, 0.d, 0.d],[!dpi,0,0],[3.7961900794466779d,       1.7749140899322542d,       5.6285878813227015d] ] )
  ; -0.4721362888813019,       0.6151739358901978,       0.6313860416412354,       3.1415926535897931
  ;
  ;eu = [[eu],[special_eu]]
  ;eu = special_eu
  ;n = 3
  ;eu = FLOAT(eu)

  ;RESOLVE_ROUTINE, 'rotationlibc', /compile_full, /either
  t = SYSTIME(1)
  PRINT, "eu2: "
  eu2 = dblarr(3, n)
  for i=0, n-1 do begin
    eu2[*,i] = ax2eu(eu2ax(eu[*,i]))
  end
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    ax: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    eu2[*,i] = cu2eu(eu2cu(eu[*,i]))
  End
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    cu: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    eu2[*,i] = ho2eu(eu2ho(eu[*,i]))
  End
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    eu2[*,i] = om2eu(Eu2om(eu[*,i]))
  End
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    om: ", STRTRIM(mx, 2)
 
  For i=0, n-1 Do Begin
    eu2[*,i] = qu2eu(Eu2qu(eu[*,i]))
  End
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    eu2[*,i] = ro2eu(Eu2ro(eu[*,i]))
  End
  mx = MAX(ABS(eu2 - eu))
  PRINT, "    ro: ", STRTRIM(mx, 2)
 
  ;;;;;;;;;;;;;;;;;;;;;;;;

  
  cu = dblarr(3, n)
  cu2 = dblarr(3,n)
  For i=0, n-1 Do Begin
    cu[*,i] = eu2cu(eu[*,i])
  End
    
  PRINT, "cu2: "
  For i=0, n-1 Do Begin
    cu2[*,i] = ax2cu(cu2ax(cu[*,i]))
  End
  mx = MAX(ABS(cu2 - cu))
  PRINT, "    ax: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    cu2[*,i] = ho2cu(Cu2ho(cu[*,i]))
  End
  mx = MAX(ABS(cu2 - cu))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    cu2[*,i] = om2cu(Cu2om(cu[*,i]))
  End
  mx = MAX(ABS(cu2 - cu))
  PRINT, "    om: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    cu2[*,i] = qu2cu(Cu2qu(cu[*,i]))
  End
  mx = MAX(ABS(cu2 - cu))
  PRINT, "    qu: ", STRTRIM(mx, 2)
 
  For i=0, n-1 Do Begin
    cu2[*,i] = ro2cu(Cu2ro(cu[*,i]))
  End
  mx = MAX(ABS(cu2 - cu))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  
  
  cu =  0
  cu2 = 0
  ax = dblarr(4, n)
  ax2 = ax
  
  For i=0, n-1 Do Begin
    ax[*,i] = Eu2ax(eu[*,i])
  End
  
  
  PRINT, "ax2: "
  For i=0, n-1 Do Begin
    ax2[*,i] = ho2ax(ax2ho(ax[*,i]))
  End
  mx = MAX(ABS(ax2 - ax))
  PRINT, "    ho: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    ax2[*,i] = om2ax(Ax2om(ax[*,i]))
  End
  mx = MAX(ABS(ax2 - ax))
  PRINT, "    om: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    ax2[*,i] = qu2ax(Ax2qu(ax[*,i]))
  End
  mx = MAX(ABS(ax2 - ax))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    ax2[*,i] = ro2ax(Ax2ro(ax[*,i]))
  End
  mx = MAX(ABS(ax2 - ax))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  
  ax = 0
  ax2 = 0
  ho = dblarr(3, n)
  ho2 = ho
  
  For i=0, n-1 Do Begin
    ho[*,i] = Eu2ho(eu[*,i])
  End
  
  
  PRINT, "ho2: "
  For i=0, n-1 Do Begin
    ho2[*,i] = om2ho(ho2om(ho[*,i]))
  End
  mx = MAX(ABS(ho2 - ho))
  PRINT, "    om: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    ho2[*,i] = qu2ho(Ho2qu(ho[*,i]))
  End
  mx = MAX(ABS(ho2 - ho))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    ho2[*,i] = ro2ho(Ho2ro(ho[*,i]))
  End
  mx = MAX(ABS(ho2 - ho))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  
  ho = 0
  ho2 = 0
  
  om = dblarr(3,3,n)
  om2 = dblarr(3,3,n)
  
  For i=0, n-1 Do Begin
    om[*,*,i] = Eu2om(eu[*,i])
  End
  
  PRINT, "om2: "
  For i=0, n-1 Do Begin
    om2[*,*,i] = Qu2om(om2qu(om[*,*,i]))
  End
  mx = MAX(ABS(om2 - om))
  PRINT, "    qu: ", STRTRIM(mx, 2)
  
  For i=0, n-1 Do Begin
    om2[*,*,i] = ro2om(Om2ro(om[*,*,i]))
  End
  mx = MAX(ABS(om2 - om))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  
  om = 0
  om2 = 0
  
  qu = DBLARR(4,n)
  qu2 = dblarr(4,n)

  For i=0, n-1 Do Begin
    qu[*,i] = Eu2qu(eu[*,i])
  End
  

  PRINT, "qu2: "
  For i=0, n-1 Do Begin
    qu2[*,i] = Ro2qu(Qu2ro(qu[*,i]))
  End
  mx = MAX(ABS(qu2 - qu))
  PRINT, "    ro: ", STRTRIM(mx, 2)
  
  Print, ''
  PRINT, "Time to complete: ", STRTRIM(SYSTIME(1)-t,2)

End

