#pragma once
#include <memory>
#include "../../memory/Mmu.hpp"
#include "../../registers/Registers.hpp"

constexpr auto MSP = 13;
constexpr auto PSP = 14;
constexpr auto LR = 15;
constexpr auto PC = 16;

namespace devices {
namespace cpu {
namespace assembler {

class Execute {
public:
    Execute()=default;
    virtual ~Execute()=default;
    void executeCommand(std::string command, uint32_t data,
                        std::shared_ptr<registers::Registers>& registers, std::shared_ptr<memory::Mmu>& mmu);
private:

    bool IsDoubleInstruction() const;
    bool doubleInstruction = false;
    uint32_t firstPartOfInstruction = 0x0;
    std::string lastCommand_;
    static void b_t2(uint16_t data,
              std::shared_ptr<registers::Registers>& registers);
    void bl(const std::string& command, uint32_t data,
            std::shared_ptr<registers::Registers>& registers);
    void push(uint16_t data, std::shared_ptr<registers::Registers> &registers, std::shared_ptr<memory::Mmu>& mmu);
    void add_t1_sp_imm(uint16_t data, std::shared_ptr<registers::Registers> &registers);
};

} //namespace assembler
} //namespace cpu
} //namespace devices
