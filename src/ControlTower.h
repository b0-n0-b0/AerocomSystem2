#ifndef __AEROCOMSYSTEMS2_CONTROLTOWER_H_
#define __AEROCOMSYSTEMS2_CONTROLTOWER_H_

#include <omnetpp.h>

using namespace omnetpp;

class ControlTower : public cSimpleModule
{
  private:
    simsignal_t responseTimeSignal;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
