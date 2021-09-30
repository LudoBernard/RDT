//
// Created by efarhan on 9/15/20.
//

#include "TestChannel.h"

TestChannel::TestChannel() :
    sender_(*this), receiver_(*this)

{

}

const TestSender &TestChannel::GetSender() const {
    return sender_;
}

const TestReceiver &TestChannel::GetReceiver() const {
    return receiver_;
}

void TestChannel::SendToReceiver(const Packet &packet)
{
    packetToReceiver_++;
    if(state_ & LOSS_PKT_RECEIVER)
    {
        return;
    }
    if(state_ & LOSS_HALF_PKT_RECEIVER && packetToReceiver_ % 2 == 1)
    {
        return;
    }
    bool isCorrupted = false;
    Packet corruptPacket = packet;
    if(state_ & CORRUPT_PKT_DATA_RECEIVER)
    {
        corruptPacket.data[2]++;
        isCorrupted = true;
    }
    if(state_ & CORRUPT_PKT_CHECKSUM_RECEIVER)
    {
        corruptPacket.checksum++;
        isCorrupted = true;
    }
    if(state_ & CORRUPT_PKT_SEQ_NMB_RECEIVER)
    {
        corruptPacket.sequenceNmb++;
        isCorrupted = true;
    }
    receiver_.ReceivePacket(isCorrupted?corruptPacket:packet);
}

void TestChannel::SendToSender(const Packet &packet)
{
    packetToSender_++;
    if(state_ & LOSS_PKT_SENDER)
    {
        return;
    }
    if(state_ & LOSS_HALF_PKT_SENDER && packetToReceiver_ % 2 == 1)
    {
        return;
    }
    bool isCorrupted = false;
    Packet corruptPacket = packet;
    if(state_ & CORRUPT_PKT_DATA_SENDER)
    {
        corruptPacket.data[2] += 4;
        isCorrupted = true;
    }
    if(state_ & CORRUPT_PKT_CHECKSUM_SENDER)
    {
        corruptPacket.checksum++;
        isCorrupted = true;
    }
    if(state_ & CORRUPT_PKT_SEQ_NMB_SENDER)
    {
        corruptPacket.sequenceNmb++;
        isCorrupted = true;
    }
    sender_.ReceivePacket(isCorrupted?corruptPacket:packet);
}

void TestChannel::SendNewPacket(float packetDelay)
{
    sender_.SendNewPacket(packetDelay);
}

void TestChannel::SetState(std::uint32_t state)
{
    state_ = state;
}

void TestChannel::Send(const std::string_view txt)
{
    sender_.Send(txt);
}

void TestChannel::Update(float dt)
{
    sender_.Update(dt);
}
