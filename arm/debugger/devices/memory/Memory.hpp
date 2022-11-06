#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace devices {
namespace memory {

class Memory {
public:
    Memory()=default;
    void allocateMemory(uint32_t memorySize, std::string permission);
    void WriteMemory(uint32_t address, uint32_t data);
    uint32_t ReadMemory(uint32_t address);
    ~Memory()=default;
    uint32_t GetMemorySize() {return memorySize_;}
private:
    std::string permission_;
    uint32_t memorySize_;
    std::map<uint32_t, uint32_t> memory_;
};

} // namespace memory
} // namespace devices