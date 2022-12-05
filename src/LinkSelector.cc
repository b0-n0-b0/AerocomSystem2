#include "LinkSelector.h"
#include "DataLink.h"


// Sub Module which manages a FIFO queue, which is responsible for sending packets. In the non monitored operation mode
// the DL is chosen once for all the simulation  at the start. In the monitored one the link selector scans periodically
// all the available data links every m seconds and selects the one with the highest capacity. In the monitored mode there’s
// also a malus due to the monitoring delay X. After the delay the operations are handled as usual.


Define_Module(LinkSelector);

void LinkSelector::initialize(int stage)
{
    //two stage inizialization to avoid requests sent to a DL before the inizialization of the capacity
    if(stage == 0){
        //set up of the needed messages
        malusExpire = new cMessage("malusExpire");
        monitoringExpire = new cMessage("monitoringExpire");
        nDL = getAncestorPar("nDL");
        //0 -> monitored, 1 -> non-monitored
        operationMode = par("operationMode");
    }else if (stage == 1){
        // set up of the variables needed for the monitoring
        if(operationMode == 0 && nDL > 0){
            m = par("m");
            X = par("X");
            monitorDl();
        }
        else if(nDL > 0){
            chosenDL = intrand(nDL,1);
        }
    }
}

void LinkSelector::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage()){
        // restart of the monitoring
        if(strcmp(msg->getName(),"monitoringExpire") == 0){
            monitorDl();
        }
        // end of the malus, we can send messages
        if(strcmp(msg->getName(),"malusExpire") == 0){
            isScanning = false;
            sendPacket();
        }
    }
    else{
        // a message from outside is arrived, we have to store this in the queue
        handlePcktArrival(check_and_cast<AirCraftPacket*>(msg));
    }
}

void LinkSelector::getIndexBestCapacity(){
    double capacity = -1;
    cObject* temp;
    DataLink* dl;
    // searching for the best capacity
    for(int i = 0; i < nDL; ++i){
        // find the DL connected to the i-th gate
        cGate *outgate = gate("LS_out",i);
        temp = outgate->getPathEndGate()->getOwner();
        // retrieve capacity
        dl = check_and_cast<DataLink*>(temp);
        double testedCapacity = dl->getActualCapacity();
        EV <<"#DL = "<<i<<" capacity: "<< testedCapacity<<"\n";
        // test and save capacity if needed
        if(testedCapacity > capacity){
           capacity = testedCapacity;
           chosenDL = i;
       }
    }
    EV<<"chosen DL = "<<chosenDL<<"\n";
}

void LinkSelector::sendPacket(){
    // if we are not scanning and the queue has packets in it, we send them
    while(!queue.empty() && isScanning == false){
        AirCraftPacket* packet = queue.front();
        queue.pop();
        send(packet,"LS_out", chosenDL);
    }
}

void LinkSelector::handlePcktArrival(AirCraftPacket* msg){
    // save message in queue
    queue.push(msg);
    sendPacket();
}

void LinkSelector::handleMalus(){
    scheduleAt(simTime() + X, malusExpire);
}

void LinkSelector::monitorDl(){
    isScanning = true;
    scheduleAt(simTime() + m, monitoringExpire);

    getIndexBestCapacity();
    handleMalus();
}
