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

using addr = uint32_t;
using payload = uint32_t;

struct DissAss {
    std::vector<std::pair<addr,payload>> dissAssData;
};

class MemMsg
{
public:
    MemMsg()=default;
    ~MemMsg()=default;
    void SaveLayout(MemoryLayout layout) {layout_.push_back(layout);}
    void SavePayload(DissAss load) {payload_.push_back(load);}
    std::vector<MemoryLayout> GetMemLayout() {return layout_;}
    std::vector<DissAss> GetPayloadForMemory() { return payload_;}
private:
    std::vector<MemoryLayout> layout_;
    std::vector<DissAss> payload_;
};

} // namespace memory
} // namespace devices
