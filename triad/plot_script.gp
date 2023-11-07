set datafile separator ","
set term png size 800,600
set output "flops_vs_n.png"

set title "Achieved FLOP/s vs. n"
set xlabel "n (logarithmic scale)"
set ylabel "FLOP/s"

set logscale x 10
set format x "10^{%L}"

plot 'triad.csv' using 1:3 with linespoints title "Achieved FLOP/s"
