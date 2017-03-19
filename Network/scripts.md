#Scripts

copy and paste in shell

##RTT
```
sudo tcpdump -i any 'src port 9012 or dst port 9012' &> rtt-dump.result &
TCPDUMP_PID=$!
make rtt-benchmark
sudo kill $TCPDUMP_PID
cat rtt-dump.result | grep localhost > local-rtt.result
cat rtt-dump.result | grep dyn54.sysnet.ucsd.edu > remote-rtt.result
rm -f rtt-dump.result
```

##Connection
```
sudo tcpdump -i any 'src port 9012 or dst port 9012' &> conn-dump.result &
TCPDUMP_PID=$!
make conn-benchmark
sudo kill $TCPDUMP_PID
cat conn-dump.result | grep localhost > local-conn.result
cat conn-dump.result | grep dyn54.sysnet.ucsd.edu > remote-conn.result
rm -f conn-dump.result
```

##Peak
```
sudo tcpdump -i any 'src port 9012 or dst port 9012' &> peak-dump.result &
TCPDUMP_PID=$!
make peak-benchmark
sudo kill $TCPDUMP_PID
cat peak-dump.result | grep localhost > local-peak.result
cat peak-dump.result | grep dyn54.sysnet.ucsd.edu > remote-peak.result
rm -f peak-dump.result
```
