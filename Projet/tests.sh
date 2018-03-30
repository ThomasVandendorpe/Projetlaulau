for FILE in exemples/input/*
do
     valgrind -q ./appli config1.xml >/dev/null < $FILE
done
echo "FIN"
