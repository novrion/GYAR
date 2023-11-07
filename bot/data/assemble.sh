#!bin/bash

> everything.txt

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_ar_base

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_ar_undo_move

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_ar_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_ar_move_order




x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_bb_base

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_bb_undo_move

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_bb_alpha_beta

x=0
while read -r line
do
  if [ $x -gt 1412 ]; then
    echo $line >> everything.txt
  fi
  (( x++ ))
done < out_bb_move_order