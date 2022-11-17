#include "Core.hpp"

namespace devices {
namespace cpu {

constexpr auto MSP = 13;
constexpr auto PSP = 14;
constexpr auto LR = 15;
constexpr auto PC = 16;

Core::Core(std::vector<devices::memory::MemMsg> msg)
{
    registers_ = std::make_shared<registers::Registers>();
    mmu_ = std::make_shared<memory::Mmu>();
    mmu_->CreateMemory(msg);
    dumpMemoryInFile("dump.txt", 0x0, 0x100);
    //Set program counter to 0;
    registers_->writeRegister(PC,0x0);
}

void Core::SetCoreDebugMode(const std::string& mode)
{
    clock_ = std::make_shared<Ticks>(mode);
}
void Core::StartCore()
{
    size_t block = 0;
    while(true)
    {
        uint64_t tic = clock_->runClock();
        for (auto i = 0; i<tic; i++)
        {
            uint32_t address = ReadPCRegister();
            uint32_t command = GetCommandFromMemory(address);
            printf("0x%x:0x%X\n",address,command);
            registers_->writeRegister(PC,registers_->readRegister(PC)+0x4);
            //todo parse command and make it happend
            //todo add +1 to PC if assembly not override this
        }
        if (block == 10) {
            break;
        }
        block++;
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
void Core::dumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t len)
{
    mmu_->DumpMemoryInFile(filename, startAddress, len);
}

} // namespace cpu
} // namespace devices
