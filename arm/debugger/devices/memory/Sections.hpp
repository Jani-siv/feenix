#pragma once

#include <cstdint>
#include <utility>
#include <string>

namespace devices {
namespace memory {

using LMA = uint32_t;
using VMA = uint32_t;

class Sections {
public:
    Sections()=default;
    ~Sections()=default;
    void InitSection(uint32_t vma, uint32_t lma);
    uint32_t GetLmaMapping(uint32_t address) const;
    uint32_t GetVmaStartAddress() const;
private:
    void SetMemoryMapping(uint32_t lma, uint32_t vma);
    std::string sectionName_{};
    std::pair<VMA,LMA> vmaToLma_{};
};

} // namespace memory
} // namespace devices
