% Rodrigues vector to stereographic vector
function res=ro2st(ro)
res=qu2st(ro2qu(ro));

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

