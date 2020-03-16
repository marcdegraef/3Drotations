% stereographic vector to cubochoric vector
function res=st2cu(st)
l=sqrt(sum(st.*st));

if l > 0
    temp=st/l;
    angle=4*atan(l);
    res=ho2cu(temp*(3*(angle-sin(angle))/4)^(1/3));
    
else
    res=[0,0,0];
end

