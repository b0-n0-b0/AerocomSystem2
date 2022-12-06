#include "ControlTower.h"
#include "AirCraftPacket_m.h"
Define_Module(ControlTower);

void ControlTower::initialize()
{
    responseTimeSignal = registerSignal("responseTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    double responseTime = msg->getArrivalTime().dbl() - check_and_cast<AirCraftPacket*>(msg)->getGenTime();
//    EV << responseTime;
    emit(responseTimeSignal, responseTime);
    delete(msg);
//    EV<< check_and_cast<AirCraftPacket*>(msg)->getGenTime();
}
