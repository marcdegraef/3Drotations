% from cubochoric to rotation matrix

function q = cu2om(c)

q = ho2om(cu2ho(c));

thr = 1e-8;
for i=1:3
  for j=1:3
    if (abs(q(i,j))< thr) 
        q(i,j) = 0.0;
    end
  end
end