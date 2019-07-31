% from Euler angles to quaternions

function q = eu2qu(eu)

global epsijk
% epsijk = -1;
epsijk

% q = zeros(1,4);

aphi1 = eu(1);
aPhi = eu(2);
aphi2 = eu(3);

sigma = 0.5*(aphi1+aphi2);
delta = 0.5*(aphi1-aphi2);
c = cos(aPhi/2);
s = sin(aPhi/2);

q0 = c*cos(sigma);

% q = [c*cos(sigma); -epsijk*s*cos(delta); -epsijk*s*sin(delta); -epsijk*c*sin(sigma)];

if q0>=0
    q = [c*cos(sigma), -epsijk*s*cos(delta), -epsijk*s*sin(delta), -epsijk*c*sin(sigma)];
else
    q = [-c*cos(sigma), epsijk*s*cos(delta), epsijk*s*sin(delta), epsijk*c*sin(sigma)];
end

% set values very close to 0 as 0
thr = 1e-10;
if (abs(q(1))-0)<thr
    q(1)=0.0;
elseif (abs(q(2))-0)<thr
    q(2)=0.0;
elseif (abs(q(3))-0)<thr
    q(3)=0.0;
elseif (abs(q(4))-0)<thr
    q(4)=0.0;    
end