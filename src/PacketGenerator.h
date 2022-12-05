#ifndef __AEROCOMSYSTEMS2_PACKETGENERATOR_H_
#define __AEROCOMSYSTEMS2_PACKETGENERATOR_H_

#include <omnetpp.h>

using namespace omnetpp;

class PacketGenerator : public cSimpleModule
{
    private:
    // packet generation period
    // TODO: shouldn't this be random?
    double k = 5;
    cMessage *packetToLs;
    simtime_t generationTime;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void generateNewPacket(cMessage* msg);
};
#endif
