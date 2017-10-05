% from quaternions to axis-angle pair

function q = qu2ax(qq)

thr = 1e-8;
omega = 2.0 * acos(qq(1));

if ((omega-0.0)<thr) 
  q = [0.0, 0.0, 1.0, 0.0];
else
    
  if ((qq(1)-0.0)<thr)
      q = [qq(2), qq(3), qq(4), pi];
  else
    s =  (qq(1)/abs(qq(1)))/sqrt(qq(2)^2+qq(3)^2+qq(4)^2);
    q = [ qq(2)*s, qq(3)*s, qq(4)*s, omega];
  end
 
end 

% set values very close to 0 as 0
if (abs(q(1))-0)<thr
    q(1)=0;
elseif (abs(q(2))-0)<thr
    q(2)=0;
elseif (abs(q(3))-0)<thr
    q(3)=0;
end