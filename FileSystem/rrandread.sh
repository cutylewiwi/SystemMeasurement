#! /bin/bash

RESULT="rrandread.result"
TESTDIR="/mnt/test/"

rm $RESULT

#get remote sudo passwd
echo -n Password:
read -s password

for LOOP in {1..10}
 do
   echo ${LOOP} 
   ssh xcc@dyn54.sysnet.ucsd.edu "echo $password |sudo -S sh -c \'echo 3 >/proc/sys/vm/drop_caches\'"
   sudo -S sh -c 'echo 3 >/proc/sys/vm/drop_caches'
   unbuffer ./randread $TESTDIR 1 | tee -a $RESULT
 done
