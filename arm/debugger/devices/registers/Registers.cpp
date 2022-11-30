#include "Registers.hpp"
#include <algorithm>
#include <stdexcept>

namespace devices {
namespace registers {

Registers::Registers()
{
    InitRegisters();
}

uint32_t Registers::readRegister(uint16_t registerAddress)
{
    auto pointer = RegisterMap_.find(registerAddress);
    if (pointer != RegisterMap_.end()) {
        return *pointer->second;
    }
    return 0xFFFFFFFF;
}

void Registers::writeRegister(uint16_t dest, uint32_t value)
{
    auto pointer = RegisterMap_.find(dest);
    if (pointer != RegisterMap_.end()) {
        *pointer->second = value;
    }
}

void Registers::InitRegisters()
{
    for(unsigned int & gpRegister : gpRegisters_)
    {
        gpRegister=0x0;
    }
    for(unsigned int & psRegister : psRegisters_)
    {
        psRegister=0x0;
    }
    for (auto i=0; i < gpRegisterSize; i++)
    {
        uint32_t* ptr;
        ptr = &gpRegisters_[i];
        RegisterMap_[i]=ptr;
    }
    writeRegister(MSP,0x0);
    writeRegister(LR,0xFFFFFFFF);
    writeRegister(PC,0x2);
}
void Registers::SetConditionFlag(std::string flag)
{
    if(flag == "Z")
    {
        SET_FLAG(apsr_,FLAG_Z);
    }
    if(flag == "C")
    {
        SET_FLAG(apsr_,FLAG_C);
    }
    if(flag == "N")
    {
        SET_FLAG(apsr_,FLAG_N);
    }
    if(flag == "V")
    {
        SET_FLAG(apsr_,FLAG_V);
    }
}

} // namespace registers
} // namespace devices
