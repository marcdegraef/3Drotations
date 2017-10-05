% from cubochoric to quaternions

function q = cu2qu(c)

q = ho2qu(cu2ho(c));

% set values very close to 0 as 0
thr = 1e-10;
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
elseif (abs(q(4))-0)<thr
    q(4)=0;
end