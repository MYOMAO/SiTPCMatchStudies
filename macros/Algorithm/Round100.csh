set num=52288

echo $num
    
@ nummin=$num / 100 * 100
@ nummax=($num / 100 + 1) * 100


echo "nummin: " $nummin "   nummax: " $nummax

