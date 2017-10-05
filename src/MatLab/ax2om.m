% from axis-angle pair to rotation matrix

function q = ax2om(ax)

global epsijk

thr = 1e-10;

n1 = ax(1);
n2 = ax(2);
n3 = ax(3);
w  = ax(4);

c = cos(w);
s = sin(w);

q = [c+(1-c)*n1^2,     (1-c)*n1*n2+s*n3, (1-c)*n1*n3-s*n2;...
     (1-c)*n1*n2-s*n3, c+(1-c)*n2^2,     (1-c)*n2*n3+s*n1;...
     (1-c)*n1*n3+s*n2, (1-c)*n2*n3-s*n1, c+(1-c)*n3^2];
 
if (epsijk ==1) 
     q = transpose(q);
end
 
for i=1:3
 for j=1:3
   if (abs(q(i,j))< thr) 
        q(i,j) = 0.0;
   end
 end
end