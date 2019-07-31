function resultorientations = rotation(aa,inputmethod)

% use double-precision accuracy
% (single-precision accuracy may cause some errors when there's an Infinity value in the presentation)
format long
%
% inputs: aa          - input orientation [angle values in DEGREES]
%         inputmethod - in which presentation aa is
%                       Euler angle 'eu', Rotation matrix 'om', Axis-angle pair
%                       'ax', Rodrigues-Frank vector 'ro', Quaternion 'qu',
%                       Homochoric vector 'ho' or Cubochoric vector 'co'
% outputs: resEu - present in Euler angle
%          resOm - present in Rotation matrix form
%          resAx - present in Axis-angle pair [n;angle]
%          resRo - present in Rodrigues-Frank vector
%          resQu - present in Quaternion
%          resHo - present in Homochoric vector
%          resCu - present in Cubochoric vector
%          [angle values in DEGREES]
%
% set -1 in brackets for an alternative way of doing things; 
% set 1 for the the Morawiec version
setGlobal_epsijk(-1);
%  In the first case, epsijk=-1, the rotation 120@[111] will result in 
%  an axis angle pair of [111], 2pi/3.  In the second case, epsijk=+1, the axis-angle 
%  pair will be -[111], 2pi/3.  In all cases, the rotations are interpreted
%  in the passive sense. For an in-depth explanation, please refer to the
%  rotations tutorial paper. These changes propagate to where quaternions and rotations in general are used.
%  [ref] 
%
% Example:
% Given a set of Euler angles, [270, 180, 360] degrees, what are the
% equivalent presentations in other spaces?
%
% results = rotation([270,180,360],'eu')
% Using alternative way.
% epsijk =
%     -1
% results = 
%
%         EulerAngle: [270 180 360]
%     RotationMatrix: [ 0  -1   0; -1   0   0; 0   0  -1]
%      AxisAnglePair: [0.707106781186548 -0.707106781186547 0 180]
%    RodriguesVector: [0.707106781186548 -0.707106781186547 0 Inf]
%         Quaternion: [0 0.707106781186548 -0.707106781186548 0]
%         Homochoric: [0.940925808446189 -0.940925808446188 0]
%         Cubochoric: [1.072514698555513 -1.072514698555513 0]
%
% NOTE: The Rodrigues vector is presented in 4 elements. This is because if
% the angle w=n*pi, then tan(w/2)=Infinity, then the Rodrigues vector would
% become [Inf Inf Inf]. In order to avoid this case, we present it in a
% 4-element vector. Therefore, the actual Rodrigues vector would be
% multiplying the last element to the first three ones. For the example
% above, the Rodrigues vector would be [Inf Inf Inf].
%
% !!NOTE: If each xx2xx.m were to be used individually, the angle values
% should be in RADIANS!!


switch inputmethod

    case 'eu'
        aa = aa*pi/180; % change to radians
        % check
        if length(aa)~=3
            error('Size of Euler angle not correct.')
        end
        if (aa(1)<0) || (aa(1)>2*pi) || (aa(2)<0) || (aa(2)>pi) || (aa(3)<0) || (aa(3)>2*pi)
            error('Euler angle outside of valid range.')
        end
        
        % transformation
        resEu = aa;
        resEu = resEu*180/pi; %change back to degrees
        resOm = eu2om(aa);
        resAx = eu2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = eu2ro(aa);
        resQu = eu2qu(aa);
        resHo = eu2ho(aa);
        resCu = eu2cu(aa);
    
    case 'om'
        % check 
        if det(aa)==0
            error('Determinant of rotation matrix must be positive.')
        end
        if (det(aa)-1)>1e-15
            error('Determinant of rotation matrix must be unity.')
        end
        r = sum(sum(abs(aa*transpose(aa))));
        if (r-3)>1e-15
            error('Rotation matrix times its transpose must be identity matrix.')
        end
        
        % transformation
        resEu = om2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = aa;
        resAx = om2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = om2ro(aa);
        resQu = om2qu(aa);
        resHo = om2ho(aa);
        resCu = om2cu(aa);
        
    case 'ax'
        aa(4) = aa(4)*pi/180; % angle changes to radians
        % check
        if length(aa)~=4
            error('Size of axis-angle pair not correct.')
        end
        if (aa(4)<0) || (aa(4)>2*pi)
            error('Axis-angle pair outside of valid range.')
        end
        r = sqrt(sum(aa(1:3).*aa(1:3)));
        if (r-1)>1e-15
            error('Axis vector must have unit norm.')
        end
        
        % transformation
        resEu = ax2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = ax2om(aa);
        resAx = aa;
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = ax2ro(aa);
        resQu = ax2qu(aa);
        resHo = ax2ho(aa);
        resCu = ax2cu(aa);
        
    case 'ro'
        % check
        if length(aa)~=4
            error('Size of Rodrigues-Frank vector not correct.')
        end
        if (aa(4)<0) 
            error('Rodrigues-Frank vector has negative length.')
        end
        r = abs(sqrt(sum(aa(1:3).*aa(1:3))));
        if (r-1)>1e-15
            error('Rodrigues-Frank axis vector not normalized.')
        end
        
        % transformation
        resEu = ro2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = ro2om(aa);
        resAx = ro2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = aa;
        resQu = ro2qu(aa);
        resHo = ro2ho(aa);
        resCu = ro2cu(aa);
        
    case 'qu'
        % check
        if length(aa)~=4
            error('Size of quaternion not correct.')
        end
        if (aa(1)<0) 
            error('Quaternion must have positive scalar part.')
        end
        r = sqrt(sum(aa.*aa));
        if (r-1)>1e-15
            error('Quaternion must have unit norm.')
        end
        
        % transformation
        resEu = qu2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = qu2om(aa);
        resAx = qu2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = qu2ro(aa);
        resQu = aa;
        resHo = qu2ho(aa);
        resCu = qu2cu(aa);
        
    case 'ho'
        % check
        if length(aa)~=3
            error('Size of homochoric vector not correct.')
        end
        thr = 1e-10;
        r1 = (3*pi/4)^(1/3);
        r  = sqrt(sum(aa.*aa));
        if ((r-r1)>thr) 
            error('Homochoric vector outside homochoric ball.')
        end
        
        % transformation
        resEu = ho2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = ho2om(aa);
        resAx = ho2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = ho2ro(aa);
        resQu = ho2qu(aa);
        resHo = aa;
        resCu = ho2cu(aa);
        
    case 'cu'
        % check
        if length(aa)~=3
            error('Size of cubochoric vector not correct.')
        end
        thr = 1e-10;
        r1 = pi^(2/3)/2;
        r  = max(abs(aa));
        if ((r-r1)>thr) 
            error('Cubochoric vector outside cube.')
        end
        
        % transformation
        resEu = cu2eu(aa);
        resEu = resEu*180/pi; %change back to degrees
        resOm = cu2om(aa);
        resAx = cu2ax(aa);
        resAx(4) = resAx(4)*180/pi;  %change back to degrees
        resRo = cu2ro(aa);
        resQu = cu2qu(aa);
        resHo = cu2ho(aa);
        resCu = aa;
        
        % take care of Rodrigues vector?!
        
end

resultorientations.EulerAngle = resEu;
resultorientations.RotationMatrix = resOm;
resultorientations.AxisAnglePair = resAx;
resultorientations.RodriguesVector = resRo;
resultorientations.Quaternion = resQu;
resultorientations.Homochoric = resHo;
resultorientations.Cubochoric = resCu;
    