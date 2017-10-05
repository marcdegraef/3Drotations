% from rotation matrix to Euler angles

function q = om2eu(om)

thr = 1e-8;

if abs(abs(om(3,3))-1.0)>thr
    
    zeta = 1/sqrt(1-om(3,3)^2);
    q = [atan2(om(3,1)*zeta , -om(3,2)*zeta), acos(om(3,3)), ...
         atan2(om(1,3)*zeta , om(2,3)*zeta)];
    
else
  % we arbitrarily assign the entire angle to phi_1   
    if abs(om(3,3)-1.0)<thr
    
        q = [atan2(om(1,2),om(1,1)),0.0,0.0];
        
    else
    
        q = [-atan2(-om(1,2),om(1,1)),pi,0.0];
    end

end

% reduce Euler angles to definition ranges (and positive values only)
if (q(1)<0.0) 
    q(1) = mod(q(1)+100.0*pi,2.0*pi);
end

if (q(2)<0.0) 
    q(2) = mod(q(2)+100.0*pi,pi);
end

if (q(3)<0.0) 
    q(3) = mod(q(3)+100.0*pi,2.0*pi);
end
