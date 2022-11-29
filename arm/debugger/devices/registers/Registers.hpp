#pragma once

#include <string>
#include <map>
//https://developer.arm.com/documentation/dui0552/a/the-cortex-m3-processor/programmers-model/core-registers?lang=en
namespace devices {
namespace registers {

constexpr auto MSP = 13;
constexpr auto PSP = 14;
constexpr auto LR = 15;
constexpr auto PC = 16;
constexpr auto gpRegisterSize =17u;
constexpr auto psRegisterSize = 5u;

class Registers {
public:
    Registers();
    ~Registers()=default;
    uint32_t readRegister(uint16_t registerAddress);
    void writeRegister(uint16_t dest, uint32_t value);
private:
    void InitRegisters();
    void FillRegistersWithZeros();
    std::map<uint16_t,uint32_t*> RegisterMap_;
    uint32_t gpRegisters_[gpRegisterSize]{};
    uint32_t psRegisters_[psRegisterSize]{};
};

} // namespace registers
} // namespace devices
