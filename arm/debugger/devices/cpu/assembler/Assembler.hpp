#pragma once

#include <memory>
#include "../../registers/Registers.hpp"

#define FLAG_Z 0x1U
#define FLAG_C 0x2U
#define FLAG_N 0x3U
#define FLAG_V 0x4U

#define SET_FLAG(flag_var, flag) ((flag_var) |= (flag))
#define CLR_FLAG(flag_var, flag) ((flag_var) &= ~(flag))
#define GET_FLAG(flag_var, flag) ((_Bool)((flag_var) & (flag)))

namespace devices {
namespace cpu {
namespace assembler {

class Assembler{
public:
    Assembler()=default;
    ~Assembler()=default;
    std::string Execute(uint32_t command);
private:
    uint8_t apsrFlags_ = 0x0;
    bool adc_t1(uint32_t command);
    bool adc_t2(uint32_t command);
    bool add_t1_imm(uint32_t command);
    bool add_t2_imm(uint32_t command);
    bool add_t1_reg(uint32_t command);
    bool add_t2_reg(uint32_t command);
    bool add_t1_sp_imm(uint32_t command);
    bool add_t2_sp_imm(uint32_t command);
    bool add_t1_sp_reg(uint32_t command);
    bool add_t2_sp_reg(uint32_t command);
    bool adr(uint32_t command);
    bool and_imm(uint32_t command);
    bool and_reg(uint32_t command);
    bool asr_imm(uint32_t command);
    bool asr_reg(uint32_t command);
};

} //namespace assembler
} //namespace cpu
} //namespace devices
