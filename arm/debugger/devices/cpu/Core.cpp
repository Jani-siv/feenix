#include "Core.hpp"

namespace devices {
namespace cpu {

constexpr auto MSP = 13;
constexpr auto PSP = 14;
constexpr auto LR = 15;
constexpr auto PC = 16;

Core::Core(const std::vector<devices::memory::MemMsg>& msg)
{
    registers_ = std::make_shared<registers::Registers>();
    mmu_ = std::make_shared<memory::Mmu>();
    mmu_->CreateMemory(msg);
    dumpMemoryInFile("dump.txt", 0x0, 0x100);
    //set MSP address
    registers_->writeRegister(MSP,mmu_->ReadData32(0x0));
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
            uint16_t command = GetCommandFromMemory(address);
            printf("0x%x:0x%X\n",address,command);
            printf("%s\n", assembler_->GetThumbCode(command).c_str());
            assembler::Execute::executeCommand(assembler_->GetThumbCode(command),
                                               command,registers_,mmu_);
            //todo add align in execute class
            //registers_->writeRegister(PC,registers_->readRegister(PC)+0x2);
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
    return mmu_->ReadData16(address);
}
void Core::dumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t len)
{
    mmu_->DumpMemoryInFile(filename, startAddress, len);
}

} // namespace cpu
} // namespace devices
