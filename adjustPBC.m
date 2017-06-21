function [ dist ] = adjustPBC( dist, box )
%UNTITLED7 Summar(2) of this function goes here
%   Detailed explanation goes here
    
   if (dist(1) > box(1))
      dist(1) = dist(1) - box(1);
   elseif (dist(1) < 0)
      dist(1) = dist(1) + box(1); % what if it's a lot less than 0?? 
   end

   if (dist(2) > box(2))
      dist(2) = dist(2) - box(2);
   elseif (dist(2) < 0)
      dist(2) = dist(2) + box(2); % same worry... 
   end

   if (dist(3) > box(3))
      dist(3) = dist(3) - box(3);
   elseif (dist(3) < 0)
      dist(3) = dist(3) + box(3); % same worry...
   end

end

