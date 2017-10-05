% from homochoric to Rodrigues vector

function q = ho2ro(h)

q = ax2ro(ho2ax(h));

% set values very close to 0 as 0
thr = 1e-8;
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end
