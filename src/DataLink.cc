#include "DataLink.h"

Define_Module(DataLink);

void DataLink::initialize()
{
    //TODO: SIGNALS DEFINITION

    //
    startVariation = new cMessage("startVariation");
    double minCapacity = par("minCapacity");
    double maxCapacity = par("maxCapacity");
    startCapacity = uniform(minCapacity, maxCapacity);
    nextCapacity = uniform(minCapacity, maxCapacity);
    generate_t();
    scheduleAt(simTime() + t, startVariation);
}

void DataLink::handleMessage(cMessage *msg)
{
    // if the timer is over, we generate a new nextCapacity and start the linear progression again
    if( msg->isSelfMessage() ){
        startCapacityVariation();
    }else{
        // if a message from outside comes, we send it to the CT
        send(msg,"DL_out");
    }
}
void DataLink::startCapacityVariation(){
    //the time t elapsed so we have reached the nextCapacity
    //we then generate a new capacity to be reached
    startCapacity = nextCapacity;
    double minCapacity = par("minCapacity");
    double maxCapacity = par("maxCapacity");
    nextCapacity = uniform(minCapacity, maxCapacity);
    // we generate a new t and then start the timer for the capacity selection once again
    generate_t();
    scheduleAt(simTime() + t, startVariation);

}

void DataLink::generate_t(){
    int generationMode = par("generationMode");
    double lognormalMean = par("lognormalMean");
    double lognormalStdev = par("lognormalStdev");
    double exponentialMean = par("exponentialMean");
    if(generationMode == 0){
        // TODO: which values for mean, stdev and rng?
        t = lognormal(lognormalMean, lognormalStdev);
    }else if (generationMode == 1){
        // TODO: which values for mean and rng?
        t = exponential(exponentialMean);
    }
    // I save the instant in which I generated the t, this instant will be used do calculate the actual capacity
    lastGenerationTime = simTime().dbl();
}

double DataLink::getActualCapacity(){
    //this function will be called by the LinkSelector to retrieve the capacity at the time of the call
    //random debug values
//    t = 20.5;
//    startCapacity = 2000;
//    nextCapacity = 1000;
    double computationTime = simTime().dbl();
    double delta = computationTime - lastGenerationTime;
    double increment = ((nextCapacity - startCapacity)/t) * delta;
    double actualCapacity = startCapacity + increment;
    //debug
//    EV << "startCapacity = " << startCapacity<< "\nnextCapacity = " << nextCapacity<< "\ncomputation time = " << computationTime<<"\ndelta = "<< delta << "\nincrement = " << increment << "\nactualCapacity = " << actualCapacity;
    return actualCapacity;
}
