#include "Memory.hpp"

#include <utility>

namespace devices {
namespace memory {

void Memory::WriteMemory32(uint32_t address, uint32_t data)
{
    if (address < memorySize_ && permission_.length() > 1)
    {
        WriteMemory16(address, (data & 0x0000FFFF));
        data = data >> 16;
        WriteMemory16(address+2, data);
    }
}

void Memory::WriteMemory16(uint32_t address, uint16_t data)
{
    if (address < memorySize_ && permission_.length() > 1)
    {
        WriteMemory8(address,(data & 0x00FF));
        data = data >> 8;
        WriteMemory8(address+1,data);
    }
}

void Memory::WriteMemory8(uint32_t address, uint8_t data)
{
    if (address < memorySize_ && permission_.length() > 1)
    {
        memory_.at(address) = data;
    }
}

uint32_t Memory::ReadMemory32(uint32_t address)
{
    if (address <= memorySize_)
    {
        uint32_t data = ReadMemory16(address+2);
        data = data << 16;
        data += ReadMemory16(address);
        return data;
    }
    return 0;
}

uint16_t Memory::ReadMemory16(uint32_t address)
{
    if (address <= memorySize_)
    {
        uint16_t data = ReadMemory8(address+1);
        data = data << 8;
        data += ReadMemory8(address);
        return data;
    }
    return 0;
}

uint8_t Memory::ReadMemory8(uint32_t address)
{
    if (address <= memory_.size())
    {
        return memory_.at(address);
    }
    return 0;
}

void Memory::allocateMemory(uint32_t memorySize, std::string permission)
{
    permission_ = std::move(permission);
    memorySize_ = memorySize;
    for(uint32_t i = 0x0; i < memorySize; i++)
    {
        memory_.push_back(0x00);
    }
}

} // namespace memory
} // namespace devices
