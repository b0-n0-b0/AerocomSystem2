simple ControlTower
{
    parameters:
        @signal[responseTime] (type = double);
        @statistic[responseTimeStatistic](title = "response time statistic";source = "responseTime"; record = vector, stats);
    gates:
        input CT_in[parent.nDL];
}
