function q = GetPyramid(xyz)

next = 1;
if ((abs(xyz(1)) <= xyz(3)) && (abs(xyz(2)) <= xyz(3))) 
  p = 1;				% pyramid 1
  next = 0;
end  
    
if (next)  
 if ((abs(xyz(1)) <= -xyz(3)) && (abs(xyz(2)) <= -xyz(3)))
  p = 2;				% pyramid 2
  next = 0;
 end    
end 

if (next)
 if ((abs(xyz(3)) <= xyz(1)) && (abs(xyz(2)) <= xyz(1)))
  p = 3;				% pyramid 3
  next = 0;
 end  
end 
    
if (next)
 if ((abs(xyz(3)) <= -xyz(1)) && (abs(xyz(2)) <= -xyz(1)))
  p = 4;				% pyramid 4
  next = 0;
 end  
end 

if (next)
 if ((abs(xyz(1)) <= xyz(2)) && (abs(xyz(3)) <= xyz(2)))
  p = 5;				% pyramid 5
  next = 0;
 end  
end
    
if (next)
 if ((abs(xyz(1)) <= -xyz(2)) && (abs(xyz(3)) <= -xyz(2)))
  p = 6;				% pyramid 6
%   next = 0;
 end  
end

q = p;

