#!/bin/bash

successProbability=0.9

if [ $# -le 2 ]; then
  echo Usage: $0 radius data_set_file query_set_file 
  exit
fi

nDataSet=` wc -l "$2"`
for x in $nDataSet; do nDataSet=$x; break; done
nQuerySet=` wc -l "$3"`
for x in $nQuerySet; do nQuerySet=$x; break; done
dimension=`head -1 "$2" | wc -w`

#echo $nDataSet $nQuerySet $dimension

bin/exactNNs $nDataSet $nQuerySet $dimension $successProbability $1 "$2" "$3"
