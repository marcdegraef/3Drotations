% from Euler angles to axis-angle pair

function q = eu2ax(eu)

global epsijk
thr = 1e-10;

aphi1 = eu(1);
aPhi = eu(2);
aphi2 = eu(3);

t     = tan(aPhi/2);
sigma = (aphi1+aphi2)/2;
delta = (aphi1-aphi2)/2;
tau   = sqrt(t^2+(sin(sigma))^2);
% alpha = 2*atan(tau);

if (abs(sigma-pi*0.5)<=thr)   % Infinity 
  alpha = pi;
else
  alpha = 2.0 * atan(tau/cos(sigma));
end 

if (abs(alpha)<thr) 
 % return a default identity axis-angle pair
        q = [ 0.0, 0.0, 1.0, 0.0 ];
else
 % passive axis-angle pair so a minus sign in front
        q(1:3) = - epsijk * [ t*cos(delta), t*sin(delta), sin(sigma) ] / tau;
        q(4) = alpha;
end

% make sure alpha is positive
if (alpha<0.0) 
    q = -q;
end

% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end