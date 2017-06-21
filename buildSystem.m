function [ system ] = buildSystem(  )
% Generates a system that conforms to the specifications detailed in
% various input files. A "system" is characterized by atom types 

    cd hautklein\;
    fid = fopen('aTypes.txt');
    numAtomTypes = fscanf(fid, '%i', 1);
    atomTypeList = textscan(fid, '%d %c %f %f %f %c');

    atomType = struct([]);
    for i=1:numAtomTypes
        atomType(i).name = atomTypeList{2}(i);
        atomType(i).mass = atomTypeList{3}(i);
        atomType(i).charge = atomTypeList{4}(i);
        atomType(i).radius = atomTypeList{5}(i);
        atomType(i).color = atomTypeList{6}(i);
    end

    fid = fopen('atomList.txt');
    numAtoms = fscanf(fid, '%i', 1);
    atomList = fscanf(fid, '%i %i %f %f %f', [5 numAtoms]);
    atomList = atomList';

    atom = struct([]);
    for i=1:numAtoms
        atom(i).id = atomList(i, 1);
        atom(i).type = atomList(i, 2);
        atom(i).position = atomList(i, 3:5);
        atom(i).velocity = rand(1,3) - 0.5;
        % atom(i).velocity = [0 0 0];
        atom(i).force = [0 0 0];
        atom(i).prevPos = [0 0 0];
    end

    fid = fopen('pTypes.txt');
    numPairTypes = factorial(numAtomTypes+1)/(2*factorial(numAtomTypes-1));
    pairTypeList = fscanf(fid, '%i %i %f %f', [4 numPairTypes]);
    pairTypeList = pairTypeList';

    pairType = struct([]);
    for i=1:numPairTypes
        pairType(i).atom1 = pairTypeList(i, 1);
        pairType(i).atom2 = pairTypeList(i, 2);
        % pairType(i).hash = ;
        pairType(i).A = pairTypeList(i, 3);
        pairType(i).B = pairTypeList(i, 4);
    end
    
    fid = fopen('bTypes.txt');
    numBondTypes = factorial(numAtomTypes+1)/(2*factorial(numAtomTypes-1));
    bondTypeList = fscanf(fid, '%i %i %f %f', [4 numBondTypes]);
    bondTypeList = bondTypeList';

    bondType = struct([]);
    for i=1:numBondTypes
        bondType(i).atom1 = bondTypeList(i, 1);
        bondType(i).atom2 = bondTypeList(i, 2);
        % pairType(i).hash = ;
        bondType(i).k = bondTypeList(i, 3);
        bondType(i).b = bondTypeList(i, 4);
    end
    
    fid = fopen('bondList.txt');
    numBonds = fscanf(fid, '%i', 1);    
    bondList = fscanf(fid, '%i %i', [2 numBonds]);
    bonds = zeros(numAtoms, numAtoms);
    bondList = bondList';

    for i=1:numBonds
        index1 = bondList(i,1);
        index2 = bondList(i,2);
        bonds(index1, index2) = 1;
    end
    
    fid = fopen('specs.txt');
    specs = textscan(fid, 'temp: %f\ndt: %f\ncutoff: %f\nbox: %f %f %f\nt_max: %f\ntau: %f', [8 1]); 
    temp = specs{1};
    dt = specs{2};
    rc = specs{3};
    box = [ specs{4} specs{5} specs{6} ];
    t_max = specs{7};
    tau = specs{8};
    
    system.atoms = atom;
    system.atomTypes = atomType;
    system.numSteps = t_max / dt;
    system.trajectory = zeros(numAtoms, system.numSteps, 3);
   
    totalKE = 0;
    BOLTZMANN =  8.314472e-3; % Not certain about these units...
       
    
    
    for i=1:numAtoms
        A = system.atoms(i);
        system.trajectory(i, 1, 1:3) = [A.position(1), A.position(2), A.position(3)];
        system.trajectory
        vel = atom(i).velocity;
        type = atom(i).type;
        totalKE = totalKE + sum(atomType(type).mass .* (vel .^ 2));
    end 


    system.bonds = bonds;
    system.bondTypes = bondType;
    system.pairTypes = pairType;
    system.numAtoms = numAtoms;
    system.numAtomTypes = numAtomTypes;
    system.numBondTypes = numBondTypes;
    system.numPairTypes = numPairTypes;
    system.desiredTemp = temp;
    system.timestep = dt;
    system.cutoff = rc;
    system.box = box;
    system.maxTime = t_max;
    system.timeStep = 0;
    system.kinetic = zeros(system.numSteps, 1);
    system.tau = tau;
    system.previousTemp = totalKE/(BOLTZMANN * 3 * numAtoms);
  
    cd ..;
end