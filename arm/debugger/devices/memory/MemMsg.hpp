#pragma once

#include <string>
#include <vector>

namespace devices {
namespace memory {

struct MemoryLayout {
    std::string name{};
    std::basic_string<char> permission{};
    uint32_t startingAddress{};
    uint32_t dataLength{};
};

class MemMsg
{
public:
    MemMsg()=default;
    ~MemMsg()=default;
    void SaveLayout(devices::memory::MemoryLayout layout) {layout_.push_back(layout);}
    std::vector<MemoryLayout> GetMemLayout() {return layout_;}
private:
    std::vector<MemoryLayout> layout_;
};

} // namespace memory
} // namespace devices
