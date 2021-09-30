
#include <cstddef>
#include "Client.h"

bool Client::CheckCorrupt(const Packet &packet)
{
    byte checksum = 0;
    /*******************************
     * Begin Generate the checksum
     */

    /*******************************
     * End Generate the checksum
     */

    /*******************************
     * Compare the checksum in the packet and the generated one
     * and return the result
     */

    return false;
}

Packet Client::GenerateChecksum(const Packet &packet)
{
    Packet generatedPacket = packet;
    byte checksum = 0;
    /*******************************
     * Begin Generate the checksum
     */

    /*******************************
     * End Generate the checksum
     */
    return generatedPacket;
}

