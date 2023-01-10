# PECSN project
## Alternative version
The objective of the project is to evaluate the performance of two different implementations of a communication protocol, used by Aircrafts to communicate with a Control Tower via Data Links having a transmission capacity varying linearly in time. 
The two implementations are:
- Unmonitored: The Aircraft keeps the same serving Data Link for the whole simulation;
- Monitored: The Aircraft monitors the service time of Data Links every m seconds and selects the Data Link with the highest actual capacity. Monitoring Data Link service time gives X seconds of malus, so during the monitoring period, it won't be possible to send packets for X seconds, the system will start sending packets at t = km+X.
The evaluation will focus primarily on the performance indexes regarding response time, waiting time and queue length.
