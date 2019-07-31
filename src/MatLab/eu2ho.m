% from Euler angles to homochoric

function q = eu2ho(eu)

q = ax2ho(eu2ax(eu));

thr = 1e-10;
% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end
