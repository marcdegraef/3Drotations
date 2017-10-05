% from Euler angles to Rodrigues vector

function q = eu2ro(eu)

global epsijk
% epsijk = -1;

thr = 1e-10;

% first go to the axis-angle representation
q = eu2ax(eu);

% then adjust the fourth component to be tan(omega/2)
t = q(4);
if (abs(t-pi)<thr)
  q(4) = Inf;
  return
end
 
if (abs(t-0)<thr) 
  q = [0.0, 0.0, epsijk, 0.0];
else
  q(4) = tan(t*0.5);
end
