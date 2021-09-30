//
// Created by efarhan on 9/15/20.
//

#include <Packet.h>
#include <Client.h>
#include "gtest/gtest.h"

TEST(checksum, check_seq_nmb_positive)
{
    Packet packet;
    packet.sequenceNmb = 3;
    packet = Client::GenerateChecksum(packet);
    EXPECT_TRUE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_seq_nmb_corrupt)
{
    Packet packet;
    packet.sequenceNmb = 3;
    packet = Client::GenerateChecksum(packet);
    packet.sequenceNmb = 4;
    EXPECT_FALSE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_data_positive1)
{
    Packet packet;
    packet.data[3] = 3;
    packet = Client::GenerateChecksum(packet);
    EXPECT_TRUE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_data_positive2)
{
    Packet packet;
    packet.sequenceNmb = 3;
    packet.data = {"hello"};
    packet = Client::GenerateChecksum(packet);
    EXPECT_TRUE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_data_corrupt1)
{
    Packet packet;
    packet.data[3] = 3;
    packet = Client::GenerateChecksum(packet);
    packet.data[3] = 4;
    EXPECT_FALSE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_data_corrupt2)
{
    Packet packet;
    packet.data[3] = 3;
    packet = Client::GenerateChecksum(packet);
    packet.data[4] = 4;
    EXPECT_FALSE(Client::CheckCorrupt(packet));
}

TEST(checksum, check_checksum_corrupt)
{
    Packet packet;
    packet.sequenceNmb = 3;
    packet.data[3] = 3;
    packet = Client::GenerateChecksum(packet);
    packet.checksum++;
    EXPECT_FALSE(Client::CheckCorrupt(packet));
}