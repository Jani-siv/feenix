#include "Mmu.hpp"

#include <utility>

namespace devices {
namespace memory {

constexpr uint32_t u32inBytes = 4;

void Mmu::CreateMemory(const std::string& memoryName, uint32_t startAddr, uint32_t sizeInBytes, std::string permission)
{
    Memory mem;
    uint32_t bytes = (sizeInBytes - (sizeInBytes % u32inBytes)) / u32inBytes;
    mem.allocateMemory(bytes, std::move(permission));
    memory_[memoryName]=mem;
    memoryVmaStartPoint_[memoryName]=startAddr;
}

void Mmu::CreateSections(const std::string& name, uint32_t size, uint32_t vma, uint32_t lma)
{
    Sections sec;
    sec.InitSection(sectionIdNum_,size,vma,lma);
    sectionIdNum_++;
    sections_[name]=sec;
}

void Mmu::WriteData32(uint32_t address, uint32_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory32(transformedAddress, data);
}

void Mmu::WriteData16(uint32_t address, uint16_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory16(transformedAddress, data);
}

void Mmu::WriteData8(uint32_t address, uint8_t data)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    memory_[memName].WriteMemory8(transformedAddress, data);
}

uint32_t Mmu::ReadData32(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory32(transformedAddress);
}

uint16_t Mmu::ReadData16(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory16(transformedAddress);
}

uint8_t Mmu::ReadData8(uint32_t address)
{
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    return memory_[memName].ReadMemory8(transformedAddress);
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

} // namespace memory
} // namespace devices
