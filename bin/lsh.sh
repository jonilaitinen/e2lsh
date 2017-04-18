#!/bin/bash

dir=bin

if [ $# -le 2 ]; then
  echo Usage: $0 radius data_set_file query_set_file "[successProbability]"
  exit
fi

paramsFile=$2.params

if [ $# -ge 4 ]; then
 # success probability supplied
 $dir/lsh_computeParams $1 "$2" "$3" $4 > "$paramsFile" || exit 1
else
 # success probability not supplied
 $dir/lsh_computeParams $1 "$2" "$3" > "$paramsFile" || exit 1
fi

chmod g+rw "$paramsFile"

echo "R*******" >/dev/stderr
echo "R*********************" >/dev/stderr
echo "R-NN DS params computed." >/dev/stderr
echo "R*********************" >/dev/stderr
echo "R*******" >/dev/stderr

$dir/lsh_fromParams "$2" "$3" "$paramsFile"

# successProbability=0.9

# nDataSet=` wc -l $2` # | sed -e 's/^\  //g' | sed -e 's/\.//'`
# for x in $nDataSet; do nDataSet=$x; break; done
# nQuerySet=` wc -l $3` # $2 | sed -e 's/^\  //g' | sed -e 's/\.*//'`
# for x in $nQuerySet; do nQuerySet=$x; break; done
# dimension=`head -1 $3 | wc -w`

# echo $nDataSet $nQuerySet $dimension

# m=`cat bin/mem`

# bin/LSHMain $nDataSet $nQuerySet $dimension $successProbability $* $m
