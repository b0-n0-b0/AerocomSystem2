#ifndef __AEROCOMSYSTEMS2_LINKSELECTOR_H_
#define __AEROCOMSYSTEMS2_LINKSELECTOR_H_

#include <omnetpp.h>
#include <queue>
#include "AirCraftPacket_m.h"

using namespace omnetpp;

class LinkSelector : public cSimpleModule
{
  protected:
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual int numInitStages() const override  { return 2; };
    virtual void handleMessage(cMessage *msg) override;
    cMessage* serviceTimeExpire;

  private:
    std::queue<AirCraftPacket*> queue;
    std::queue<double> waitingTimeQueue;
    int chosenDL;
    int nDL;
    int operationMode;
    double X;
    bool serving = false;
    //signals
    simsignal_t serviceTimeSignal = registerSignal("serviceTime");
    simsignal_t waitingTimeSignal = registerSignal("waitingTime");
    simsignal_t queueLengthSignal = registerSignal("queueLength");

    void getIndexBestCapacity();
    double getIndexCapacity(int i);
    void sendPacket();
    void handlePcktArrival(AirCraftPacket* msg);
    void serviceTimePckt();
};

#endif
