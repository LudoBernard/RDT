//
// Created by efarhan on 9/15/20.
//
#include <iostream>
#include "Packet.h"
#include "Sender.h"
#include "Channel.h"

void Sender::ReceivePacket(const Packet &packet)
{
    if (!CheckCorrupt(packet))
    {
        return;
    }
    bool isAck = packet.data[0];
    byte seqNmb = packet.sequenceNmb;
    if(isAck)
    {
    	
        if(seqNmb == 1)
        {
            CalculateFirstRTT(packet.rtt);
        }
        else
        {
            CalculateNewRTT(packet.rtt);
        }
        timer_ = 0.f;
        lastSendSeqNmb_++;
    }
    else
    {
    }
	
}

void Sender::SendPacket(const Packet &packet)
{
    channel_.SendToReceiver(packet);
}

void Sender::Send(std::string_view msg)
{
    size_t pktNumber = msg.size()/Packet::packetSize;
    if(pktNumber*Packet::packetSize != msg.size())
    {
        pktNumber++;
    }
    for(size_t i = 0; i < pktNumber;i++)
    {
        Packet p;
        for(size_t j = 0; j < Packet::packetSize; j++)
        {
            const auto index = i * Packet::packetSize + j;
            if(index == msg.size())
                break;
            const char c = msg[index];
            if(c == 0)
                break;
            p.data[j] = c;
        }
        p.sequenceNmb = i+1;
        p = Client::GenerateChecksum(p);
        sentPackets_.push_back(p);
    }
    lastSendSeqNmb_ = 1;
}

void Sender::Update(float dt)
{
    if(IsMessageSent())
    {
        return;
    }
    timer_ += dt;
    if(timer_ >= rto_)
    {
        OnTimeout();
    }
}

byte Sender::GetLastSendSeqNmb() const
{
    return lastSendSeqNmb_;
}

void Sender::CalculateFirstRTT(float r)
{
    srtt_ = r;
    rttvar_ = (r / 2.f);
    rto_ = srtt_ + std::max(g_, k_ * rttvar_);
    if (rto_ < 1.0f) rto_ = 1.0f;
}

void Sender::CalculateNewRTT(float r)
{
    rttvar_ = (1.f - beta_) * rttvar_ + beta_ * std::abs(srtt_ - r);
    srtt_ = (1.f - alpha_) * srtt_ + alpha_ * r;
    rto_ = srtt_ + std::max(g_, k_ * rttvar_);
    if (rto_ < 1.0f) rto_ = 1.0f;
}

bool Sender::IsMessageSent() const {
    return lastSendSeqNmb_ == sentPackets_.size() + 1;
}

void Sender::OnTimeout()
{
    Packet& packet = sentPackets_[lastSendSeqNmb_-1];
    packet.rtt = packetDelay_;
    SendPacket(packet);
    //TODO update RTT and timer
    rto_ *= 2.f;
    if (rto_ < 1.0f) rto_ = 1.0f;
    timer_ = 0.0f;
}

void Sender::SendNewPacket(float packetDelay)
{
    if(IsMessageSent())
        return;
    packetDelay_ = packetDelay;
    Packet& packet = sentPackets_[lastSendSeqNmb_-1];
    packet.rtt = packetDelay;
    SendPacket(packet);
}

float Sender::GetSrtt() const {
    return srtt_;
}

float Sender::GetRttvar() const {
    return rttvar_;
}

float Sender::GetRto() const {
    return rto_;
}

size_t Sender::GetPacketNmb() const {
    return sentPackets_.size();
}
