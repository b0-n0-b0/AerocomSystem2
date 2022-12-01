simple LinkSelector
{
    parameters:
        int X = default(5);
        int m = default(10);
        int operationMode = default(0);
    gates:
        input LS_in;
        output LS_out[parent.nDL];
}
