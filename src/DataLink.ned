simple DataLink
{
    parameters:
        // capacity variation extremes
        double minCapacity = default(6000);
        double maxCapacity = default(15000);
        //0 -> lognorm , 1-> exp
        int generationMode = default(0);
        // TODO: look at the generations and investigate the best values for these params		
        double exponentialMean = default(1);
        double lognormalMean = default(1);
        double lognormalStdev = default(1);
	gates:
	    output DL_out;
	    input DL_in;
}
