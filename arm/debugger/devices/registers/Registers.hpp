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
    uint32_t readRegister(std::string registerAddress);
    void writeRegister(std::string dest, uint32_t value);
private:
    void InitRegisters();
    std::map<std::string,uint32_t*> RegisterMap_;
    uint32_t gpRegisters_[gpRegisterSize]{};
    uint32_t psRegisters_[psRegisterSize]{};
};

} // namespace registers
} // namespace devices
