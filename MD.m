clear;
  system = buildSystem();
  system = initialize(system); 
  numSteps = system.numSteps;
  numAtoms = system.numAtoms;
  
  for i=1:numSteps
     system.timeStep = i;
     system = updateForces(system);
     system = integrate(system, i);
  end 
 plotTraj(system);
