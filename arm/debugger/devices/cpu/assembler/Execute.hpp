#pragma once
#include <memory>
#include "../../memory/Mmu.hpp"
#include "../../registers/Registers.hpp"

constexpr auto PC = 16;

namespace devices {
namespace cpu {
namespace assembler {

class Execute {
public:
    Execute()=default;
    virtual ~Execute()=default;
    void executeCommand(std::string command, uint32_t data,
                        std::shared_ptr<registers::Registers>& registers);
private:
    static void b_t2(uint16_t data,
              std::shared_ptr<registers::Registers>& registers);
    void bl(const std::string& command, uint32_t data,
            std::shared_ptr<registers::Registers>& registers);
    bool IsDoubleInstruction() const;
    bool doubleInstruction = false;
    uint32_t firstPartOfInstruction = 0x0;
    std::string lastCommand_;
};

} //namespace assembler
} //namespace cpu
} //namespace devices
