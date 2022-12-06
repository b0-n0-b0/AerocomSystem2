simple LinkSelector
{
    parameters:
        // malus
        double X = default(5);
        // scan period
        int m = default(10);
        // operation mode: 0 -> monitored, 1 -> non-monitored
        int operationMode = default(0);
    gates:
        input LS_in;
        output LS_out[parent.nDL];
}
