#include "Mmu.hpp"

#include <utility>

namespace devices {
namespace memory {

constexpr uint32_t u32inBytes = 4;

void Mmu::CreateMemory(const std::vector<MemMsg>& message)
{
    for (auto i: message) {
        for (auto j : i.GetMemLayout()) {
            memLayout_.push_back(j);
        }
        for (auto k : i.GetPayloadForMemory()) {
            if (!k.dissAssData.empty())
            {
                for (auto l : k.dissAssData)
                {
                    dissAss_.push_back(l);
                }
            }
        }
    }
    //todo new private functions for these below
    //create memory
    for (const auto& i: memLayout_) {
        Memory mem;
        uint32_t bytes = (i.dataLength - (i.dataLength % u32inBytes)) / u32inBytes;
        mem.allocateMemory(bytes, i.permission);
        memory_[i.name] = mem;
        memoryVmaStartPoint_[i.name] = i.startingAddress;
    }
    //write data to memory
    for (auto i : dissAss_)
    {
        this->memory_["rom"].WriteMemory16(i.first,i.second);
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

uint32_t Mmu::ReadData32(uint32_t address)
{
    //todo no need for memory location modification
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
  //  return memory_[memName].ReadMemory32(ConvertLmaToVectorPosition(transformedAddress));
  return memory_[memName].ReadMemory32(address);
}

uint16_t Mmu::ReadData16(uint16_t address)
{
    //todo no need for memory location modification
    MemoryName memName = getMemoryName(address);
    SectionName secName = getSectionName(address);
    //uint32_t transformedAddress = sections_[secName].GetLmaMapping(address);
    //  return memory_[memName].ReadMemory32(ConvertLmaToVectorPosition(transformedAddress));
    return this->memory_[memName].ReadMemory16(address);
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

void Mmu::DumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t endAddress)
{
    dump.SetDumpFilename(std::move(filename));
    std::string memoryName = getMemoryName(startAddress);
    std::vector<uint32_t> data;
    auto memSize = memory_[memoryName].GetMemorySize();
    if ((endAddress/4) > memSize)
    {
        endAddress = memSize;
    }
    for (auto i = 0x0; i < endAddress; i++) {
        if ((i % 4 == 0) || (i == 0x0)) {
            data.push_back(memory_[memoryName].ReadMemory32(i));

        }
    }
    //memory_[memoryName].PrintMemory();
    dump.DumpMemoryDataToFile(data);
}

} // namespace memory
} // namespace devices
