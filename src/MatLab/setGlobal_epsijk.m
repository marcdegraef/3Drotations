function setGlobal_epsijk(val)

global epsijk

epsijk = val;

if val ==1
    fprintf('Using Morawiec version.\n');
else
    fprintf('Using alternative way.\n');
end