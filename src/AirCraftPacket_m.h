//
// Generated file, do not edit! Created by opp_msgtool 6.0 from AirCraftPacket.msg.
//

#ifndef __AIRCRAFTPACKET_M_H
#define __AIRCRAFTPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class AirCraftPacket;
/**
 * Class generated from <tt>AirCraftPacket.msg:1</tt> by opp_msgtool.
 * <pre>
 * packet AirCraftPacket
 * {
 *     double genTime;
 *     int size;
 * }
 * </pre>
 */
class AirCraftPacket : public ::omnetpp::cPacket
{
  protected:
    double genTime = 0;
    int size = 0;

  private:
    void copy(const AirCraftPacket& other);

  protected:
    bool operator==(const AirCraftPacket&) = delete;

  public:
    AirCraftPacket(const char *name=nullptr, short kind=0);
    AirCraftPacket(const AirCraftPacket& other);
    virtual ~AirCraftPacket();
    AirCraftPacket& operator=(const AirCraftPacket& other);
    virtual AirCraftPacket *dup() const override {return new AirCraftPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual double getGenTime() const;
    virtual void setGenTime(double genTime);

    virtual int getSize() const;
    virtual void setSize(int size);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AirCraftPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AirCraftPacket& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline AirCraftPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<AirCraftPacket*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __AIRCRAFTPACKET_M_H

