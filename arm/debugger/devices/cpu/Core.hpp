#pragma once
#include <memory>
#include "../registers/Registers.hpp"
#include "../memory/Mmu.hpp"
#include "Ticks.hpp"

namespace devices {
namespace cpu {

class Core {
public:
    Core(std::vector<devices::memory::MemMsg> msg);
    ~Core() = default;
    virtual void SetCoreDebugMode(const std::string& mode);
    virtual void StartCore();
protected:
    virtual void dumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t len);
    uint32_t ReadPCRegister();
    uint32_t GetCommandFromMemory(uint32_t address);
    std::shared_ptr<registers::Registers> registers_;
    std::shared_ptr<memory::Mmu> mmu_;
    std::shared_ptr<Ticks> clock_;
};

} // namespace cpu
} // namespace devices
