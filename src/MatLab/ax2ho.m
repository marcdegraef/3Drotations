% from axis-angle pair to homochoric

function q = ax2ho(ax)

f = 0.75 * ( ax(4) - sin(ax(4)) );
f = f^(1/3);

q = ax(1:3) * f;

thr = 1e-10;
% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end