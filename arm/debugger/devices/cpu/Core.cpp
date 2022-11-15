#include "Core.hpp"

namespace devices {
namespace cpu {

constexpr auto MSP = 13;
constexpr auto PSP = 14;
constexpr auto LR = 15;
constexpr auto PC = 16;

Core::Core()
{
    registers_ = std::make_shared<registers::Registers>();
    mmu_ = std::make_shared<memory::Mmu>();
    //Set program counter to 0;
    registers_->writeRegister(PC,0x0);
    //Init ticks

}
} // namespace cpu
} // namespace devices
