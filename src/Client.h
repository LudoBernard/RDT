#pragma once
#include "Packet.h"

class Client
{
public:
    virtual void ReceivePacket(const Packet& packet) = 0;
    virtual void SendPacket(const Packet& packet) = 0;
    /**
     * Returns true if packet is NOT corrupted, and false if corrupted
     */
    static bool CheckCorrupt(const Packet& packet);
    static Packet GenerateChecksum(const Packet& packet);

private:
    byte lastReceivedPacket = 0;
};