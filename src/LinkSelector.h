#ifndef __AEROCOMSYSTEMS2_LINKSELECTOR_H_
#define __AEROCOMSYSTEMS2_LINKSELECTOR_H_

#include <omnetpp.h>
#include <queue>
#include "AirCraftPacket_m.h"

using namespace omnetpp;

class LinkSelector : public cSimpleModule
{
  protected:
//    virtual void initialize() override;
    virtual void initialize(int stage) override;
    virtual int numInitStages() const { return 2; };
    virtual void handleMessage(cMessage *msg) override;
    cMessage* malusExpire;
    cMessage* monitoringExpire;
    cMessage* ServiceTimeExpire;

  private:
    std::queue<AirCraftPacket*> queue;
    std::queue<double> waitingTimeQueue;
    int chosenDL;
    int nDL;
    int operationMode;
    double X;
    int m;
    bool isScanning = true;
    //signals
    simsignal_t serviceTimeSignal = registerSignal("serviceTime");
    simsignal_t waitingTimeSignal = registerSignal("waitingTime");
    simsignal_t queueLengthSignal = registerSignal("queueLength");

    void getIndexBestCapacity();
    double getIndexCapacity(int i);
    void sendPacket();
    void handlePcktArrival(AirCraftPacket* msg);
    void handleMalus();
    void monitorDl();
    void serviceTimePckt();
};

#endif
