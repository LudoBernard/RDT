//
// Created by efarhan on 9/18/20.
//


#include "gtest/gtest.h"
#include "random.h"
#include "TestChannel.h"

const float updateDeltaTime = 0.1f;
const float packetDelay = 0.1f;
const float firstRtt = 1.0f;
const int updateToTimeout = int(firstRtt/packetDelay);

const std::string longText ="C'est un trou de verdure ou chante une riviere\n"\
        "Accrochant follement aux herbes des haillons\n"\
        "D'argent ; ou le soleil, de la montagne fiere,\n"\
        "Luit : c'est un petit val qui mousse de rayons.\n"\
        "Un soldat jeune, bouche ouverte, tete nue,\n"\
        "Et la nuque baignant dans le frais cresson bleu,\n"\
        "Dort; il est etendu dans l'herbe sous la nue,\n"\
        "Pale dans son lit vert ou la lumiere pleut.\n"\
        "Les pieds dans les glaieuls, il dort.Souriant comme\n"\
        "Sourirait un enfant malade, il fait un somme : \n"\
        "Nature, berce - le chaudement : il a froid.\n"\
        "Les parfums ne font pas frissonner sa narine;\n"\
        "Il dort dans le soleil, la main sur sa poitrine\n"\
        "Tranquille.Il a deux trous rouges au cote droit.";


TEST(timeout, timeout_interval1)
{
    TestChannel channel;
    channel.Send(longText);
    float avgDelay = 0.5f;
    float margin = 0.2f;
    size_t packetToSent = channel.GetSender().GetPacketNmb();
    for(size_t i = 0; i < packetToSent; i++)
    {
        float delay = RandomRange(avgDelay - margin, avgDelay + margin);
        channel.SendNewPacket(delay);
    }
    const auto srtt = channel.GetSender().GetSrtt();
    const auto rto = channel.GetSender().GetRto();

    EXPECT_NEAR(srtt, 0.5f, 0.1f);
    EXPECT_GT(rto, avgDelay + margin);
    //rfc6298 2.4
    EXPECT_GE(rto, 1.0f);
}


TEST(timeout, timeout_interval2)
{
    TestChannel channel;
    channel.Send(longText);
    float avgDelay = 2.0f;
    float margin = 0.3f;
    std::vector<float> delays;
    size_t packetToSent = channel.GetSender().GetPacketNmb();
    for(size_t i = 0; i < packetToSent; i++)
    {
        float delay = RandomRange(avgDelay - margin, avgDelay + margin);
        channel.SendNewPacket(delay);
    }
    const auto srtt = channel.GetSender().GetSrtt();
    const auto rto = channel.GetSender().GetRto();

    EXPECT_NEAR(srtt, 2.0f, 0.2f);
    EXPECT_GT(rto, avgDelay + margin);
    //rfc6298 2.4
    EXPECT_GE(rto, 1.0f);
}

TEST(timeout, loss_receiver)
{
    TestChannel channel;
    channel.SetState(TestChannel::LOSS_PKT_RECEIVER);

    channel.Send("Hello");

    channel.SendNewPacket(packetDelay);
    for(int i = 0; i < updateToTimeout; i++)
    {
        channel.Update(updateDeltaTime);
    }
    EXPECT_TRUE(channel.GetSender().HasTimeout());
    EXPECT_FALSE(channel.GetSender().IsMessageSent());
}

TEST(timeout, loss_sender)
{
    TestChannel channel;
    channel.SetState(TestChannel::LOSS_PKT_SENDER);

    channel.Send("Hello");

    channel.SendNewPacket(packetDelay);
    for(int i = 0; i < updateToTimeout; i++)
    {
        channel.Update(updateDeltaTime);
    }
    EXPECT_TRUE(channel.GetSender().HasTimeout());
    EXPECT_FALSE(channel.GetSender().IsMessageSent());
}


TEST(timeout, loss_once_receiver)
{
    TestChannel channel;
    channel.SetState(TestChannel::LOSS_HALF_PKT_RECEIVER);

    channel.Send("Hello");

    channel.SendNewPacket(packetDelay);
    for(int i = 0; i < 2*updateToTimeout; i++)
    {
        channel.Update(updateDeltaTime);
    }
    EXPECT_TRUE(channel.GetSender().HasTimeout());
    EXPECT_TRUE(channel.GetSender().IsMessageSent());
}

TEST(timeout, loss_once_sender)
{
    TestChannel channel;
    channel.SetState(TestChannel::LOSS_HALF_PKT_SENDER);

    channel.Send("Hello");

    channel.SendNewPacket(packetDelay);
    for(int i = 0; i < 2*updateToTimeout; i++)
    {
        channel.Update(updateDeltaTime);
    }
    EXPECT_TRUE(channel.GetSender().HasTimeout());
    EXPECT_TRUE(channel.GetSender().IsMessageSent());
}