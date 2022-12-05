#include "PacketGenerator.h"
#include "AirCraftPacket_m.h"

Define_Module(PacketGenerator);

void PacketGenerator::initialize()
{
    generationTime = uniform(0,k,0);
    packetToLs = new cMessage("packetToLs");
    scheduleAt(simTime() + generationTime, packetToLs ); //start  timer to generate the first packet
}

void PacketGenerator::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
          generateNewPacket(msg); //generate a new packet
       }
}


void PacketGenerator::generateNewPacket(cMessage *msg)
{
    AirCraftPacket*  packet= new AirCraftPacket; //create the packet
    packet->setGenTime(simTime().dbl());
    send(packet, "PG_out");
    generationTime = uniform(0,k,0);
    scheduleAt(simTime() + generationTime, msg);
    EV<< "generated packet";

}
