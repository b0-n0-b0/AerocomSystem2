#ifndef __AEROCOMSYSTEMS2_PACKETGENERATOR_H_
#define __AEROCOMSYSTEMS2_PACKETGENERATOR_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class PacketGenerator : public cSimpleModule
{
    private:
    double k;
    cMessage *packetToLs;
    simtime_t generationTime;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void generateNewPacket(cMessage* msg);
};

#endif
