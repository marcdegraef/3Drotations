% stereographic vector to axis-angle pair

function res=st2ax(st)
l=sqrt(sum(st.*st));
thr = 1e-10;
if l > 0 
    temp=st/l;
    if abs(l-1)<thr
        res=[temp(1),temp(2), temp(3), pi];
    else
        res=[temp(1),temp(2), temp(3), 4*atan(l)];
    end
else
    res = [0,0,1,0];
   
end
