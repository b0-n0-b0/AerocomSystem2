#ifndef __AEROCOMSYSTEMS2_DATALINK_H_
#define __AEROCOMSYSTEMS2_DATALINK_H_

#include <omnetpp.h>

using namespace omnetpp;

class DataLink : public cSimpleModule
{
    public:
        virtual double getActualCapacity();

    private:
        double t;
        double lastGenerationTime;
        cMessage *startVariation;
        double startCapacity;
        double nextCapacity;
        double minCapacity;
        double maxCapacity;
        virtual void generate_t();
        virtual void startCapacityVariation();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

#endif
