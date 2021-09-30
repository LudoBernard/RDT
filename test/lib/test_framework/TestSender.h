#pragma once

#include "Sender.h"

class TestSender : public Sender
{
public:
    using Sender::Sender;
    const Packet &getLastPacketReceived() const
    {
        return lastPacketReceived_;
    }


    void ReceivePacket(const Packet &packet) override
    {
        lastPacketReceived_ = packet;
        Sender::ReceivePacket(packet);
    }

    void OnTimeout() override
    {
        hasTimeout = true;
        Sender::OnTimeout();
    }
    [[nodiscard]] bool HasTimeout() const
    {
        return hasTimeout;
    }
private:
    Packet lastPacketReceived_;
    bool hasTimeout = false;


};