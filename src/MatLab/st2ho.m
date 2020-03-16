% stereographic vector to homochoric vector
function res=st2ho(st)
l=sqrt(sum(st.*st));

if l > 0
    temp=st/l;
    angle=4*atan(l);
    res=temp*(3*(angle-sin(angle))/4)^(1/3);
    
else
    res=[0,0,0];
end

