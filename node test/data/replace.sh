#!bin/bash
tmp=$(cat $1 | tr "." ",")
echo $tmp > $1
