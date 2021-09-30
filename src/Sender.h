#pragma once
#include <string_view>
#include <vector>
#include "Client.h"

class Channel;
class Sender : public Client
{
public:
    explicit Sender(Channel& channel) : channel_(channel){}
    virtual void Send (std::string_view msg);

    void ReceivePacket(const Packet &packet) override;

    void SendPacket(const Packet &packet) override;
    /*
     * \brief THis function will send the next packet in the queue
     */
    virtual void Update(float dt);
    virtual void SendNewPacket(float packetDelay);
    [[nodiscard]] byte GetLastSendSeqNmb() const;
    virtual void OnTimeout();

    void CalculateFirstRTT(float r);
    void CalculateNewRTT(float r);
    [[nodiscard]] bool IsMessageSent() const;

    [[nodiscard]] float GetSrtt() const;

    [[nodiscard]] float GetRttvar() const;

    [[nodiscard]] float GetRto() const;

    [[nodiscard]] size_t GetPacketNmb() const;
protected:
    Channel& channel_;
    std::vector<Packet> sentPackets_;
    //sequence Nmb starts at 1..n with n == packet number
    byte lastSendSeqNmb_ = 0;
    float timer_ = 0.0f;

    float packetDelay_ = 0.1f;
    //[RFC6298] rtt retransmission timer (https://tools.ietf.org/html/rfc6298)
    const float k_ = 4.0f;
    const float alpha_ = 1.0f/8.0f;
    const float beta_ = 1.0f/4.0f;
    const float g_ = 0.1f;
    float srtt_ = 0.0f;
    float rttvar_ = 0.0f;
    float rto_ = 1.0f;
};