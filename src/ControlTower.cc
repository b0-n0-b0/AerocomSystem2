#include "ControlTower.h"
#include "AirCraftPacket_m.h"
Define_Module(ControlTower);

void ControlTower::initialize()
{
    responseTimeSignal = registerSignal("responseTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    AirCraftPacket* packet = check_and_cast<AirCraftPacket*>(msg);
    double responseTime = msg->getArrivalTime().dbl() - packet->getGenTime() + packet->getServiceTime();
//    EV << responseTime;
    emit(responseTimeSignal, responseTime);
    delete(packet);
//    EV<< check_and_cast<AirCraftPacket*>(msg)->getGenTime();
}
