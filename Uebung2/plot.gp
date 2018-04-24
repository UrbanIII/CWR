set term x11 0
set title 'Velocity in x-direction'
plot 'velocities.txt' u 1:2 t 'Stokes', 'velocities.txt' u 1:4 t 'Newton'
set term x11 1 
set title 'Velocity in y-direction'
plot 'velocities.txt' u 1:3 t 'Stokes', 'velocities.txt' u 1:5 t 'Newton'
set term x11 2 
set title 'Parabola'
plot 'positions.txt' u 2:3 t 'Stokes', 'positions.txt' u 4:5 t 'Newton'
