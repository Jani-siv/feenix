#include "Assembler.hpp"

//SET_FLAG(apsrFlags_, FLAG_C);
//if (GET_FLAG(apsrFlags_, FLAG_N)) { ... }
//CLR_FLAG(apsrFlags_, FLAG_C);

namespace devices {
namespace cpu {
namespace assembler {


std::string Assembler::Execute(uint32_t command)
{
    if(adc_t1(command)) {return "ADC_T1";}
    if(adc_t2(command)) {return "ADC_T2";}
    if(add_t1_imm(command)) {return "ADD_T1_IMM";}
    if(add_t2_imm(command)) {return "ADD_T2_IMM";}
    if(add_t1_reg(command)) {return "ADD_T1_REG";}
    if(add_t2_reg(command)) {return "ADD_T2_REG";}
    if(add_t1_sp_imm(command)) {return "ADD_T1_SP_IMM";}
    if(add_t2_sp_imm(command)) {return "ADD_T2_SP_IMM";}
    if(add_t1_sp_reg(command)) {return "ADD_T1_SP_REG";}
    if(add_t2_sp_reg(command)) {return "ADD_T2_SP_REG";}
    if(and_imm(command)) {return "AND_IMM";}
    if(and_reg(command)) {return "AND_REG";}
    if(adr(command)) {return "ADR";}
    if(asr_imm(command)) {return "ASR_IMM";}
    if(asr_reg(command)) {return "ASR_REG";}
    return "nope";
}
bool Assembler::adc_t1(uint32_t command)
{
    command = command >> 22;
    return ((command - 0x105) == 0);
}
bool Assembler::adc_t2(uint32_t command)
{
    command = command >> 20;
    return ((command - 0x75A) == 0);
}
bool Assembler::add_t1_imm(uint32_t command)
{
    command = command >> 24;
    return ((command - 0x1C) == 0);
}
bool Assembler::add_t2_imm(uint32_t command)
{
    command = command >> 27;
    return ((command - 0x6) == 0);
}
bool Assembler::add_t1_reg(uint32_t command)
{
    command = command >> 25;
    return ((command - 0xC) == 0);
}
bool Assembler::add_t2_reg(uint32_t command)
{
    uint32_t temp = command;
    uint8_t rm, rdn ,dn;
    temp = temp >> 16;
    dn = (temp&0x80);
    dn = dn >> 7;
    rdn = dn;
    rdn = rdn << 3;
    rdn += (temp&0x7);
    rm = (temp&0x78);
    rm = rm >> 3;
    if (rdn == 0xD || rm == 0xD) {return false;}
    command = command >> 24;
    return ((command - 0x44) == 0);
}
bool Assembler::add_t1_sp_imm(uint32_t command)
{
    command = command >> 27;
    return ((command - 0x15) == 0);
}
bool Assembler::add_t2_sp_imm(uint32_t command)
{
    command = command >> 23;
    return ((command - 0x160) == 0);
}
bool Assembler::add_t1_sp_reg(uint32_t command)
{
    command = command >> 16;
    CLR_FLAG(command,0);
    CLR_FLAG(command,1);
    CLR_FLAG(command,2);
    CLR_FLAG(command,7);
    return ((command - 0x4468) == 0);
}
bool Assembler::add_t2_sp_reg(uint32_t command)
{
    command = command >> 16;
    CLR_FLAG(command,3);
    CLR_FLAG(command,4);
    CLR_FLAG(command,5);
    CLR_FLAG(command,6);
    return ((command - 0x4480) == 0);
}
bool Assembler::adr(uint32_t command)
{
    command = command >> 27;
    return ((command - 0x14) == 0);
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
bool Assembler::and_reg(uint32_t command)
{
    command = command >> 22;
    return ((command - 0x100)==0);
}
bool Assembler::asr_imm(uint32_t command)
{
    command = command >> 27;
    return ((command - 0x2)==0);
}
bool Assembler::asr_reg(uint32_t command)
{
    command = command >> 22;
    return ((command - 0x104)==0);
}


} //namespace assembler
} //namespace cpu
} //namespace devices
