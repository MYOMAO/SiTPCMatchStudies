set i=0
set f=8

while ( $i < $f )
 
	echo "TPC Optiom i = " $i
	
	runit_beam3.csh 51616 0 $i


	mv track_match.root track_match_${i}.root


	mv DSTSeedSofar.root_${i}.root OutFile/DST/

	mv track_match_${i}.root OutFile/Match/



	@ i = $i + 1

end
