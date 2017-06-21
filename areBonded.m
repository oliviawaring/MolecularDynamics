function [ flag ] = areBonded( atom1, atom2, system )
%UNTITLED12 Summary of this function goes here
%   Detailed explanation goes here

   id1 = atom1.id;
   id2 = atom2.id;
  
   flag = system.bonds(id1, id2);
 
end

