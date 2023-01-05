#include "LinkSelector.h"
#include "DataLink.h"


// Sub Module which manages a FIFO queue, which is responsible for sending packets. In the non monitored operation mode
// the DL is chosen once for all the simulation  at the start. In the monitored one the link selector scans periodically
// all the available data links every m seconds and selects the one with the highest capacity. In the monitored mode there's
// also a malus due to the monitoring delay X. After the delay the operations are handled as usual.

Define_Module(LinkSelector);

void LinkSelector::initialize(int stage)
{
    //two stage inizialization to avoid requests sent to a DL before the inizialization of the capacity
    if(stage == 0){
        //set up of the needed messages
        serviceTimeExpire= new cMessage("serviceTimeExpire");
        nDL = getAncestorPar("nDL");
        //0 -> monitored, 1 -> non-monitored
        operationMode = par("operationMode");
    }else if (stage == 1){
        // set up of the variables needed for the monitoring
        if(operationMode == 0 && nDL > 0){
            X = par("X");
        }
        else if(nDL > 0){
            chosenDL = intrand(nDL,1);
            EV<<"chosen DL = "<<chosenDL<<"\n";
        }
    }
}

void LinkSelector::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage()){
        serving = false;
        sendPacket();
    }
    else{
        // a message from outside is arrived, we have to store this in the queue
        handlePcktArrival(check_and_cast<AirCraftPacket*>(msg));
    }
}

double LinkSelector::getIndexCapacity(int i){
    cObject* temp;
    DataLink* dl;
    cGate *outgate = gate("LS_out",i);
    temp = outgate->getPathEndGate()->getOwner();
    // retrieve capacity
    dl = check_and_cast<DataLink*>(temp);
    return dl->getActualCapacity();
}

void LinkSelector::getIndexBestCapacity(){
    double capacity = -1;
    // searching for the best capacity
    for(int i = 0; i < nDL; ++i){
        // find the DL connected to the i-th gate
        double testedCapacity = getIndexCapacity(i);
        EV <<"#DL = "<<i<<" capacity: "<< testedCapacity<<"\n";
        // test and save capacity if needed
        if(testedCapacity > capacity){
           capacity = testedCapacity;
           chosenDL = i;
       }
    }
    EV<<"chosen DL = "<<chosenDL<<"\n";
}

void LinkSelector::serviceTimePckt(){
    // if we are not scanning and the queue has packets in it, we send them
    if(!queue.empty() && !serving){
         //signal for the service time
        // monitoring
        if(operationMode == 0)
             getIndexBestCapacity();

         double capacity = getIndexCapacity(chosenDL);
         // X% malus if monitoring (X == 0.5 -> 50%)
         if(operationMode == 0)
             capacity -= capacity*X;

         double serviceTime = queue.front()->getSize()/capacity;
         serving = true;
         emit(serviceTimeSignal, serviceTime);
         //signal for the queueing time
         double startWaitingTime = waitingTimeQueue.front();
         waitingTimeQueue.pop();
         emit(waitingTimeSignal, (simTime().dbl() - startWaitingTime));
         // simulation of the time to send a packet
         scheduleAt(simTime() + serviceTime, serviceTimeExpire);
//         EV <<"service time: " <<serviceTime << '\n';
     }
}

void LinkSelector::sendPacket(){
    if(!queue.empty()){
        AirCraftPacket* packet = queue.front();
        queue.pop();
        emit(queueLengthSignal, queue.size());
        send(packet,"LS_out", chosenDL);
        EV <<"packet sent \n";
        //try to send another packet
        serviceTimePckt();
    }
 }


void LinkSelector::handlePcktArrival(AirCraftPacket* msg){
    // save message in queue
    if(nDL > 0){
        // signal for the queue length
        queue.push(msg);
        emit(queueLengthSignal, queue.size());
        //queue used to memorize the instant when a packet enters the queue
        waitingTimeQueue.push(simTime().dbl());
        //if I'm not transmitting another packet
        if(!serving) {
           serviceTimePckt();
         }
    }else{
        delete(msg);
    }
}


void LinkSelector::finish(){
    while(!queue.empty()){
        AirCraftPacket* packet = queue.front();
        queue.pop();
        delete(packet);
    }
    cancelEvent(serviceTimeExpire);
    delete(serviceTimeExpire);
}
