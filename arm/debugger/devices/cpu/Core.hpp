#pragma once
#include <memory>
#include "../registers/Registers.hpp"
#include "../memory/Mmu.hpp"
#include "Ticks.hpp"

namespace devices {
namespace cpu {

class Core {
public:
    Core();
    ~Core() = default;
    virtual void SetCoreDebugMode(const std::string& mode);
    virtual void StartCore();
protected:
    uint32_t ReadPCRegister();
    uint32_t GetCommandFromMemory(uint32_t address);
    std::shared_ptr<registers::Registers> registers_;
    std::shared_ptr<memory::Mmu> mmu_;
    std::shared_ptr<Ticks> clock_;
};

} // namespace cpu
} // namespace devices
