% axis-angle pair to stereographic vector
function res=ax2st(ax)
res=qu2st(ax2qu(ax));

thr = 1e-10;
% set values very close to 0 as 0
if abs(res(1))<thr
    res(1)=0;
end
if abs(res(2))<thr
    res(2)=0;
end

if abs(res(3))<thr
    res(3)=0;
end

