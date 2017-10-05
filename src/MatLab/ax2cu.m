% from axis-angle pair to cubochoric

function q = ax2cu(ax)

q = ho2cu(ax2ho(ax));

thr = 1e-10;
% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end