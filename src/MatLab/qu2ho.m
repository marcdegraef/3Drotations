% from quaternions to homochoric

function q = qu2ho(qq)

omega = 2.0 * acos(qq(1));
if (omega==0.0)
    q = [ 0.0, 0.0, 0.0 ];
else
    s = 1.0/sqrt(sum(qq(2:4).^2));
    q = qq(2:4) * s;
    f = 0.75 * ( omega - sin(omega) );
    q = q * f^(1/3);
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
