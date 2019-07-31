% from Rodrigues vector to rotation matrix

function q = ro2om(r)

q = ax2om(ro2ax(r));

thr = 1e-8;
for i=1:3
  for j=1:3
    if (abs(q(i,j))< thr) 
        q(i,j) = 0.0;
    end
  end
end