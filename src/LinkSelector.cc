#include "LinkSelector.h"

/*
 Sub Module which manages a FIFO queue, which is responsible for sending packets. In the non monitored operation mode
 the DL is chosen once for all the simulation  at the start. In the monitored one the link selector scans periodically
 all the available data links every m seconds and selects the one with the highest capacity. In the monitored mode there’s
 also a malus due to the monitoring delay X. After the delay the operations are handled as usual.
*/

Define_Module(LinkSelector);

void LinkSelector::initialize()
{
    malusExpire = new cMessage("malusExpire");
    monitoringExpire = new cMessage("monitoringExpire");

    chosenDL = par("chosenDL");
    nDL = par("nDL");
    operationMode = par("operationMode"); //0 --> monitored

    if(operationMode == 0 && nDL > 0){
        m = par("m");
        X = par("X");
        monitorDl();
    }
    else if(nDL > 0){
        chosenDL = intrand(nDL);
        std::cout<<chosenDL;
    }
}

void LinkSelector::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        if(strcmp(msg->getName(),"monitoringExpire") == 0){
            monitorDl();
        }
        if(strcmp(msg->getName(),"malusExpire") == 0){
            isScanning = false;
            sendPacket();
        }
    }
    else{
        handlePcktArrival(msg);
    }
}

//capire come prendere vettore dl da altro modulo
void LinkSelector::getIndexBestCapacity(){
   int capacity = -1;

    cModule* temp;
    temp = getModuleByPath("DataLink");


//    DataLink* dl;
//    dl = check_and_cast<DataLink*>(temp);
//
//    for(int i = 0; i < nDL; i++){
//        if(dl[i].getActualCapacity() > capacity){
//            capacity = dl->aSearchFunction("getActualCapacity");
//            chosenDl = i;
//        }
//    }
}

void LinkSelector::sendPacket(){
    if(!queue.empty() && isScanning == false){
        while(!queue.empty()){
            cMessage* packet = (cMessage*)queue.front();
            queue.pop();
            send(packet,"LS_out", chosenDL);
        }
    }
}

void LinkSelector::handlePcktArrival(cMessage* msg){
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
