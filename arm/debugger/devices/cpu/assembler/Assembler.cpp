#include "Assembler.hpp"

//SET_FLAG(apsrFlags_, FLAG_C);
//if (GET_FLAG(apsrFlags_, FLAG_N)) { ... }
//CLR_FLAG(apsrFlags_, FLAG_C);

namespace devices {
namespace cpu {
namespace assembler {

//ARMv7-M
bool Assembler::adc_t2(uint32_t command)
{
    command = command >> 20;
    return ((command - 0x75A) == 0);
}
bool Assembler::and_imm(uint32_t command)
{
    //if rd && s == 1 see TST_imm
    uint32_t temp = command;
    temp = temp >> 15;
    CLR_FLAG(command,26);
    uint8_t s, rd;
    s = (command&0x00100000);
    s = s >> 20;
    rd =(command&0x00000F00);
    rd = rd >> 8;
    command = command >> 20;
    if ((command - 0xF00) == 0) {
        if (s == 0x1 && rd == 0xF) { return false; }
        return true;
    }
    return false;
}

std::string Assembler::ExecuteThumb(uint32_t command)
{
    if(adc_reg(command)) {return "ADC_REG";}
  //  if(adc_t2(command)) {return "ADC_T2";}
    if(add_t1_imm(command)) {return "ADD_T1_IMM";}
    if(add_t2_imm(command)) {return "ADD_T2_IMM";}
    if(add_t1_reg(command)) {return "ADD_T1_REG";}
    if(add_t2_reg(command)) {return "ADD_T2_REG";}
    if(add_t1_sp_imm(command)) {return "ADD_T1_SP_IMM";}
    if(add_t2_sp_imm(command)) {return "ADD_T2_SP_IMM";}
    if(add_t1_sp_reg(command)) {return "ADD_T1_SP_REG";}
    if(add_t2_sp_reg(command)) {return "ADD_T2_SP_REG";}
  //  if(and_imm(command)) {return "AND_IMM";}
    if(and_reg(command)) {return "AND_REG";}
    if(adr(command)) {return "ADR";}
    if(asr_imm(command)) {return "ASR_IMM";}
    if(asr_reg(command)) {return "ASR_REG";}
    if(b_t1(command)) {return "B_T1";}
    if(b_t2(command)) {return "B_T2";}
    if(bic_reg(command)) {return "BIC_REG";}
    if(bkpt(command)) {return "BKPT";}
    if(bl(command)) {return "BL";}
    if(bx(command)) {return "BX";}
    if(cmn(command)) {return "CMN";}
    if(cmp_imm(command)) {return "CMP_IMM";}
    if(cmp_t1_reg(command)) {return "CMP_T1_REG";}
    if(cmp_t2_reg(command)) {return "CMP_T2_REG";}
    if(eor(command)) {return "EOR";}
    if(ldm(command)) {return "LDM";}
    if(ldr_t1_imm(command)) {return  "LDR_T1_IMM";}
    if(ldr_t2_imm(command)) {return  "LDR_T2_IMM";}
    if(ldr_t1_lit(command)) {return  "LDR_T1_LIT";}
    if(ldr_t1_reg(command)) {return  "LDR_T1_REG";}
    if(ldrb_t1_imm(command)) {return  "LDRB_T1_IMM";}
    if(ldrb_t1_reg(command)) {return  "LDRB_T1_REG";}
    if(ldrh_t1_imm(command)) {return  "LDRH_T1_IMM";}
    if(ldrh_t1_reg(command)) {return  "LDRH_T1_REG";}
    if(ldrsb_t1_reg(command)) {return  "LDRSB_T1_REG";}
    if(ldrsh_t1_reg(command)) {return  "LDRSH_T1_REG";}
    if(lsl_t1_imm(command)) {return  "LSL_T1_IMM";}
    if(lsl_t1_reg(command)) {return  "LSL_T1_REG";}
    if(lsr_t1_imm(command)) {return  "LSR_T1_IMM";}
    if(lsr_t1_reg(command)) {return  "LSR_T1_REG";}
    if(mov_t1_imm(command)) {return  "MOV_T1_IMM";}
    if(mov_t1_reg(command)) {return  "MOV_T1_REG";}
    if(mov_t2_reg(command)) {return  "MOV_T2_REG";}
    if(mul_t1(command)) {return  "MUL_T1";}
    if(mvn_t1_reg(command)) {return  "MVN_T1_REG";}
    if(orr_t1_reg(command)) {return  "ORR_T1_REG";}
    if(pop_t1(command)) {return  "POP_T1";}
    if(push_t1(command)) {return  "PUSH_T1";}
    if(ror_t1_reg(command)) {return  "ROR_T1_REG";}
    if(rsb_t1_imm(command)) {return  "RSB_T1_IMM";}
    if(sbc_t1_reg(command)) {return  "SBC_T1_REG";}
    if(stm_t1(command)) {return  "STM_T1";}
    if(str_t1_imm(command)) {return  "STR_T1_IMM";}
    if(str_t2_imm(command)) {return  "STR_T2_IMM";}
    if(str_t1_reg(command)) {return  "STR_T1_REG";}
    if(strb_t1_imm(command)) {return  "STRB_T1_IMM";}
    if(strb_t1_reg(command)) {return  "STRB_T1_REG";}
    if(strh_t1_imm(command)) {return  "STRH_T1_IMM";}
    if(strh_t1_reg(command)) {return  "STRH_T1_REG";}
    if(sub_t1_imm(command)) {return  "SUB_T1_IMM";}
    if(sub_t2_imm(command)) {return  "SUB_T2_IMM";}
    if(sub_t1_reg(command)) {return  "SUB_T1_REG";}
    if(sub_t1_sp_imm(command)) {return  "SUB_T1_SP_IMM";}
    if(svc_t1(command)) {return  "SVC_T1";}
    if(tst_t1_reg(command)) {return  "TST_T1_REG";}
    return "nope";
}
bool Assembler::adc_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x105) == 0);
}
bool Assembler::add_t1_imm(uint16_t command)
{
    command = command >> 8;
    return ((command - 0x1C) == 0);
}
bool Assembler::add_t2_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x6) == 0);
}
bool Assembler::add_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0xC) == 0);
}
bool Assembler::add_t2_reg(uint16_t command)
{
    uint16_t temp = command;
    uint8_t rm, rdn ,dn;
    dn = (temp&0x80);
    dn = dn >> 7;
    rdn = dn;
    rdn = rdn << 3;
    rdn += (temp&0x7);
    rm = (temp&0x78);
    rm = rm >> 3;
    if (rdn == 0xD || rm == 0xD) {return false;}
    command = command >> 8;
    return ((command - 0x44) == 0);
}
bool Assembler::add_t1_sp_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x15) == 0);
}
bool Assembler::add_t2_sp_imm(uint16_t command)
{
    command = command >> 7;
    return ((command - 0x160) == 0);
}
bool Assembler::add_t1_sp_reg(uint16_t command)
{
    CLR_FLAG(command,0);
    CLR_FLAG(command,1);
    CLR_FLAG(command,2);
    CLR_FLAG(command,7);
    return ((command - 0x4468) == 0);
}
bool Assembler::add_t2_sp_reg(uint16_t command)
{
    CLR_FLAG(command,3);
    CLR_FLAG(command,4);
    CLR_FLAG(command,5);
    CLR_FLAG(command,6);
    return ((command - 0x4480) == 0);
}
bool Assembler::adr(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x14) == 0);
}
bool Assembler::and_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x100)==0);
}
bool Assembler::asr_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x2)==0);
}
bool Assembler::asr_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x104)==0);
}
//todo need second 16 bits for address
bool Assembler::b_t1(uint16_t command)
{
    uint16_t temp = (command&0x0F00);
    temp = temp >> 8;
    command = command >> 12;
    if ((command - 0xD) == 0)
    {
        if (temp != 0xF)
        {
            return true;
        }
    }
    return false;
}
bool Assembler::b_t2(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x1C)==0);
}
bool Assembler::bic_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10E)==0);
}
bool Assembler::bkpt(uint16_t command)
{
    command = command >> 8;
    return ((command - 0xBE)==0);
}
bool Assembler::bl(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x1E)==0);
}
bool Assembler::bx(uint16_t command)
{
    command = command >> 7;
    return ((command - 0x08E)==0);
}
bool Assembler::cmn(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10B)==0);
}
bool Assembler::cmp_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x5)==0);
}
bool Assembler::cmp_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10A)==0);
}
bool Assembler::cmp_t2_reg(uint16_t command)
{
    command = command >> 8;
    return ((command - 0x45)==0);
}
bool Assembler::eor(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x101)==0);
}
bool Assembler::ldm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x19)==0);
}
bool Assembler::ldr_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0xD)==0);
}
bool Assembler::ldr_t2_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x13)==0);
}
bool Assembler::ldr_t1_lit(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x9)==0);
}
bool Assembler::ldr_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2C)==0);
}
bool Assembler::ldrb_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0xF)==0);
}
bool Assembler::ldrb_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2E)==0);
}
bool Assembler::ldrh_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x11)==0);
}
bool Assembler::ldrh_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2D)==0);
}
bool Assembler::ldrsb_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2B)==0);
}
bool Assembler::ldrsh_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2F)==0);
}
bool Assembler::lsl_t1_imm(uint16_t command)
{
    uint16_t temp = (command&0x07C0);
    temp = temp >> 6;
    command = command >> 11;
    if (command == 0x0)
    {
        if (temp != 0x0)
        {
            return true;
        }
    }
    return false;
}
bool Assembler::lsl_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x102)==0);
}
bool Assembler::lsr_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x1)==0);
}
bool Assembler::lsr_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x103)==0);
}
bool Assembler::mov_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x4)==0);
}
bool Assembler::mov_t1_reg(uint16_t command)
{
    command = command >> 8;
    return ((command - 0x46)==0);
}
bool Assembler::mov_t2_reg(uint16_t command)
{
    command = command >> 6;
    return (command ==0);
}
bool Assembler::mul_t1(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10D)==0);
}
bool Assembler::mvn_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10F)==0);
}
bool Assembler::orr_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x10C)==0);
}
bool Assembler::pop_t1(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x5E)==0);
}
bool Assembler::push_t1(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x5A)==0);
}
bool Assembler::ror_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x107)==0);
}
bool Assembler::rsb_t1_imm(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x109)==0);
}
bool Assembler::sbc_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x106)==0);
}
bool Assembler::stm_t1(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x18)==0);
}
bool Assembler::str_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0xC)==0);
}
bool Assembler::str_t2_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x12)==0);
}
bool Assembler::str_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x28)==0);
}
bool Assembler::strb_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0xE)==0);
}
bool Assembler::strb_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x2A)==0);
}
bool Assembler::strh_t1_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x10)==0);
}
bool Assembler::strh_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0x29)==0);
}
bool Assembler::sub_t1_imm(uint16_t command)
{
    command = command >> 9;
    return ((command - 0xF)==0);
}
bool Assembler::sub_t2_imm(uint16_t command)
{
    command = command >> 11;
    return ((command - 0x7)==0);
}
bool Assembler::sub_t1_reg(uint16_t command)
{
    command = command >> 9;
    return ((command - 0xD)==0);
}
bool Assembler::sub_t1_sp_imm(uint16_t command)
{
    command = command >> 7;
    return ((command - 0x161)==0);
}
bool Assembler::svc_t1(uint16_t command)
{
    command = command >> 8;
    return ((command - 0xDF)==0);
}
bool Assembler::tst_t1_reg(uint16_t command)
{
    command = command >> 6;
    return ((command - 0x108)==0);
}

} //namespace assembler
} //namespace cpu
} //namespace devices
