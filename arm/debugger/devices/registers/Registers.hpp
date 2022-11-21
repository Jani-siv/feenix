#pragma once

#include <string>
#include <map>

namespace devices {
namespace registers {

constexpr auto gpRegisterSize =17u;
constexpr auto psRegisterSize = 5u;

class Registers {
public:
    Registers();
    ~Registers()=default;
    uint32_t readRegister(uint8_t registerAddress);
    void writeRegister(uint8_t dest, uint32_t value);
private:
    void InitRegisters();
    void FillRegistersWithZeros();
    std::map<uint8_t,uint32_t*> RegisterMap_;
    uint32_t gpRegisters_[gpRegisterSize]{};
    uint32_t psRegisters_[psRegisterSize]{};
};

} // namespace registers
} // namespace devices
