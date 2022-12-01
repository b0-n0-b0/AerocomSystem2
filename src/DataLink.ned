simple DataLink
{
    parameters:
        double minCapacity = default(6000);
        double maxCapacity = default(15000);
        int generationMode = default(0); //0 -> lognorm , 1-> exp
        double exponentialMean = default(1); // mean = 1/lambda
        double lognormalMean = default(1);
        double lognormalStdev = default(1);
	gates:
	    output DL_out;
	    input DL_in;
}
