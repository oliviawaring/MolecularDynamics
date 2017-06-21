masses = {.2, .4, .6};
charges = {.2, .4, .6};
radii = {.2, .4, .6};
x = {.3, .5, .7};
y = {.3, .5, .7};
z = {.3, .5, .7};

atomTypes = struct('mass', masses, 'charge', charges, 'radius', radii);

positions = struct('x', x, 'y', y, 'z', z);
velocities = struct('x', x, 'y', y, 'z', z);

atoms = struct{'type', types, 'position', positions, 'velocity', velocities};


