% from Rodrigues vector to axis-angle pair

function q = ro2ax(r)

ta = r(4);
thr = 1e-10;
if (ta<thr) 
  q = [0.0, 0.0, 1.0, 0.0];
  return
end

if (ta==Inf)
  q = [r(1), r(2), r(3), pi];
else
  angle = 2.0*atan(ta);
  ta = 1.0/sqrt(sum(r(1:3).*r(1:3)));
  q = [ r(1)*ta, r(2)*ta, r(3)*ta, angle];
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