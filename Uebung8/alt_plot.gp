#http://psy.swansea.ac.uk/staff/carter/gnuplot/gnuplot_3d.htm

set view map
#set size ratio .9

#set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
#set object 1 rect fc rgb "black" fillstyle solid 1.0

splot "out" using 1:2:3 with points pointtype 5 pointsize 10 palette linewidth 30

