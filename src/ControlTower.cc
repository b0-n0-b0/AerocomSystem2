#include "ControlTower.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    responseTimeSignal = registerSignal("responseTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    //TODO: check the equivalent for getSending implemented by Mariella
//    double responseTime = msg->getArrivalTime().dbl() - msg->getSending();
//    emit(responseTimeSignal, responseTime);
    delete(msg);
}
