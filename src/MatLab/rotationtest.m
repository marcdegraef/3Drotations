clear
% rotation test
format long
setGlobal_epsijk(-1);
% one test: difference between eu2om and results.resOm
% diffom = max(max(eu2om(inputanglerad)-results.resOm));

% pair tests: difference between eu2om and results.resOm
% diffpair = max(ax2eu(om2ax(eu2om(inputanglerad)))-inputanglerad);

testangles = [ 0.0000000000000000        0.0000000000000000        0.0000000000000000 ;...   
   90.000000000000000        0.0000000000000000        0.0000000000000000 ;...
   180.00000000000000        0.0000000000000000        0.0000000000000000 ;...
   270.00000000000000        0.0000000000000000        0.0000000000000000 ;...    
   360.00000000000000        0.0000000000000000        0.0000000000000000 ;...    
   0.0000000000000000        90.000000000000000        0.0000000000000000 ;...    
   90.000000000000000        90.000000000000000        0.0000000000000000 ;...    
   180.00000000000000        90.000000000000000        0.0000000000000000 ;...    
   270.00000000000000        90.000000000000000        0.0000000000000000 ;...    
   360.00000000000000        90.000000000000000        0.0000000000000000 ;...    
   0.0000000000000000        180.00000000000000        0.0000000000000000 ;...    
   90.000000000000000        180.00000000000000        0.0000000000000000 ;...    
   180.00000000000000        180.00000000000000        0.0000000000000000 ;...    
   270.00000000000000        180.00000000000000        0.0000000000000000 ;...    
   360.00000000000000        180.00000000000000        0.0000000000000000 ;...    
   0.0000000000000000        0.0000000000000000        90.000000000000000 ;...    
   90.000000000000000        0.0000000000000000        90.000000000000000 ;...    
   180.00000000000000        0.0000000000000000        90.000000000000000 ;...    
   270.00000000000000        0.0000000000000000        90.000000000000000 ;...    
   360.00000000000000        0.0000000000000000        90.000000000000000 ;...    
   0.0000000000000000        90.000000000000000        90.000000000000000 ;...    
   90.000000000000000        90.000000000000000        90.000000000000000 ;...    
   180.00000000000000        90.000000000000000        90.000000000000000 ;...    
   270.00000000000000        90.000000000000000        90.000000000000000 ;...    
   360.00000000000000        90.000000000000000        90.000000000000000 ;...    
   0.0000000000000000        180.00000000000000        90.000000000000000 ;...    
   90.000000000000000        180.00000000000000        90.000000000000000 ;...    
   180.00000000000000        180.00000000000000        90.000000000000000 ;...    
   270.00000000000000        180.00000000000000        90.000000000000000 ;...    
   360.00000000000000        180.00000000000000        90.000000000000000 ;...    
   0.0000000000000000        0.0000000000000000        180.00000000000000 ;...    
   90.000000000000000        0.0000000000000000        180.00000000000000 ;...    
   180.00000000000000        0.0000000000000000        180.00000000000000 ;...    
   270.00000000000000        0.0000000000000000        180.00000000000000 ;...    
   360.00000000000000        0.0000000000000000        180.00000000000000 ;...    
   0.0000000000000000        90.000000000000000        180.00000000000000 ;...    
   90.000000000000000        90.000000000000000        180.00000000000000 ;...    
   180.00000000000000        90.000000000000000        180.00000000000000 ;...    
   270.00000000000000        90.000000000000000        180.00000000000000 ;...    
   360.00000000000000        90.000000000000000        180.00000000000000 ;...    
   0.0000000000000000        180.00000000000000        180.00000000000000 ;...    
   90.000000000000000        180.00000000000000        180.00000000000000 ;...    
   180.00000000000000        180.00000000000000        180.00000000000000 ;...    
   270.00000000000000        180.00000000000000        180.00000000000000 ;...    
   360.00000000000000        180.00000000000000        180.00000000000000 ;...    
   0.0000000000000000        0.0000000000000000        270.00000000000000 ;...    
   90.000000000000000        0.0000000000000000        270.00000000000000 ;...    
   180.00000000000000        0.0000000000000000        270.00000000000000 ;...    
   270.00000000000000        0.0000000000000000        270.00000000000000 ;...    
   360.00000000000000        0.0000000000000000        270.00000000000000 ;...    
   0.0000000000000000        90.000000000000000        270.00000000000000 ;...    
   90.000000000000000        90.000000000000000        270.00000000000000 ;...    
   180.00000000000000        90.000000000000000        270.00000000000000 ;...    
   270.00000000000000        90.000000000000000        270.00000000000000 ;...    
   360.00000000000000        90.000000000000000        270.00000000000000 ;...    
   0.0000000000000000        180.00000000000000        270.00000000000000 ;...    
   90.000000000000000        180.00000000000000        270.00000000000000 ;...    
   180.00000000000000        180.00000000000000        270.00000000000000 ;...    
   270.00000000000000        180.00000000000000        270.00000000000000 ;...    
   360.00000000000000        180.00000000000000        270.00000000000000 ;...    
   0.0000000000000000        0.0000000000000000        360.00000000000000 ;...    
   90.000000000000000        0.0000000000000000        360.00000000000000 ;...    
   180.00000000000000        0.0000000000000000        360.00000000000000 ;...    
   270.00000000000000        0.0000000000000000        360.00000000000000 ;...    
   360.00000000000000        0.0000000000000000        360.00000000000000 ;...    
   0.0000000000000000        90.000000000000000        360.00000000000000 ;...    
   90.000000000000000        90.000000000000000        360.00000000000000 ;...    
   180.00000000000000        90.000000000000000        360.00000000000000 ;...    
   270.00000000000000        90.000000000000000        360.00000000000000 ;...    
   360.00000000000000        90.000000000000000        360.00000000000000 ;...    
   0.0000000000000000        180.00000000000000        360.00000000000000 ;...    
   90.000000000000000        180.00000000000000        360.00000000000000 ;...    
   180.00000000000000        180.00000000000000        360.00000000000000 ;...    
   270.00000000000000        180.00000000000000        360.00000000000000 ;...    
   360.00000000000000        180.00000000000000        360.00000000000000 ];

N = size(testangles,1);

filename = 'C:\Users\ashle\ResearchProjects\3Drotations\src\MatLab\rotationtest.txt';

inputfile = fopen(filename,'w+');
fprintf(inputfile,'Number of rotations in file = %d\n',N);
fprintf('N = %d.\n',N);

rmode = ['eu'; 'ax' ;'ro';'ho';'cu';'qu';'om';'st'];
r1 = (3*pi/4)^(1/3); % homochoric limit
ap = pi^(2/3)/2;     % cubochoric limit

maxdiffmax = zeros(2,8,8,N);
for ii = 1:N
    
    fprintf(inputfile,'---------------------------------------------------\n');
    indtest = testangles(ii,:);
    intestrad = testangles(ii,:)*pi/180;
    
    results = rotation(indtest,'eu'); % in degrees
    % print header: all results
    fprintf(inputfile,'Euler angles              : %3.7f %3.7f %3.7f\n',results.EulerAngle(1),results.EulerAngle(2),results.EulerAngle(3));
    fprintf(inputfile,'Axis-angle pair           : %3.7f %3.7f %3.7f ; %3.7f\n',results.AxisAnglePair(1),results.AxisAnglePair(2),results.AxisAnglePair(3),results.AxisAnglePair(4));
    fprintf(inputfile,'Rodrigues vector          : %3.7f %3.7f %3.7f %3.7f\n',results.RodriguesVector(1),results.RodriguesVector(2),results.RodriguesVector(3),results.RodriguesVector(4));
    fprintf(inputfile,'Homochoric representation : %3.7f %3.7f %3.7f\n',results.Homochoric(1),results.Homochoric(2),results.Homochoric(3));
    fprintf(inputfile,'Cubochoric representation : %3.7f %3.7f %3.7f\n',results.Cubochoric(1),results.Cubochoric(2),results.Cubochoric(3));
    fprintf(inputfile,'Quaternion                : %3.7f %3.7f %3.7f %3.7f\n',results.Quaternion(1),results.Quaternion(2),results.Quaternion(3),results.Quaternion(4));
    fprintf(inputfile,'                           / %3.7f %3.7f %3.7f \\ \n',results.RotationMatrix(1,1),results.RotationMatrix(1,2),results.RotationMatrix(1,3));
    fprintf(inputfile,'Rotation matrix           :| %3.7f %3.7f %3.7f |\n',results.RotationMatrix(2,1),results.RotationMatrix(2,2),results.RotationMatrix(2,3));
    fprintf(inputfile,'                           \\ %3.7f %3.7f %3.7f / \n',results.RotationMatrix(3,1),results.RotationMatrix(3,2),results.RotationMatrix(3,3));
    fprintf(inputfile,'Stereographic representation : %3.7f %3.7f %3.7f\n',results.Stereographic(1),results.Stereographic(2),results.Stereographic(3));
    fprintf(inputfile,' \n');
    
    % pairwise tests
    diffmax = 0.0;
    tcnt = 0;
    for aa = 1:8
        fprintf(inputfile,'%s test \n',rmode(aa,:));
        for bb = 1:8
            if aa~=bb
                forwardmode = strcat(cellstr(rmode(aa,:)),'2',cellstr(rmode(bb,:)));
                revertmode  = strcat(cellstr(rmode(bb,:)),'2',cellstr(rmode(aa,:)));
                forwardfunc = str2func(forwardmode{1});
                revertfunc  = str2func(revertmode{1});
                
                if strcmp(rmode(aa,:),'eu')
                    vin  = results.EulerAngle;
                    vout = revertfunc(forwardfunc(vin*pi/180));
                    omm = eu2om(vout);
                    diff = max(max(abs(omm-results.RotationMatrix)));
                    fprintf(inputfile,'%s max om difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'ro')
                    vin  = results.RodriguesVector;
                    vout = revertfunc(forwardfunc(vin));
                    if vout(4)==Inf
                        diff = max(abs(vout(1:3))-abs(vin(1:3)));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max ro difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'ax')
                    vin  = results.AxisAnglePair;
                    vin(4) = vin(4)*pi/180;
                    vout = revertfunc(forwardfunc(vin));
%                     vin(4) = vin(4)*180/pi;
%                     vout(4) = vout(4)*180/pi;
                    if (vout(4)-pi)<=1e-8
                        diff = max(abs(vout(1:3))-abs(vin(1:3)));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max ax difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'ho')
                    vin  = results.Homochoric;
                    vout = revertfunc(forwardfunc(vin));
                    aux = sqrt(sum(vout.*vout));
                    if (abs(aux-r1))<=1e-8
                        diff = max(abs(vout)-abs(vin));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max ho difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'cu')
                    vin  = results.Cubochoric;
                    vout = revertfunc(forwardfunc(vin));
                    aux = max(abs(vout));
                    if (abs(aux-ap))<=1e-8
                        diff = max(abs(vout)-abs(vin));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max cu difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                if strcmp(rmode(aa,:),'st')
                    vin  = results.Stereographic;
                    vout = revertfunc(forwardfunc(vin));
                    aux = max(abs(vout));
                    if (abs(aux-ap))<=1e-8
                        diff = max(abs(vout)-abs(vin));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max st difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'qu')
                    vin  = results.Quaternion;
                    vout = revertfunc(forwardfunc(vin));
                    if abs(vout(1))<=1e-8
                        diff = max(abs(vout(2:4))-abs(vin(2:4)));
                    else
                        diff = max(abs(vout-vin));
                    end
                    fprintf(inputfile,'%s max qu difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
                if strcmp(rmode(aa,:),'om')
                    
                    vin  = results.RotationMatrix;
                    vout = revertfunc(forwardfunc(vin));
                    diff = max(max(abs(vout-vin)));
%                     fprintf('%s max om difference = %3.16f\n',forwardmode{1},diff);
                    fprintf(inputfile,'%s max om difference = %3.16f\n',forwardmode{1},diff);
                    diffmax = max([diffmax,diff]);
                    tcnt = tcnt+1;
                end
                
            end
        end
    end
    
    fprintf(inputfile,' \n');
    fprintf(inputfile,'Maximum difference in pairwise tests = %3.16f\n',diffmax);
    fprintf(inputfile,' \n');
    tcnt2 = tcnt;
    fprintf('done pairwise tests\n');
    maxdiffmax(1,aa,bb,ii) = diffmax;
    
    % pairwise tests
    diffmax = 0.0;
    tcnt = 0;
    for aa = 1:8
        fprintf(inputfile,'triple %s test \n',rmode(aa,:));
        for bb = 1:8
            if aa~=bb
                for cc = 1:8
                    if (cc~=aa) && (cc~=bb)
                        
                        step12 = strcat(cellstr(rmode(aa,:)),'2',cellstr(rmode(bb,:)));
                        step23  = strcat(cellstr(rmode(bb,:)),'2',cellstr(rmode(cc,:)));
                        step31  = strcat(cellstr(rmode(cc,:)),'2',cellstr(rmode(aa,:)));
                        step12func = str2func(step12{1});
                        step23func = str2func(step23{1});
                        step31func = str2func(step31{1});
                
                        if strcmp(rmode(aa,:),'eu')
                            vin  = results.EulerAngle;
                            vout = step31func(step23func(step12func(vin*pi/180)));
                            omm = eu2om(vout);
                            diff = max(max(abs(omm-results.RotationMatrix)));
                            fprintf(inputfile,'%s-%s-%s max om difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'ro')
                            vin  = results.RodriguesVector;
                            vout = step31func(step23func(step12func(vin)));
                            if vout(4)==Inf
                                diff = max(abs(vout(1:3))-abs(vin(1:3)));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max ro difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'ax')
                            vin  = results.AxisAnglePair;
                            vin(4) = vin(4)*pi/180;
                            vout = step31func(step23func(step12func(vin)));
%                             vin(4) = vin(4)*180/pi;
%                             vout(4) = vout(4)*180/pi;
                            if (vout(4)-pi)<=1e-8
                                diff = max(abs(vout(1:3))-abs(vin(1:3)));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max ax difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'ho')
                            vin  = results.Homochoric;
                            vout = step31func(step23func(step12func(vin)));
                            aux = sqrt(sum(vout.*vout));
                            if (abs(aux-r1))<=1e-8
                                diff = max(abs(vout)-abs(vin));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max ho difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'cu')
                            vin  = results.Cubochoric;
                            vout = step31func(step23func(step12func(vin)));
                            aux = max(abs(vout));
                            if (abs(aux-ap))<=1e-8
                                diff = max(abs(vout)-abs(vin));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max cu difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                        
                         if strcmp(rmode(aa,:),'st')
                            vin  = results.Stereographic;
                            vout = step31func(step23func(step12func(vin)));
                            aux = max(abs(vout));
                            if (abs(aux-ap))<=1e-8
                                diff = max(abs(vout)-abs(vin));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max st difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'qu')
                            vin  = results.Quaternion;
                            vout = step31func(step23func(step12func(vin)));
                            if abs(vout(1))<=1e-8
                                diff = max(abs(vout(2:4))-abs(vin(2:4)));
                            else
                                diff = max(abs(vout-vin));
                            end
                            fprintf(inputfile,'%s-%s-%s max qu difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                
                        if strcmp(rmode(aa,:),'om')
                            vin  = results.RotationMatrix;
                            vout = step31func(step23func(step12func(vin)));
                            diff = max(max(abs(vout-vin)));
                            fprintf(inputfile,'%s-%s-%s max om difference = %3.16f\n',step31{1},step23{1},step12{1},diff);
                            diffmax = max([diffmax,diff]);
                            tcnt = tcnt+1;
                        end
                    end
                end
            end
        end
    end
    
    fprintf(inputfile,' \n');
    fprintf(inputfile,'Maximum difference in triplet tests = %3.16f\n',diffmax);
    fprintf(inputfile,' \n');
    tcnt3 = tcnt;
    maxdiffmax(2,aa,bb,ii) = diffmax;
end