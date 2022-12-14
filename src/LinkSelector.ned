simple LinkSelector
{
    parameters:
        @signal[serviceTime] (type = double);
        @statistic[serviceTimeStatistic](title = "service time statistic";source = "serviceTime"; record = vector, stats);
        @signal[waitingTime] (type = double);
        @statistic[waitingTimeStatistic](title = "waiting time statistic";source = "waitingTime"; record = vector, stats);
        @signal[queueLength] (type = int);
        @statistic[queueLengthStatistic](title = "queue length statistic";source = "queueLength"; record = vector, stats);
        // malus
        double X = default(5);
        // scan period
        double m = default(10);
        // operation mode: 0 -> monitored, 1 -> non-monitored
        int operationMode = default(0);
    gates:
        input LS_in;
        output LS_out[parent.nDL];
}
