#!/bin/csh

# File containing the list of numbers
set filename = "Numbers.txt"

# Loop through each line in the file
foreach num (`cat $filename`)
	echo $num

	@ nummin=$num / 100 * 100
	@ nummax=($num / 100 + 1) * 100
	echo "nummin: " $nummin
	echo "nummax: " $nummax
#ls /sphenix/lustre01/sphnxpro/physics/slurp/tracking/new_2024p007/run_00051600_00051700/DST_TRKR_HIT_run2pp_new_2024p007-000${num}*root > RunList/${num}.txt
#ls /sphenix/tg/tg01/commissioning/pinkenbu/51616_1023/DST_STREAMING_EVENT_run2pp_new_2024p002-000${num}*.root > RunList/${num}.txt
	ls /sphenix/lustre01/sphnxpro/physics/slurp/streaming/physics/new_2024p002/run_000${nummin}_000${nummax}/*${num}*.root > RunList/${num}.txt

end


