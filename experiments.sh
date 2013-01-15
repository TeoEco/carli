#!/bin/bash

function average {
  COUNT=0
  VALUE=0

  for file in $@
  do
    NEW=$(tail -n 1 "$file" | sed 's/^.* .* \(.*\) .*$/\1/')
    VALUE=$(echo "scale=4; $VALUE * ($COUNT / ($COUNT + 1)) + $NEW / ($COUNT + 1)" | bc)
    COUNT=$(($COUNT + 1))
  done

  echo $VALUE
}

function averages {
  BEST_VALUE=-99999
  BEST_EXP=""

  for exp in $@; do
    VALUE=$(average $exp/*.out)
    if [ $(echo "scale=4; $VALUE > $BEST_VALUE" | bc) -eq 1 ]; then
      BEST_VALUE=$VALUE
      BEST_EXP="$exp"
    fi
  done

  echo "$BEST_VALUE for $BEST_EXP"
}

./puddleworld-batch.py -r 3
./puddleworld.py experiment-pw/*_0/*.out
./puddleworld.py experiment-pw/*_1/*.out
./puddleworld.py experiment-pw/inv-log-*_2/*.out
./puddleworld.py experiment-pw/inv-root-*_2/*.out
./puddleworld.py experiment-pw/*_3/*.out
./puddleworld.py experiment-pw/*_100/*.out
./puddleworld.py experiment-pw/*_101/*.out
./puddleworld.py experiment-pw/*_200/*.out
./puddleworld.py experiment-pw/*_201/*.out
./puddleworld.py experiment-pw/*_300/*.out
./puddleworld.py experiment-pw/*_301/*.out

./mountaincar-batch.py -r 3
./mountaincar.py experiment-mc/*_0/*.out
./mountaincar.py experiment-mc/*_1/*.out
./mountaincar.py experiment-mc/inv-log-*_2/*.out
./mountaincar.py experiment-mc/inv-root-*_2/*.out
./mountaincar.py experiment-mc/*_3/*.out
./mountaincar.py experiment-mc/*_400/*.out
./mountaincar.py experiment-mc/*_401/*.out

echo ""
averages experiment-pw/*_0
averages experiment-pw/*_1
averages experiment-pw/inv-log-*_2
averages experiment-pw/inv-root-*_2
averages experiment-pw/*_3
averages experiment-pw/*_100
averages experiment-pw/*_101
averages experiment-pw/*_200
averages experiment-pw/*_201
averages experiment-pw/*_300
averages experiment-pw/*_301
echo ""
averages experiment-mc/*_0
averages experiment-mc/*_1
averages experiment-mc/inv-log-*_2
averages experiment-mc/inv-root-*_2
averages experiment-mc/*_3
averages experiment-mc/*_400
averages experiment-mc/*_401
echo ""
