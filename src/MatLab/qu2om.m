% from quaternions to rotation matrix

function q = qu2om(qq)

global epsijk

qbar = qq(1)*qq(1)-(qq(2)*qq(2)+qq(3)*qq(3)+qq(4)*qq(4));


q(1,1) = qbar + 2.0*qq(2)*qq(2);
q(2,2) = qbar + 2.0*qq(3)*qq(3);
q(3,3) = qbar + 2.0*qq(4)*qq(4);

q(1,2) = 2.0*(qq(2)*qq(3)-qq(1)*qq(4));
q(2,3) = 2.0*(qq(3)*qq(4)-qq(1)*qq(2));
q(3,1) = 2.0*(qq(4)*qq(2)-qq(1)*qq(3));
q(2,1) = 2.0*(qq(3)*qq(2)+qq(1)*qq(4));
q(3,2) = 2.0*(qq(4)*qq(3)+qq(1)*qq(2));
q(1,3) = 2.0*(qq(2)*qq(4)+qq(1)*qq(3));

if (epsijk ~= 1)
    q = transpose(q);
end

thr = 1e-8;
for i=1:3
  for j=1:3
    if (abs(q(i,j))< thr) 
        q(i,j) = 0.0;
    end
  end
end