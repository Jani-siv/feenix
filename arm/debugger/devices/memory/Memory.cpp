#include "Memory.hpp"

#include <utility>

namespace devices {
namespace memory {

void Memory::WriteMemory(uint32_t address, uint32_t data)
{

    if (address < memorySize_ && permission_.length() > 1)
    {
        memory_[address] = data;
    }
}

uint32_t Memory::ReadMemory(uint32_t address)
{
    if (address <= memorySize_)
    {
        return memory_.find(address)->second;
    }
    return 0;
}

void Memory::allocateMemory(uint32_t memorySize, std::string permission)
{
    permission_ = std::move(permission);
    memorySize_ = memorySize;
    for(uint32_t i = 0; i < memorySize; i++)
    {
        memory_[i] = 0x0;
    }
}

} // namespace memory
} // namespace devices