SEED=$RANDOM; ./carli_r -s $SEED -e cart-pole --ignore-x true --set-goal false -c inv-update-count --eligibility-trace-decay-rate 0.99 -d 0.99 -g 0.01 -l 0.1 --policy off-policy --split-min 3 --pseudoepisode-threshold 10 --num-episodes 100 --num-steps 0; echo $SEED
