#include "Registers.hpp"
#include <algorithm>
#include <stdexcept>

namespace devices {
namespace registers {

Registers::Registers()
{
    InitRegisters();
}

uint32_t Registers::readRegister(std::string registerAddress)
{
    auto pointer = RegisterMap_.find(registerAddress);
    if (pointer != RegisterMap_.end()) {
        uint32_t val = *pointer->second;
        return val;
    }
    return 0xFFFFFFFF;
}

void Registers::writeRegister(std::string dest, uint32_t value)
{
    auto pointer = RegisterMap_.find(dest);
    if (pointer != RegisterMap_.end()) {
        *pointer->second = value;
    }
}

void Registers::InitRegisters()
{
    for(auto i = 0; i < gpRegisterSize; i++)
    {
        gpRegisters_[i]=0x0;
    }
    for(auto i = 0; i < psRegisterSize; i++)
    {
        psRegisters_[i]=0x0;
    }
    for (auto i=0; i < (gpRegisterSize-4); i++)
    {
        std::string reg="r"+std::to_string(i);
        RegisterMap_[reg]=&gpRegisters_[i];
    }
    RegisterMap_["MSP"]=&gpRegisters_[13];
    RegisterMap_["PSP"]=&gpRegisters_[14];
    RegisterMap_["LR"]=&gpRegisters_[15];
    RegisterMap_["PC"]=&gpRegisters_[16];
}

} // namespace registers
} // namespace devices
