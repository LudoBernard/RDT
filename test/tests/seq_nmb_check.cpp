//
// Created by efarhan on 9/15/20.
//

#include "gtest/gtest.h"
#include "TestChannel.h"

TEST(seq_nmb, check_seq_nmb_positive)
{
    TestChannel channel;

    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_EQ(channel.GetSender().GetLastSendSeqNmb(), 2);
    EXPECT_TRUE(channel.GetSender().IsMessageSent());
}

TEST(seq_nmb, check_receiver_seq_nmb_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_SEQ_NMB_RECEIVER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}

TEST(seq_nmb, check_receiver_data_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_DATA_RECEIVER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}

TEST(seq_nmb, check_receiver_checksum_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_CHECKSUM_RECEIVER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}

TEST(seq_nmb, check_sender_seq_nmb_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_SEQ_NMB_SENDER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}

TEST(seq_nmb, check_sender_data_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_DATA_SENDER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}

TEST(seq_nmb, check_sender_checksum_corrupt)
{
    TestChannel channel;
    channel.SetState(TestChannel::CORRUPT_PKT_CHECKSUM_SENDER);
    channel.Send("Hello");
    channel.SendNewPacket(0);
    EXPECT_NE(channel.GetSender().GetLastSendSeqNmb(), 2);
}