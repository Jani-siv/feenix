#include "Sections.hpp"

namespace devices {
namespace memory {

void Sections::InitSection(uint8_t idx, uint32_t size, uint32_t vma, uint32_t lma)
{
    SetMemoryMapping(lma, vma);
    sectionsSize_ = size;
    idx_ = idx;
}

void Sections::SetMemoryMapping(uint32_t lma, uint32_t vma)
{
    lmaToVma_ = std::make_pair(lma,vma);
    vmaToLma_ = std::make_pair(vma,lma);
}

uint32_t Sections::GetLmaMapping(uint32_t address) const
{
    return (address - (vmaToLma_.first - vmaToLma_.second));
}
uint32_t Sections::GetVmaStartAddress() const
{
    return vmaToLma_.first;
}


} // namespace memory
} // namespace devices
