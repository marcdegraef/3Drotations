% from axis-angle pair to Rodrigues vectors

function q = ax2ro(ax)

global epsijk

thr = 1e-7;

if (ax(4)==0.0)
   q = [0.0, 0.0, epsijk, 0.0];
  return
end

q(1:3) =  ax(1:3);

% we need to deal with the 180 degree case
if (abs(ax(4)-pi)<thr) 
  q(4) = Inf;
  return
else
  q(4) = tan(ax(4)*0.5);
end

% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
elseif (abs(q(4))-0)<thr
    q(4)=0;    
end