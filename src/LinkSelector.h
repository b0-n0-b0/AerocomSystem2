
#ifndef __AEROCOMSYSTEMS2_LINKSELECTOR_H_
#define __AEROCOMSYSTEMS2_LINKSELECTOR_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class LinkSelector : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    cMessage* malusExpire;
    cMessage* monitoringExpire;

  private:
    std::queue<cMessage*> queue;
    int chosenDL;
    int nDL;
    int operationMode;
    int X;
    int m;
    bool isScanning = false;

    void getIndexBestCapacity();
    void sendPacket();
    void handlePcktArrival(cMessage* msg);
    void handleMalus();
    void monitorDl();
};

#endif
