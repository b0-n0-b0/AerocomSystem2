#include "PacketGenerator.h"
#include "AirCraftPacket_m.h"

Define_Module(PacketGenerator);

void PacketGenerator::initialize()
{
           generationTime = uniform(0,k);
           packetToLs = new cMessage("packetToLs");
           scheduleAt(simTime() + generationTime, packetToLs ); //start  timer to generate the first packet
}

void PacketGenerator::handleMessage(cMessage *msg)
{
    if( strcmp(msg->getName(), "packetToLs") == 0 ){
          generateNewPacket(msg); //generate a new packet
       }
}


void PacketGenerator::generateNewPacket(cMessage *msg)
{
      AirCraftPacket*  packet= new AirCraftPacket; //create the packet
        packet->setGenTime(simTime().dbl());
        send(packet, "PG_out");
        generationTime = uniform(0,k);
        scheduleAt(simTime() + generationTime, msg );

}
