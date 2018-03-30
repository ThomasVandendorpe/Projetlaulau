i=0
res=0
while [ $i -lt $1 ]
do
    ./generer_input.sh | valgrind -q ./appli config1.xml >/dev/null
    if [ $? -eq 1 ]
    then
	res=$(($res+1))
    fi
    i=$((i+1))
done
echo "FIN"
