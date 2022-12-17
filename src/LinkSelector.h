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
    virtual void finish() override;
    virtual int numInitStages() const { return 2; };
    virtual void handleMessage(cMessage *msg) override;
    cMessage* malusExpire;
    cMessage* monitoringExpire;
    cMessage* serviceTimeExpire;

  private:
    std::queue<AirCraftPacket*> queue;
    std::queue<double> waitingTimeQueue;
    int chosenDL;
    int nDL;
    int operationMode;
    double X;
    double m;
    bool isScanning = true;
    bool serving = false;
    double nextMonitoringTime;
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
