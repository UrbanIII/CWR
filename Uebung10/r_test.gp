set term x11 1

# Histogram stolen from http://psy.swansea.ac.uk/staff/carter/gnuplot/gnuplot_frequency.htm

clear
reset
set key off
set border 3

# Add a vertical dotted line at x=0 to show centre (mean) of distribution.
set yzeroaxis

# Each bar is half the (visual) width of its x-range.
set boxwidth 0.001 absolute
set style fill solid 1.0 noborder

bin_width = 0.001;

bin_number(x) = floor(x/bin_width)

rounded(x) = bin_width * ( bin_number(x) + 0.5 )

plot 'r_test_hist' using (rounded($1)):(1) smooth frequency with boxes



# 2D
set term x11 2
plot 'r_test_2d' with points ps 1 pt 0


# 3D
set term x11 3
splot 'r_test_3d' with points pt 26 ps 0.5
