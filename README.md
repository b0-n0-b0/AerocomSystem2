# PECSN project
The objective of the project is to evaluate the performance of two different implementations of a communication protocol, used by Aircrafts to communicate with a Control Tower via Data Links having a transmission capacity varying linearly in time. 
The two implementations are:
- Unmonitored: The Aircraft keeps the same serving Data Link for the whole simulation;
- Monitored: The Aircraft constantly monitors the service time of Data Link and before each transmission it selects the Data Link with the highest actual capacity. Monitoring Data Link service time gives X% malus to capacity.
The evaluation will focus primarily on the performance indexes regarding response time, waiting time and queue length.
