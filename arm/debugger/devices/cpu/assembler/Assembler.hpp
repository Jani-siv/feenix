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
    std::string ExecuteThumb(uint32_t command);
private:
    uint8_t apsrFlags_ = 0x0;
    //thumb
    bool adc_reg(uint16_t command);
    bool add_t1_imm(uint16_t command);
    bool add_t2_imm(uint16_t command);
    bool add_t1_reg(uint16_t command);
    bool add_t2_reg(uint16_t command);
    bool add_t1_sp_imm(uint16_t command);
    bool add_t2_sp_imm(uint16_t command);
    bool add_t1_sp_reg(uint16_t command);
    bool add_t2_sp_reg(uint16_t command);
    bool adr(uint16_t command);
    bool and_reg(uint16_t command);
    bool asr_imm(uint16_t command);
    bool asr_reg(uint16_t command);
    bool b_t1(uint16_t command);
    bool b_t2(uint16_t command);
    bool bic_reg(uint16_t command);
    bool bkpt(uint16_t command);
    bool bx(uint16_t command);
    bool cmn(uint16_t command);
    bool cmp_imm(uint16_t command);
    bool cmp_t1_reg(uint16_t command);
    bool cmp_t2_reg(uint16_t command);
    bool eor(uint16_t command);
    bool ldm(uint16_t command);
    bool ldr_t1_imm(uint16_t command);
    bool ldr_t2_imm(uint16_t command);
    bool ldr_t1_lit(uint16_t command);
    bool ldr_t1_reg(uint16_t command);
    //armv7-m
    bool adc_t2(uint32_t command);
    bool and_imm(uint32_t command);
};

} //namespace assembler
} //namespace cpu
} //namespace devices
