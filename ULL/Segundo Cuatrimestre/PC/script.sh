rm tiempos_bb.txt
rm tiempos_greedy.txt

i=10000
while [ "$i" -le 320000 ]
do  
    echo "$i"
    python tiempos_greedy.py $i
    python tiempos_bb.py $i
    i=$(( $i + 10000 ))
done  
            