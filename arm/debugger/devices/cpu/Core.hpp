#pragma once
#include <memory>
#include "../registers/Registers.hpp"
#include "../memory/Mmu.hpp"

namespace devices {
namespace cpu {

class Core {
public:
    Core();
    ~Core() = default;
private:
    std::shared_ptr<registers::Registers> registers_;
    std::shared_ptr<memory::Mmu> mmu_;
};

} // namespace cpu
} // namespace devices
