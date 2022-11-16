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
}

void Core::SetCoreDebugMode(const std::string& mode)
{
    clock_ = std::make_shared<Ticks>(mode);
}
void Core::StartCore()
{
    while(true)
    {
        uint64_t tic = clock_->runClock();
        for (auto i = 0; i<tic; i++)
        {
            uint32_t address = ReadPCRegister();
            uint32_t command = GetCommandFromMemory(address);
            //todo parse command and make it happend
            //todo add +1 to PC if assembly not override this
        }
        break;
    }
}
uint32_t Core::ReadPCRegister()
{
    return registers_->readRegister(PC);
}
uint32_t Core::GetCommandFromMemory(uint32_t address)
{
    return mmu_->ReadData32(address);
}

} // namespace cpu
} // namespace devices
