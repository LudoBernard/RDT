#include "Receiver.h"
#include "Channel.h"

void Receiver::ReceivePacket(const Packet &packet)
{
    if(Client::CheckCorrupt(packet))
    {
        SendACK(packet.sequenceNmb);
    }
    else
    {
        SendNAK(packet.sequenceNmb);
    }
}

void Receiver::SendPacket(const Packet &packet)
{
    channel_.SendToSender(packet);
}

void Receiver::SendACK(byte sequenceNmb)
{
    Packet packet;
    packet.sequenceNmb = sequenceNmb;
    packet.data[0] = true;
    packet = Client::GenerateChecksum(packet);
    SendPacket(packet);
}

void Receiver::SendNAK(byte sequenceNmb)
{
    Packet packet;
    packet.sequenceNmb = sequenceNmb;
    packet.data[0] = false;
    packet = Client::GenerateChecksum(packet);
    SendPacket(packet);
}
