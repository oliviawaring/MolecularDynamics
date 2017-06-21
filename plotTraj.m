function [ ] = plotTraj( system )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

    traj = system.trajectory;
    N = system.numAtoms;
    t = system.numSteps;
    atoms = system.atoms;
    types = system.atomTypes;
    M = moviein(t);
    kinetic = system.kinetic;
    
    dummy = 'a';
    colors = repmat(dummy,N,1);
    for i=1:N
        colors(i) = types(atoms(i).type).color;
    end
    
      
        figure(1);
        x = traj(:,1,1)
        y = traj(:,1,2)
        z = traj(:,1,3)
        
        for j = 1:N
            hold on;
            scatter3(x(j), y(j), z(j), 100, colors(j), 'filled');
        end
        xlabel('x');
        ylabel('y');
        zlabel('z');
        axis([-2 2 -2 2 -2 2 0 255]);
        M(:,i) = getframe;  
        hold off;
     
    
    for i=1:t     
        figure(2);
        x = traj(:,i,1); 
        y = traj(:,i,2);
        z = traj(:,i,3);
        
        for j = 1:N
            hold on;
            scatter3(x(j), y(j), z(j), 100, colors(j), 'filled');
        end
        xlabel('x');
        ylabel('y');
        zlabel('z');
        axis([-20000 20000 -20000 20000 -20000 20000 0 255]);
        M(:,i) = getframe;  
        hold off;
    end
    figure(3);
    plot(1:t, kinetic);
    
end

