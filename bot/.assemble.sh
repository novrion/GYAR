#!bin/bash

> data/out_raw

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_ar_base

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_ar_undo_move

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_ar_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_ar_move_order




x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_bb_base

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_bb_undo_move

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_bb_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 982 ]; then
    echo $line >> data/out_raw
  fi
  (( x++ ))
done < data/out_bb_move_order



g++ -O2 -o bin/analysis.exe src/analysis.cpp
./bin/analysis.exe < data/out_raw > data/out


tmp=$(cat data/out | tr "." ",")
echo "$tmp" > data/out