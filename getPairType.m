function [ hash ] = getPairType( atom1, atom2, system )
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here

   row = atom1.type - 1;
   column = atom2.type - 1;
   % ensure that it's lower triangular (to make the hash function work
   % properly)
   if (row < column)
       temp = column;
       column = row;
       row = temp;
   end
   assert(row >= column, 'Matrix must be lower triangular');
   numAtomTypes = system.numAtomTypes;
   hash = numAtomTypes * row + column;
   for i=1:row
      hash = hash - numAtomTypes + i;
   end
   hash = hash + 1;
end

