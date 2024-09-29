#!/bin/bash
for filename_to_check in /direct/sphenix+tg+tg01/hf/zshi/SeedMatchFileAllNew/Ntuple/SeedAna_Svtx_5*root
  do
	
	echo "Checking now: " $filename_to_check

    root.exe -b -l -q -e "auto f = TFile::Open(\"$filename_to_check\"); if (f == nullptr || f->IsZombie()) { cout << \"There is a problem with the file: $filename_to_check\n\"; exit(1); }"
 
	if [ $? -ne 0 ]; then
        echo $filename_to_check has error
		echo I am removing it
		rm $filename_to_check
		echo done
       exit 1
   fi
 done ;
