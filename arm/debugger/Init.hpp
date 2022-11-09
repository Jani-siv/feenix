#pragma once

#include <memory>
#include "ElfLoader.hpp"
#include "devices/memory/MemMsg.hpp"

namespace debugger {

class Init {
public:
    Init();
    ~Init()=default;
    void LoadAndCreateMemoryLayout();
private:
    std::shared_ptr<ElfLoader> loader;
};

} // namespace debugger
