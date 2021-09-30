#pragma once

#include "Packet.h"
#include "Client.h"

class Channel;
class Receiver : public Client
{
public:
    explicit Receiver(Channel& channel) : channel_(channel){}
    void ReceivePacket(const Packet &packet) override;
    void SendPacket(const Packet &packet) override;
    void SendACK(byte sequenceNmb);
    void SendNAK(byte sequenceNmb);

protected:
    Channel& channel_;
};