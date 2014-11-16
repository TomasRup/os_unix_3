#!/bin/sh

counter=0
while [ "$counter" -lt 100 ]
  do
    target/clientapp
    counter=`expr $counter + 1`
  done
