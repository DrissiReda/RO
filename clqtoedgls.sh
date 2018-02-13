#!/bin/bash
if [ $# -le 0 ]
    then echo "Usage ./clqtoedgls.sh <file>"
    exit 1
fi
for var in "$@"; do
a="$(grep -n "^p edge" $var | head -1|cut -d':' -f1)"
echo "for $var we have $a"
if [ "$a" == "" ]
    then echo "Error: $var Incorrect format"
    continue
fi 
tail -n +$a $var > $var.1
sed s/"p edge"/"e"/g < $var.1 > $var.2
b="$(echo $var |sed 's/.*\///'|sed 's/\.[^.]*$//')"
cut -d' ' -f2,3 < $var.2 > edgls/$b.ls
rm $var.1 $var.2
./edgtoadj $b
done
