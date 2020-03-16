% from quaternions to Rodrigues vector

function q = qu2ro(qq)

global epsijk

thr = 1e-10;

q(1:3) = qq(2:4);
q(4) = 0.0;

if (qq(1)<thr)
  q(4) = Inf;
  return
end

s = sqrt(sum(q(1:3).*q(1:3)));
if (s<thr)
  q = [0.0, 0.0, epsijk, 0.0];
  return
else
  t = tan(acos(qq(1)));
  q = [q(1)/s, q(2)/s, q(3)/s, t];
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
if abs(q(4))<thr
    q(4)=0;
end
