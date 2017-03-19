# Scripts

1. make
2. scp ./server heyihong@172.19.222.54:~
3. to run corresponding tests, please copy and paste the script below in into the shell. Please have sudo cache in the shell.

## RTT
```
sudo tcpdump -i any 'src port 9014 or dst port 9014' &> rtt-dump.result &
TCPDUMP_PID=$!
make rtt-benchmark
sudo kill $TCPDUMP_PID
cat rtt-dump.result | grep localhost > local-rtt.result
cat rtt-dump.result | grep dyn54.sysnet.ucsd.edu > remote-rtt.result
rm -f rtt-dump.result
```

## Connection
```
sudo tcpdump -i any 'src port 9014 or dst port 9014' &> conn-dump.result &
TCPDUMP_PID=$!
make conn-benchmark
sudo kill $TCPDUMP_PID
cat conn-dump.result | grep localhost > local-conn.result
cat conn-dump.result | grep dyn54.sysnet.ucsd.edu > remote-conn.result
rm -f conn-dump.result
```

## Peak
```
sudo tcpdump -i any 'src port 9014' &> peak-dump.result &
TCPDUMP_PID=$!
make peak-benchmark
sudo kill $TCPDUMP_PID
cat peak-dump.result | grep localhost > local-peak.result
cat peak-dump.result | grep dyn54.sysnet.ucsd.edu > remote-peak.result
rm -f peak-dump.result
```
