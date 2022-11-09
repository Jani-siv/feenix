#include "Init.hpp"

namespace debugger {

void Init::LoadAndCreateMemoryLayout()
{

}

Init::Init()
{
    loader = std::make_shared<ElfLoader>("/home/jani/feenix/arm/debugger/config.txt");
    std::vector<devices::memory::MemMsg> msg = loader->GetMemoryLayout();
    for (auto i : msg)
    {
        printf("DEBUG: name %s\n",i.GetMemLayout().at(0).name.c_str());
        printf("DEBUG: permission %s\n",i.GetMemLayout().at(0).permission.c_str());
        printf("DEBUG: start address %u\n",i.GetMemLayout().at(0).startingAddress);
        printf("DEBUG: memory size %u\n",i.GetMemLayout().at(0).dataLength);
    }
}

} // namespace debugger
