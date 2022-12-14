#include "PacketGenerator.h"
#include "AirCraftPacket_m.h"

Define_Module(PacketGenerator);

void PacketGenerator::initialize()
{
    kMean = par("kMean");
    k = exponential(kMean,0);
    packetToLs = new cMessage("packetToLs");
    //start  timer to generate the first packet
    scheduleAt(simTime() + k, packetToLs );
}

void PacketGenerator::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        //generate a new packet
          generateNewPacket(msg);
       }
}


void PacketGenerator::generateNewPacket(cMessage *msg)
{
    //create the packet
    AirCraftPacket*  packet= new AirCraftPacket;
    packet->setGenTime(simTime().dbl());
    packet->setSize(par("size"));
    send(packet, "PG_out");
    k = exponential(kMean,0);
    scheduleAt(simTime() + k, msg);
    EV<< "packet generated";

}
