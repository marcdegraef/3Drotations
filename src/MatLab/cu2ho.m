% from cubochoric to homochoric

function q = cu2ho(xyz)

% rs = sqrt(sum(xyz.*xyz));
R1 = (3*pi/4)^(1/3);
aa = ((pi^5)/6)^(1/6);
bb = aa/2;
sc = aa/(pi^(2/3));
prek = R1*(2^0.25)/bb;

% ierr = 0;
if (max(abs(xyz)) > ((pi^(2/3)/2.0)+1e-8)) 
  q = [0.0, 0.0, 0.0];
%   ierr = 1;
  return
end

% determine which pyramid pair the point lies in and copy coordinates in correct order (see paper)
p = GetPyramid(xyz);
if (p==1) || (p==2)
    sXYZ = xyz;
elseif (p==3) || (p==4)
    sXYZ = [xyz(2), xyz(3), xyz(1)];
else
    sXYZ = [xyz(3), xyz(1), xyz(2)];
end
% select case (p)
%  case (1,2)
%   sXYZ = xyz
%  case (3,4)
%   sXYZ = (/ xyz(2), xyz(3), xyz(1) /)
%  case (5,6)
%   sXYZ = (/ xyz(3), xyz(1), xyz(2) /)
% end select

% scale by grid parameter ratio sc
XYZ = sc * sXYZ;

% transform to the sphere grid via the curved square, and intercept the zero point
if (max(abs(XYZ))== 0.0)
  LamXYZ = [0.0, 0.0, 0.0];
else
% intercept all the points along the z-axis
 if (max(abs(XYZ(1:2)))== 0.0)
    LamXYZ = [0.0, 0.0, sqrt(6/pi)*XYZ(3)];
 else  % this is a general grid point
    if (abs(XYZ(2))<= abs(XYZ(1)))
      c = cos((pi/12)*XYZ(2)/XYZ(1));
      s = sin((pi/12)*XYZ(2)/XYZ(1));
      temp = prek * XYZ(1) / sqrt(sqrt(2)-c);
      T1 = (sqrt(2)*c - 1.0) * temp;
      T2 = sqrt(2) * s * temp;
    else
      c = cos((pi/12) * XYZ(1)/XYZ(2));
      s = sin((pi/12) * XYZ(1)/XYZ(2));
      temp = prek * XYZ(2) / sqrt(sqrt(2)-c);
      T1 = sqrt(2) * s * temp;
      T2 = (sqrt(2)*c - 1.0) * temp;
    end 

% transform to sphere grid (inverse Lambert)
% [note that there is no need to worry about dividing by zero, since XYZ(3) can not become zero]
    c = T1^2+T2^2;
    s = pi*c/(24.0*XYZ(3)^2);
    c = sqrt(pi) * c / sqrt(24) / XYZ(3);
    q = sqrt( 1.0 - s );
    LamXYZ = [T1*q, T2*q, sqrt(6/pi)*XYZ(3)-c];
  end
end

% reverse the coordinates back to the regular order according to the original pyramid number
if (p==1) || (p==2)
    q = LamXYZ;
elseif (p==3) || (p==4)
    q = [LamXYZ(3), LamXYZ(1), LamXYZ(2)];
else
    q = [LamXYZ(2), LamXYZ(3), LamXYZ(1)];
end

thr = 1e-10;
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