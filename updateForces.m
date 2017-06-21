function [ system ] = updateForces( system )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

    T = system.previousTemp;
    rc2 = system.cutoff .^ 2;
    atom = system.atoms;
    atomType = system.atomTypes;
    pairType = system.pairTypes;
    bondType = system.bondTypes;
    N = system.numAtoms;
    box = system.box;
    
    K_COULOMB = 13893.5; % kN A^2 / e^2
    for i=1:N-1
        for j=i+1:N
            forceFactor = 0;
            dist = getDist(atom(i), atom(j));
            dist = adjustPBC(dist, box);
            r2 = sum(dist .^ 2);
           if r2<rc2
              pType = getPairType(atom(i), atom(j), system); % make sure that order's right...
               A = pairType(pType).A;
               B = pairType(pType).B;
               forceFactor = 12 * ((A/(r2.^6)) - (0.5 * B/(r2.^3))) / r2; % kJ/mol A^2
           end
           q1 = atomType(atom(i).type).charge;
           q2 = atomType(atom(j).type).charge;
           forceFactor = forceFactor + (K_COULOMB * q1 * q2 / r2);  % is this the right expression??? kJ/A AAAAAAAAAAHHHHH!!!!!
           if areBonded(atom(i), atom(j), system)
               bType = getBondType(atom(j), atom(i), system);
               k_harmonic = bondType(bType).k;
               b0 = bondType(bType).b;
               forceFactor = forceFactor + (k_harmonic * (sqrt(r2) - b0) / r2); % kJ/mol NO IDEA!!!!! I just want the forces to turn out right... :(
           end
           atom(i).force = atom(i).force + forceFactor .* dist;
           atom(j).force = atom(j).force - forceFactor .* dist;
           
        end
        system.atoms = atom;
    end