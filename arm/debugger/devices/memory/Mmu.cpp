#include "Mmu.hpp"

#include <utility>

namespace devices {
namespace memory {

constexpr uint32_t u32inBytes = 4;

void Mmu::CreateMemory(const std::vector<MemMsg>& memoryLayout)
{
    for (auto i: memoryLayout) {
        for (auto j : i.GetMemLayout()) {
            memLayout_.push_back(j);
        }
    }
    for (const auto& i: memLayout_) {
        Memory mem;
        uint32_t bytes = (i.dataLength - (i.dataLength % u32inBytes)) / u32inBytes;
        mem.allocateMemory(bytes, i.permission);
        memory_[i.name] = mem;
        memoryVmaStartPoint_[i.name] = i.startingAddress;
    }
}

void Mmu::CreateSections(const std::string& name, uint32_t vma, uint32_t lma)
{
    Sections sec;
    sec.InitSection(vma,lma);
    sections_[name]=sec;
}

void Mmu::WriteData32(uint32_t address, uint32_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory32(ConvertLmaToVectorPosition(transformedAddress), data);
}

void Mmu::WriteData16(uint32_t address, uint16_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory16(ConvertLmaToVectorPosition(transformedAddress), data);
}

void Mmu::WriteData8(uint32_t address, uint8_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory8(ConvertLmaToVectorPosition(transformedAddress), data);
}

uint32_t Mmu::ReadData32(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory32(ConvertLmaToVectorPosition(transformedAddress));
}

uint16_t Mmu::ReadData16(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory16(ConvertLmaToVectorPosition(transformedAddress));
}

uint8_t Mmu::ReadData8(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory8(ConvertLmaToVectorPosition(transformedAddress));
}

std::string Mmu::getMemoryName(uint32_t address)
{
    uint32_t memStartAddress = 0x0;
    MemoryName memName{};
    for (const auto& i : memoryVmaStartPoint_)
    {
        if (i.second >= memStartAddress && i.second <= address)
        {
            memStartAddress = i.second;
            memName = i.first;
        }
    }
    return memName;
}

std::string Mmu::getSectionName(uint32_t address)
{
    SectionName secName{};
    uint32_t vmaAddress = 0x0;
    for (const auto& i : sections_) {
        if (i.second.GetVmaStartAddress() >= vmaAddress && i.second.GetVmaStartAddress() <= address) {
            vmaAddress = i.second.GetVmaStartAddress();
            secName = i.first;
        }
    }
    return secName;
}

uint32_t Mmu::ConvertLmaToVectorPosition(uint32_t address)
{
    if (address % 0x4 == 0)
    {
        return (address / 4);
    }
    return 0;
}

} // namespace memory
} // namespace devices
