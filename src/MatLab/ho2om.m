% from homochoric to rotation matrix

function q = ho2om(h)

q = ax2om(ho2ax(h));

thr = 1e-8;
for i=1:3
  for j=1:3
    if (abs(q(i,j))< thr) 
        q(i,j) = 0.0;
    end
  end
end