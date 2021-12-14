#!/bin/bash

rm -f FIFO.csv LRU.csv OPT.csv

for ((i = 1; i <= 30; i++)); do  # C-style for-loop
   # numFrames = $i
   ./program3 $i
done

#Remove the last comma from all 3 files.
truncate -s-1 FIFO.csv
truncate -s-1 LRU.csv
truncate -s-1 OPT.csv
