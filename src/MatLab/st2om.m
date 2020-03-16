% stereographic vector to orientation matrix

function res=st2om(st)
l=sqrt(sum(st.*st));
thr = 1e-10;
if l > 0 
    temp=st/l;
    if abs(l-1)<thr
        ax=[temp(1),temp(2), temp(3), pi];
    else
        ax=[temp(1),temp(2), temp(3), 4*atan(l)];
    end
    res=ax2om(ax);
else
    res = eye(3);
   
end
