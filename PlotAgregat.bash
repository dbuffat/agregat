#!/bin/bash
gnuplot<<FIN

cd 'Data'

do for [i=1:3:1]{		#Il faut changer le nombre du milieu suivant le nombre de simulation que vous avez fait
   reset
   set term pdfcairo size 10.5in,7.5in
   set size square
   set output "agregat_".i.".pdf"
   stats "DonneesAgregat_".i.".txt" nooutput
   set xrange [STATS_min_x - 10:STATS_max_x + 10]
   set yrange [STATS_min_y - 10:STATS_max_y + 10]
   set palette defined (0 "cyan", 0.33 "blue", 0.66 "purple", 1 "red")
   set cbrange[0:int(STATS_records)]
   unset key
   unset border
   plot "DonneesAgregat_".i.".txt" using 1:2:3 with points palette pointsize 0.15 pointtype 7 notitle
}

FIN
