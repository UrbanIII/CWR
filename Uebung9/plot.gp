#http://www.kleerekoper.co.uk/2014/05/how-to-create-heatmap-in-gnuplot.html
set view map
set dgrid3d
splot "out" using 1:2:3 with pm3d 

