#!/bin/csh

echo "START Tony"

set baseDir=`pwd`

# source /opt/sphenix/core/bin/sphenix_setup.csh -n new 

set nevents=100
set runind=1
set opt=0

#set strin1="/sphenix/lustre01/sphnxpro/physics/slurp/streaming/physics/new_2024p002/run_00051600_00051700/"
set strin1="/sphenix/tg/tg01/commissioning/pinkenbu/51616_1023/"
echo "input directory: " $strin1

set runid=$1
set run = ("000${runid}")
set segment=$2

echo $run
set strout1=`pwd`/

echo "output directory: " $strout1

 # Format run number with leading zeros if necessary
set formatted_segment=`printf "%05d\n" $segment`
echo "formatted segment: " $formatted_segment
echo "run: " $run[$runind]

set strin0="DST_STREAMING_EVENT_run2pp_new_2024p002-${run[$runind]}-${formatted_segment}.root"
echo $strin0

echo "running Fun4All_FieldOnAllTrackers..."
root -b -q 'Fun4All_FieldOnAllTrackers.C('$nevents', "'$strin0'", "'$strin1'", "'$strout1'", 1 )'

cd ${baseDir}  # Return to base directory
