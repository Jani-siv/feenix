#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace devices {
namespace memory {

class Memory {
public:
    Memory()=default;
    void allocateMemory(uint32_t memorySize, std::string permission);
    void WriteMemory32(uint32_t address, uint32_t data);
    void WriteMemory16(uint32_t address, uint16_t data);
    void WriteMemory8(uint32_t address, uint8_t data);
    uint32_t ReadMemory32(uint32_t address);
    uint16_t ReadMemory16(uint32_t address);
    uint8_t ReadMemory8(uint32_t address);
    ~Memory()=default;
    uint32_t GetMemorySize() {return memorySize_;}
private:
    std::string permission_;
    uint32_t memorySize_;
    std::vector<uint8_t> memory_;
};

} // namespace memory
} // namespace devices