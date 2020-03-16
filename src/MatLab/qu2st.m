% from normalized quaternion to stereographic vector

function res=qu2st(c)

res=c(2:4);
thr=10^(-8);

if abs(c(1))>thr
res=res/(1+c(1));
end

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
