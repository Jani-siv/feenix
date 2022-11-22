#include "Execute.hpp"

namespace devices {
namespace cpu {
namespace assembler {

constexpr uint8_t align = 0x2;

void Execute::executeCommand(std::string command, uint32_t data,
                             std::shared_ptr<registers::Registers> &registers)
{
    if(command=="B_T2") { b_t2(data, registers);}
}
void Execute::b_t2(uint16_t command, std::shared_ptr<registers::Registers> &registers)
{
    //todo reset handler not in correct place in memory
    command = (command&0x7FF);
    command = command  * align + registers->readRegister(PC) + align;
    registers->writeRegister(PC,command);
}

} //namespace assembler
} //namespace cpu
} //namespace devices
