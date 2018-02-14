#!/bin/bash
if [ $# -le 0 ]
    then echo "Usage ./clqtoedgls.sh <file>"
    exit 1
fi
for var in "$@"; do
a="$(grep -n "^e" $var | head -1|cut -d':' -f1)"
echo "for $var we have $a"
if [ "$a" == "" ]
    then echo "Error: $var Incorrect format"
    continue
fi 
tail -n +$a $var > $var.1
b="$(echo $var |sed 's/.*\///'|sed 's/\.[^.]*$//')"
vsize="$(tail -n -1 $var | cut -d' ' -f2)"
esize="$(wc -l $var.1 | cut -d' ' -f1)"
echo "$vsize $esize" > edgls/$b.ls
cut -d' ' -f2,3 $var.1 >> edgls/$b.ls
rm $var.1
./edgtoadj $b
done
