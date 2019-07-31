% from homochoric to axis-angle pair

function q = ho2ax(h)

          
thr = 1e-8;
tfit = [+1.0000000000018852, -0.5000000002194847, ... 
        -0.024999992127593126, - 0.003928701544781374, ...
        -0.0008152701535450438, - 0.0002009500426119712, ... 
        -0.00002397986776071756, - 0.00008202868926605841, ... 
        +0.00012448715042090092, - 0.0001749114214822577, ...
        +0.0001703481934140054, - 0.00012062065004116828, ...
        +0.000059719705868660826, - 0.00001980756723965647, ... 
        +0.000003953714684212874, - 0.00000036555001439719544];

% normalize xyz and store the magnitude
hmag = sum(h.*h);
if (hmag == 0.0) 
  q = [0.0, 0.0, 1.0, 0.0];
else
  hm = hmag;
  hn = h/sqrt(hmag);

 %convert the magnitude to the rotation angle
  s = tfit(1) + tfit(2) * hmag;
  for i = 3:16
    hm = hm*hmag;
    s = s + tfit(i) * hm;
  end

  s = 2.0*acos(s);
  if (abs(s-pi) < thr)
   q = [hn(1), hn(2), hn(3), pi];
  else
   q = [hn(1), hn(2), hn(3), s];
  end
  
end 

% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end