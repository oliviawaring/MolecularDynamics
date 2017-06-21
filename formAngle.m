function [ flag ] = formAngle( atom1, atom2, atom3, system )
%UNTITLED12 Summary of this function goes here
%   Detailed explanation goes here

   id1 = atom1.id;
   id2 = atom2.id;
   id3 = atom3.id;
  
   flag = system.angles(id1, id2, id3);
 
end

