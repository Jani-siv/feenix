#include "Init.hpp"
#include "devices/memory/Memory.hpp"
#include "devices/memory/Mmu.hpp"
#include "devices/cpu/Core.hpp"


namespace debugger {

Init::Init()
{
    loader = std::make_shared<ElfLoader>("/home/jani/feenix/arm/debugger/config.txt");
    std::vector<devices::memory::MemMsg> msg = loader->GetMemoryLayout();
    std::shared_ptr<devices::cpu::Core> core = std::make_shared<devices::cpu::Core>(msg);
    core->SetCoreDebugMode("step");
    core->StartCore();

    for (auto i : msg)
    {
        printf("DEBUG: name %s\n",i.GetMemLayout().at(0).name.c_str());
        printf("DEBUG: permission %s\n",i.GetMemLayout().at(0).permission.c_str());
        printf("DEBUG: start address %u\n",i.GetMemLayout().at(0).startingAddress);
        printf("DEBUG: memory size %u\n",i.GetMemLayout().at(0).dataLength);
    }
    devices::memory::Mmu mmu;
    mmu.CreateMemory(msg);
    mmu.DumpMemoryInFile("testi.txt", 0x0, 0x98);
}

} // namespace debugger
