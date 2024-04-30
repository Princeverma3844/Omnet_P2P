//
// Generated file, do not edit! Created by opp_msgtool 6.0 from ArrayMessage.msg.
//

#ifndef __ARRAYMESSAGE_M_H
#define __ARRAYMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class ArrayMessage;
/**
 * Class generated from <tt>ArrayMessage.msg:1</tt> by opp_msgtool.
 * <pre>
 * message ArrayMessage
 * {
 *     int arrayData[5000];
 *     int arraySize;
 *     int source;
 *     int des;
 *     bool dir;
 *     int prop;
 * }
 * </pre>
 */
class ArrayMessage : public ::omnetpp::cMessage
{
  protected:
    int arrayData[5000] = {0};
    int arraySize = 0;
    int source = 0;
    int des = 0;
    bool dir = false;
    int prop = 0;

  private:
    void copy(const ArrayMessage& other);

  protected:
    bool operator==(const ArrayMessage&) = delete;

  public:
    ArrayMessage(const char *name=nullptr, short kind=0);
    ArrayMessage(const ArrayMessage& other);
    virtual ~ArrayMessage();
    ArrayMessage& operator=(const ArrayMessage& other);
    virtual ArrayMessage *dup() const override {return new ArrayMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual size_t getArrayDataArraySize() const;
    virtual int getArrayData(size_t k) const;
    virtual void setArrayData(size_t k, int arrayData);

    virtual int getArraySize() const;
    virtual void setArraySize(int arraySize);

    virtual int getSource() const;
    virtual void setSource(int source);

    virtual int getDes() const;
    virtual void setDes(int des);

    virtual bool getDir() const;
    virtual void setDir(bool dir);

    virtual int getProp() const;
    virtual void setProp(int prop);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ArrayMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ArrayMessage& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline ArrayMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<ArrayMessage*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __ARRAYMESSAGE_M_H
