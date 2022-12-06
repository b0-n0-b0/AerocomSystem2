#include "PacketGenerator.h"
#include "AirCraftPacket_m.h"

Define_Module(PacketGenerator);

void PacketGenerator::initialize()
{
    k = par("k");
    generationTime = uniform(0,k,0);
    packetToLs = new cMessage("packetToLs");
    //start  timer to generate the first packet
    scheduleAt(simTime() + generationTime, packetToLs );
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
    generationTime = uniform(0,k,0);
    scheduleAt(simTime() + generationTime, msg);
    EV<< "packet generated";

}
