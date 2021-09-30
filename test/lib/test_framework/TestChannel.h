#pragma once
#include "Channel.h"
#include "TestSender.h"
#include "TestReceiver.h"

class TestChannel : public Channel
{
public:
    enum Type : std::uint32_t
    {
        NONE = 0u,
        CORRUPT_PKT_DATA_SENDER = 1u << 0u,
        CORRUPT_PKT_DATA_RECEIVER = 1u << 1u,
        CORRUPT_PKT_SEQ_NMB_SENDER = 1u << 2u,
        CORRUPT_PKT_SEQ_NMB_RECEIVER = 1u << 3u,
        CORRUPT_PKT_CHECKSUM_SENDER = 1u << 4u,
        CORRUPT_PKT_CHECKSUM_RECEIVER = 1u << 5u,
        LOSS_PKT_SENDER = 1u << 6u,
        LOSS_PKT_RECEIVER = 1u << 7u,
        LOSS_HALF_PKT_SENDER = 1u << 8u,
        LOSS_HALF_PKT_RECEIVER = 1u << 9u,
    };
    TestChannel();
    [[nodiscard]] const TestSender &GetSender() const;

    [[nodiscard]] const TestReceiver &GetReceiver() const;
    void SetState(std::uint32_t state);
    void SendToReceiver(const Packet &packet) override;

    void SendToSender(const Packet &packet) override;
    void Update(float dt);
    void SendNewPacket(float packetDelay) override;

    void Send(const std::string_view txt) override;

protected:
    size_t packetToReceiver_ = 0;
    size_t packetToSender_ = 0;
    TestSender sender_;
    TestReceiver receiver_;
    std::uint32_t state_ = NONE;

};