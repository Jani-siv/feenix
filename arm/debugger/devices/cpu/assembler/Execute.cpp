#include "Execute.hpp"

namespace devices {
namespace cpu {
namespace assembler {

constexpr uint8_t align = 0x2;

void Execute::executeCommand(std::string command, uint32_t data,
                             std::shared_ptr<registers::Registers> &registers, std::shared_ptr<memory::Mmu>& mmu)
{
    if (command == "nope") {
        if(IsDoubleInstruction())
        {
            command = lastCommand_;
        }
        else
        {
            registers->writeRegister(PC,registers->readRegister(PC)+align);
        }
    }
    if(command=="B_T2") { b_t2(data, registers);}
    if(command=="BL") { bl(command, data, registers);}
    if(command=="PUSH_T1") {push(data, registers, mmu);}
    if(command=="ADD_T1_SP_IMM") {add_t1_sp_imm(data,registers);}
    if(command=="MOV_T2_REG") {mov_t2_reg(data,registers,mmu);}
}
void Execute::b_t2(uint16_t data, std::shared_ptr<registers::Registers> &registers)
{
    registers->writeRegister(PC,(data&0x07FF)*align+registers->readRegister(PC)+0x4);
}
void Execute::bl(const std::string& command, uint32_t data, std::shared_ptr<registers::Registers> &registers)
{
    if (!IsDoubleInstruction())
    {
        lastCommand_ = command;
        doubleInstruction = true;
        firstPartOfInstruction = data;
        firstPartOfInstruction <<= 16;
        registers->writeRegister(PC,registers->readRegister(PC)+align);
    }
    else
    {
        lastCommand_ = "";
        firstPartOfInstruction += data;
        data = firstPartOfInstruction;
        firstPartOfInstruction = 0;
        doubleInstruction = false;
        bool I1, J1, S, I2, J2;
        S = (data & 0x04000000);
        J1 = (data & 0x00002000);
        J2 = (data & 0x00000800);
        uint16_t imm11 = (data & 0x000007FF);
        data = data >> 16;
        uint16_t imm10 = (data & 0x03FF);
        I1 = not(J1 xor S);
        I2 = not(J2 xor S);
        uint32_t imm32 = I1;
        imm32 = imm32 << 1;
        imm32 += I2;
        imm32 = imm32 << 10;
        imm32 += imm10;
        imm32 = imm32 << 12;
        imm32 += imm11;
        imm32 = imm32 << 1;
        uint8_t oneInstruction = 0x2;
        uint8_t twoInstruction = 0x4;
        uint32_t pcVal = registers->readRegister(PC);
        if (S) {
            uint32_t total = pcVal - (imm32 + twoInstruction +align);
            registers->writeRegister(PC, total);
        }
        else {
            uint32_t total = pcVal + imm32 + oneInstruction;
            registers->writeRegister(PC, total);
        }
    }
}
bool Execute::IsDoubleInstruction() const
{
    return doubleInstruction;
}
void Execute::push(uint16_t data, std::shared_ptr<registers::Registers> &registers, std::shared_ptr<memory::Mmu>& mmu)
{
    //Only for r0-r7 + lr
    uint16_t lowReg = (data&0x01FF);
    for (auto i = 0x0; i < 8; i++)
    {
        if ((lowReg&0x0001) == 0x1)
        {
            //0-7 Reg
            mmu->WriteData32(registers->readRegister(MSP),registers->readRegister(i));
            registers->writeRegister(MSP,(registers->readRegister(MSP)-align));
        }
        lowReg >>= 1;
    }
    if (lowReg > 0)
    {
        //LR
        mmu->WriteData32(registers->readRegister(MSP),registers->readRegister(LR));
        registers->writeRegister(MSP,(registers->readRegister(MSP)-align));
    }
    registers->writeRegister(PC,(registers->readRegister(PC)+align));
}
void Execute::add_t1_sp_imm(uint16_t data, std::shared_ptr<registers::Registers> &registers)
{
    uint8_t imm8 = (data&0x00FF);
    data >>= 8;
    uint8_t reg = (data&0x0007);
    uint32_t total = registers->readRegister(MSP) + imm8;
    registers->writeRegister(reg,total);
    registers->writeRegister(PC,(registers->readRegister(PC)+align));
}
void Execute::mov_t2_reg(uint32_t data, std::shared_ptr<registers::Registers> &registers,
                         std::shared_ptr<memory::Mmu> &mmu)
{

}

} //namespace assembler
} //namespace cpu
} //namespace devices
