function [ dist ] = getDist( atom1, atom2 )
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

   curPos1 = atom1.position;
   curPos2 = atom2.position;
   dist = curPos1 - curPos2;
   
end

