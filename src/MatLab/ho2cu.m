% from homochoric to cubochoric

function q = ho2cu(xyz)

format long
thr = 1e-10;

R1 = (3*pi/4)^(1/3);
aa = (pi^(5/6))*(1/6)^(1/6);
ap = pi^(2/3);
bb = aa/2;
sc = aa/ap;

rs = sqrt(sum(xyz.*xyz));
if ((rs-R1)>thr) 
  q = [0 0 0]; 
  return
end

if (max(abs(xyz))-0.0)<thr 
  q = [0 0 0]; 
  return
end
    
% determine pyramid
p = GetPyramid(xyz);

if (p==1) || (p==2)
    xyz3 = xyz;
elseif (p==3) || (p==4)
    xyz3 = [xyz(2), xyz(3), xyz(1)];
else
    xyz3 = [xyz(3), xyz(1), xyz(2)];
end
% look into MATLAB selectIf    
% select case (p)
%  case (1,2)
%   xyz3 = xyz;
%  case (3,4)
%   xyz3 = [xyz(2), xyz(3), xyz(1)];
%  case (5,6)
%   xyz3 = [xyz(3), xyz(1), xyz(2)];
% end select

% inverse M_3
temp = sqrt( 2*rs/(rs+ abs(xyz3(3)) ) );
xyz2 = [xyz3(1)*temp, xyz3(2)*temp, (abs(xyz3(3))/xyz3(3))*rs*sqrt(pi/6)];

% inverse M_2
qxy = xyz2(1)*xyz2(1) + xyz2(2)*xyz2(2);
sx = 1.0;
if (xyz2(1) ~= 0.0)  
    sx = abs(xyz2(1))/xyz2(1);
end
sy = 1.0;
if (xyz2(2) ~= 0.0)  
    sy = abs(xyz2(2))/xyz2(2);
end

if (qxy ~= 0.0)
   if (abs(xyz2(2)) <= abs(xyz2(1))) 
      q2xy = qxy + xyz2(1)*xyz2(1);
      sq2xy = sqrt(q2xy);
      temp = (bb/sqrt(2)/R1) * sqrt(q2xy*qxy/(q2xy-abs(xyz2(1))*sq2xy));
      tt = (xyz2(2)*xyz2(2)+abs(xyz2(1))*sq2xy)/sqrt(2)/qxy; 
      if (tt > 1.0) 
          tt = 1.0;
      elseif (tt < -1.0) 
          tt = -1.0;
      end
      ac = acos(tt);
      T1inv = temp*sx;
      T2inv = temp*sy*ac/(pi/12);
   else 
      qx2y = qxy + xyz2(2)*xyz2(2);
      sqx2y = sqrt(qx2y);
      temp = (bb/sqrt(2)/R1) * sqrt(qx2y*qxy/(qx2y-abs(xyz2(2))*sqx2y));
      tt = (xyz2(1)*xyz2(1)+abs(xyz2(2))*sqx2y)/sqrt(2)/qxy;
      if (tt > 1.0) 
          tt = 1.0;
      elseif (tt < -1.0) 
          tt = -1.0;
      end
      ac = acos(tt);      
      T1inv = temp*sx*ac/(pi/12);
      T2inv = temp*sy;
   end
else
    T1inv = 0.0;
    T2inv = 0.0;
end
xyz1 = [T1inv, T2inv, xyz2(3)];

% inverse M_1
xyz1 = xyz1/sc;

% reverst the coordinates back to the regular order according to the original pyramid number

if (p==1) || (p==2)
    q = xyz1;
elseif (p==3) || (p==4)
    q = [xyz1(3), xyz1(1), xyz1(2)];
else
    q = [xyz1(2), xyz1(3), xyz1(1)];
end

% set values very close to 0 as 0
if abs(q(1))<thr
    q(1)=0;
end
if abs(q(2))<thr
    q(2)=0;
end
if abs(q(3))<thr
    q(3)=0;
end

