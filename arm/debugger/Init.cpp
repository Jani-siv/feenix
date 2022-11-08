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
        printf("DEBUG:%s\n",i.GetMemLayout().at(0).name.c_str());
        printf("DEBUG:%s\n",i.GetMemLayout().at(0).permission.c_str());
        printf("DEBUG:%u\n",i.GetMemLayout().at(0).startingAddress);
        printf("DEBUG:%u\n",i.GetMemLayout().at(0).dataLength);
    }
}

} // namespace debugger
