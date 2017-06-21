function [ system ] = integrate_berendsen( system, time )
%UNTITLED11 Summary of this function goes here
%   Detailed explanation goes here
   
   N = system.numAtoms;
   dt = system.timestep;
   atom = system.atoms;
   a_types = system.atomTypes;
   tau = system.tau;
   T_0 = system.desiredTemp;
   T_prev = system.previousTemp;
   BOLTZMANN = 8.314472e-3; % DUNNO!!!!!
   
   totalV = [ 0 0 0 ];
   totalV2 = [ 0 0 0 ];
   totalKE = 0;

   scaling = sqrt(1 + dt / tau * ((T_0 / T_prev) - 1));
   for i=1:N
      curPos = atom(i).position;
      force = atom(i).force;
      prevPos = atom(i).prevPos;                                                       
      type = atom(i).type;
      nextPos = 2 .* curPos - prevPos + (dt .^ 2) .* force ./ a_types(type).mass;
      vel = scaling * (nextPos - prevPos) ./ (2 .* dt);
      atom(i).prevPos = curPos;
      atom(i).position = nextPos;
      atom(i).velocity = vel;
      totalV = totalV + vel;
      totalV2 = totalV2 + (vel .^ 2);
      a_types(type).mass
      totalKE = totalKE + sum(a_types(type).mass .* (vel .^ 2));
      system.trajectory(i, system.timeStep+1, 1:3) = [nextPos(1), nextPos(2), nextPos(3)];
   end
   system.kinetic(time) = totalKE;
   T_current = totalKE/(BOLTZMANN * 3 * N);
   system.temperature(time) = T_current;
   system.previousTemp = T_current;
   system.atoms = atom;
end

