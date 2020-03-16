% from Rodrigues vector to quaternions

function q = ro2qu(r)

q = ax2qu(ro2ax(r));

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