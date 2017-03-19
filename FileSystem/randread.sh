#! /bin/bash

RESULT="randread.result"
TESTDIR="./"

rm $RESULT

for LOOP in {1..10}
 do
   echo ${LOOP} 
   sudo -S sh -c 'echo 3 >/proc/sys/vm/drop_caches'
   unbuffer ./randread $TESTDIR ./ 1 | tee -a $RESULT
 done
