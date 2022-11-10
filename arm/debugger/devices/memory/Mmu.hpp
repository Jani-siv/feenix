#pragma once

#include <cstdint>
#include <string>

#include "Memory.hpp"
#include "Sections.hpp"
#include "MemMsg.hpp"
//todo path from content root
#include "../Dumpper.hpp"

using MemoryName = std::string;
using SectionName = std::string;

namespace devices {
namespace memory {

class Mmu {
public:
    Mmu()=default;
    ~Mmu()=default;
    void CreateMemory(const std::vector<MemMsg>& message);
    void CreateSections(const std::string& name, uint32_t vma, uint32_t lma);
    void DumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t endAddress);
    uint32_t ReadData32(uint32_t address);
    uint16_t ReadData16(uint32_t address);
    uint8_t ReadData8(uint32_t address);
    void WriteData32(uint32_t address, uint32_t data);
    void WriteData16(uint32_t address, uint16_t data);
    void WriteData8(uint32_t address, uint8_t data);
    std::string getMemoryName(uint32_t address);
private:
    Dumpper dump;
    static uint32_t ConvertLmaToVectorPosition(uint32_t address);
    std::string getSectionName(uint32_t address);
    std::map<std::string, Memory> memory_;
    std::map<MemoryName, uint32_t> memoryVmaStartPoint_;
    std::map<SectionName, Sections> sections_;
    std::vector<MemoryLayout> memLayout_;
    std::vector<std::pair<addr, payload>> dissAss_;
};

} // namespace memory
} // namespace devices
