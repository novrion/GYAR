#!bin/bash

> data/out

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_ar_base

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_ar_undo_move

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_ar_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_ar_move_order




x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_bb_base

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_bb_undo_move

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_bb_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 1414 ]; then
    echo $line >> data/out
  fi
  (( x++ ))
done < data/out_bb_move_order



tmp=$(cat data/out | tr "." ",")
echo $tmp > data/out