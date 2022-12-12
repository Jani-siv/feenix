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

#define FLAG_Z 0x1U
#define FLAG_C 0x2U
#define FLAG_N 0x3U
#define FLAG_V 0x4U

#define SET_FLAG(flag_var, flag) ((flag_var) |= (flag))
#define CLR_FLAG(flag_var, flag) ((flag_var) &= ~(flag))
#define GET_FLAG(flag_var, flag) ((_Bool)((flag_var) & (flag)))

class Registers {
public:
    Registers();
    ~Registers()=default;
    uint32_t readRegister(uint16_t registerAddress);
    void writeRegister(uint16_t dest, uint32_t value);
    [[nodiscard]] uint8_t GetConditionFlags() const {return apsr_;}
    void SetConditionFlag(std::string flag);
    void ClearConditionFlags() {apsr_ = 0x0;}
private:
    void InitRegisters();
    void FillRegistersWithZeros();
    std::map<uint16_t,uint32_t*> RegisterMap_;
    uint32_t gpRegisters_[gpRegisterSize]{};
    uint32_t psRegisters_[psRegisterSize]{};
    uint8_t apsr_ = 0x0;
};

} // namespace registers
} // namespace devices
