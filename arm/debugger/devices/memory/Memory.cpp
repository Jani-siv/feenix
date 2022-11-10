#include "Memory.hpp"

#include <utility>

namespace devices {
namespace memory {

void Memory::WriteMemory32(uint32_t address, uint32_t data)
{
    //todo permission
    if (address < memorySize_ )//&& permission_.length() > 1)
    {
        uint16_t low = (data & 0x0000FFFF);
        data = data >> 16;
        uint16_t high = data;
        WriteMemory16(address+2, low);
        WriteMemory16(address, high);
    }
}

void Memory::WriteMemory16(uint32_t address, uint16_t data)
{
    if (address < memorySize_ && permission_.length() > 1)
    {
        uint8_t low = (data & 0x00FF);
        data = data >> 8;
        uint8_t high = data;
        WriteMemory8(address+2,low);
        WriteMemory8(address+1,high);
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
        uint16_t low = ReadMemory16(address+2);
      //  printf("LOW16: %X\n",low);
        uint16_t high = ReadMemory16(address);
      //  printf("HIGH16: %X\n",high);
        uint32_t data = high;
        data = data << 16;
        data += low;
        return data;
    }
    return 0;
}

uint16_t Memory::ReadMemory16(uint32_t address)
{
    if (address <= memorySize_)
    {
        auto low = ReadMemory8(address+2);
        auto high = ReadMemory8(address+1);
        uint16_t data = high;
        data = data << 8;
        data +=low;
        return data;
    }
    return 0;
}

uint8_t Memory::ReadMemory8(uint32_t address)
{
    if (address <= memory_.size())
    {
      //  printf("%X\n",address);
        return memory_.at(address);
    }
    return 0;
}

void Memory::allocateMemory(uint32_t memorySize, std::string permission)
{
    /*one address is 1 byte*/
    permission_ = std::move(permission);
    memorySize_ = memorySize;
    for(uint32_t i = 0x0; i < memorySize; i++)
    {
        memory_.push_back(0x00);
    }
}
void Memory::PrintMemory()
{
  for (auto i : memory_)
  {
      printf("%X\n",i);
  }
}

} // namespace memory
} // namespace devices
