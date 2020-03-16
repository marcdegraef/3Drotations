% cubochoric vector to stereographic vector
function res=cu2st(cu)
res=qu2st(cu2qu(cu));

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