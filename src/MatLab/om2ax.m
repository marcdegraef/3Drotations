% from rotation matrix to axis-angle pair

function q = om2ax(om)

global epsijk


q = zeros(1,4);
thr = 1e-10;

% first get the rotation angle
t = 0.5*(om(1,1)+om(2,2)+om(3,3) - 1.0);

if t>1.0 
    t = 1.0;
elseif t<-1.0
    t = -1.0;
end

q(4) = acos(t);

if (q(4)==0.0)
    q(1:3) = [0.0, 0.0, 1.0];
    return
else
    % find eigenvectors V and eigenvalues W of the rotation matrix
    [V,W] = eig(om);
    for i = 1:3
        
        if ((abs(real(W(i,i))-1.0)<thr) && (abs(imag(W(i,i)))<thr))
            q(1:3) = V(:,i);
            % change sign 
            % matlab chose descending order for same eigenvector value
            % eg. if v1=-v2, it would choose v1=-1 and v2=1,
            % need to change to v1=1 and v2=-1.
            if q(1)<0
                q(1:3) = -q(1:3);
            end
            
            if ((om(2,3)-om(3,2))~=0.0) 
                s = sign(-epsijk*(om(2,3)-om(3,2)));
                q(1) = s*abs(q(1));
            end
            if ((om(3,1)-om(1,3))~=0.0) 
                s = sign(-epsijk*(om(3,1)-om(1,3)));
                q(2) = s*abs(q(2));
            end
            if ((om(1,2)-om(2,1))~=0.0) 
                s = sign(-epsijk*(om(1,2)-om(2,1)));
                q(3) = s*abs(q(3));
            end
            return
        end
    end
    
end
