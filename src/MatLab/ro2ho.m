% from Rodrigues vector to homochoric

function q = ro2ho(r)

rv = sum(r(1:3).*r(1:3));

if (rv==0.0)
    q = [ 0.0, 0.0, 0.0 ];
    return
end

if (r(4)==Inf)
   f = 0.75*pi;
else
   omega = 2.0*atan(r(4));
   f = 0.75*(omega - sin(omega));
end

q(1:3) = r(1:3) * f^(1/3);

% set values very close to 0 as 0
thr = 1e-8;
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end