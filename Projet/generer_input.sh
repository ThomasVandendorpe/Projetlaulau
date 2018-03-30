WIDTH=100
HEIGHT=100
MAX=10
RAND=1 #1 pour random, 0 sinon

#echo "2"
#echo "1"
echo $(( (RANDOM % 2 ) +1 ))
echo $(( (RANDOM % 3 ) +1 ))

i=1
while [ $i -le $HEIGHT ]
do
    j=1
    while [ $j -le $WIDTH ]
    do
	if [ $RAND -eq 1 ]
	then
	    echo -n "$(( (RANDOM % $MAX ) +1 )) "
	else
	    echo -n "$i "
	fi
	j=$(($j+1))
    done
    echo ""
    i=$(($i+1))
done
