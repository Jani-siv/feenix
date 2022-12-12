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
    void
    mov_t2_reg(uint32_t data, std::shared_ptr<registers::Registers> &registers);
    void sub_t1_sp_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void add_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void ldr_t1_lit(uint16_t data, std::shared_ptr<registers::Registers>& registers,
                    std::shared_ptr<memory::Mmu>& mmu);
    void ldm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void stm_t1(uint16_t data, std::shared_ptr<registers::Registers>& registers,
                std::shared_ptr<memory::Mmu>& mmu);
    void ldrb_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers,
                     std::shared_ptr<memory::Mmu>& mmu);
    void strb_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers,
        std::shared_ptr<memory::Mmu>& mmu);
    void str_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers,
                    std::shared_ptr<memory::Mmu>& mmu);
    void ldr_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers,
                    std::shared_ptr<memory::Mmu>& mmu);
    void mov_t1_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void lsl_ti_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void orr_t1_reg(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void add_t1_reg(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void cmp_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void b_t1(uint16_t data, std::shared_ptr<registers::Registers>& registers);
    void add_t2_imm(uint16_t data, std::shared_ptr<registers::Registers>& registers);
};

} //namespace assembler
} //namespace cpu
} //namespace devices
