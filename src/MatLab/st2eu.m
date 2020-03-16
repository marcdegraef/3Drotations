% stereographic vector to euler angles

function res=st2eu(st)
l=sqrt(sum(st.*st));
thr = 1e-10;
if l > 0 
    temp=st/l;
    if abs(l-1)<thr
        ax=[temp(1),temp(2), temp(3), pi];
    else
        ax=[temp(1),temp(2), temp(3), 4*atan(l)];
    end
    res=ax2eu(ax);
else
    res=[0,0,0];
end
