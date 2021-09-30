#pragma once
#include <cstdint>
#include <cstddef>
#include <array>

using byte = std::uint8_t;

struct Packet
{
    const static size_t packetSize = 30;
    float rtt = 0.0f;
    byte checksum = 0;
    byte sequenceNmb = 0;
    std::array<byte, packetSize> data{};

};