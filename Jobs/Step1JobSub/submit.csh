#!/bin/csh

# File containing the list of numbers
set filename = "FileList.txt"


set index=0

# Loop through each line in the file
foreach num (`cat $filename`)
	echo $index
	echo $num

	set runname = "FileLists/file_${index}.txt"


foreach file (`cat $runname`)
# Extract the filename

	echo "file: " $file
# Extract the digits before .root after the last -
	set last_segment = `echo $file | sed 's/^.*-\([0-9]*\)\.root$/\1/'`

# Remove leading zeros
	set seg = `echo $last_segment | sed 's/^0*//'`
	set run = `echo $file | sed -n 's/.*000\([0-9]*\)-.*/\1/p'`
#
	echo "seg = " $seg 
	echo "run = " $run

	if ("$seg" == "") then

	set seg = 0

	endif

	set i = 0
	set f = 8





	sed -i "13s/.*/Run=${run}/" condor.sh	
	sed -i "14s/.*/Seg=${seg}/" condor.sh	
	#sed -i "15s/.*/TPCOpt=${i}/" condor.sh	

	#echo "TPC Corr Index: i = " ${i}  

	condor_submit condor.sh

#	@ i = $i + 1

	end
	@ index = $index + 1

	end


