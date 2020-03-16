% from rotation matrix to quaternions

function q = om2qu(om)

global epsijk

thr = 1e-10;

s = 1+om(1,1)+om(2,2)+om(3,3);
if abs(s)<thr
    s=0;
end
q0 = 0.5*sqrt(s);

s = 1+om(1,1)-om(2,2)-om(3,3);
if abs(s)<thr
    s=0;
end
q1 = 0.5*sqrt(s);

s = 1-om(1,1)+om(2,2)-om(3,3);
if abs(s)<thr
    s=0;
end
q2 = 0.5*sqrt(s);

s = 1-om(1,1)-om(2,2)+om(3,3);
if abs(s)<thr
    s=0;
end
q3 = 0.5*sqrt(s);

% verify the signs (q0 always positive)
if epsijk == 1
    if om(3,2)<om(2,3)
       q1 = -epsijk*q1;
    end
    if om(1,3)<om(3,1)
       q2 = -epsijk*q2;
    end
    if om(2,1)<om(1,2)
       q3 = -epsijk*q3;
    end
end

% normalization
magq = sqrt(q0^2+q1^2+q2^2+q3^2);
if magq ~= 0.0
   q = [q0,q1,q2,q3]/magq;
end

% ! we need to do a quick test here to make sure that the 
% ! sign of the vector part is the same as that of the 
% ! corresponding vector in the axis-angle representation;
% ! these two can end up being different, presumably due to rounding 
% ! issues, but this needs to be further analyzed...
% ! This adds a little bit of computation overhead but for now it
% ! is the easiest way to make sure the signs are correct.

oax = om2ax(om);
if (oax(1)*q(2)<0.0) 
    q(2) = -q(2);
end
if (oax(2)*q(3)<0.0) 
    q(3) = -q(3);
end
if (oax(3)*q(4)<0.0) 
    q(4) = -q(4);
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