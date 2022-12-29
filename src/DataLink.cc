#include "DataLink.h"

Define_Module(DataLink);

void DataLink::initialize()
{
    startVariation = new cMessage("startVariation");
    minCapacity = par("minCapacity");
    maxCapacity = par("maxCapacity");
    startCapacity = uniform(minCapacity, maxCapacity,2);
    nextCapacity = uniform(minCapacity, maxCapacity,2);
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
    nextCapacity = uniform(minCapacity, maxCapacity, 2);
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
        t = lognormal(lognormalMean, lognormalStdev,2);
    }else if (generationMode == 1){
        t = exponential(exponentialMean,2);
    }
    // I save the instant in which I generated the t, this instant will be used do calculate the actual capacity
    lastGenerationTime = simTime().dbl();
}

double DataLink::getActualCapacity(){
    //this function will be called by the LinkSelector to retrieve the capacity at the time of the call
    double computationTime = simTime().dbl();
    double delta = computationTime - lastGenerationTime;
    double increment = ((nextCapacity - startCapacity)/t) * delta;
    double actualCapacity = startCapacity + increment;
    return actualCapacity;
}
