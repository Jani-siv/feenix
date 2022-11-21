#pragma once

#include <cstdint>
#include <vector>
#include <fstream>

namespace devices {

class Dumpper {
public:
    Dumpper()=default;
    ~Dumpper()=default;
    void SetDumpFilename(std::string filename);
    void DumpMemoryDataToFile(std::vector<uint32_t>& data) const;
    void DumpMemoryDataToFile(std::vector<uint16_t>& data) const;
    void DumpMemoryDataToFile(std::vector<uint8_t>& data) const;
private:
    [[nodiscard]] std::string ConvertUint8ToString(uint8_t num) const;
    void WriteData(const std::string& dumpData) const;
    std::string filename_;
};

} // namespace devices
