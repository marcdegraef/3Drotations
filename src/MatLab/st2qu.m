% from stereographic vector to quaternion

function q = st2qu(c)
l=sqrt(sum(c.*c));
if l>0
    temp=c/l;
    ax=[temp(1),temp(2),temp(3),4*atan(l)];
    c=cos(ax(4)*0.5);s=sin(ax(4)*0.5);
    q = [c, ax(1)*s, ax(2)*s, ax(3)*s ];
else
    q=[1,0,0,0];
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