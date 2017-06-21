function [ hash ] = getBondType( atom1, atom2, system )
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here

   row = atom1.type - 1;
   column = atom2.type - 1;
   numAtomTypes = system.numAtomTypes;  
   hash = numAtomTypes * row + column;
   for i=1:row
      hash = hash - numAtomTypes + 1;
   end
   hash = hash + 1;

end

