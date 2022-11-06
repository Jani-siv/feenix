#pragma once

#include <cstdint>
#include <string>

#include "Memory.hpp"
#include "Sections.hpp"

using MemoryName = std::string;
using SectionName = std::string;

namespace devices {
namespace memory {

class Mmu {
public:
    Mmu()=default;
    ~Mmu()=default;
    void CreateMemory(const std::string& memoryName, uint32_t startAddr, uint32_t sizeInBytes, std::string permission);
    void CreateSections(const std::string& name, uint32_t size,
                        uint32_t vma, uint32_t lma);
    uint32_t ReadData32(uint32_t address);
    uint16_t ReadData16(uint32_t address);
    uint8_t ReadData8(uint32_t address);
    void WriteData32(uint32_t address, uint32_t data);
    void WriteData16(uint32_t address, uint16_t data);
    void WriteData8(uint32_t address, uint8_t data);
private:
    std::string getMemoryName(uint32_t address);
    std::string getSectionName(uint32_t address);
    uint8_t sectionIdNum_=0;
    std::map<std::string, Memory> memory_;
    std::map<MemoryName, uint32_t> memoryVmaStartPoint_;
    std::map<SectionName, Sections> sections_;
};

} // namespace memory
} // namespace devices
