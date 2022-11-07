#pragma once

#include <string>
#include <map>
#include <vector>
//todo Move linkerscript in own object file
namespace debugger {

struct memoryDev {
    std::string name{};
    uint8_t permission{};
    uint32_t origin{};
    uint32_t dataLength{};
};

using configAttribute = std::string;
using configPath = std::string;

class ElfLoader {
public:
    explicit ElfLoader(std::string configFile);
    ~ElfLoader()=default;
private:
    void ReadConfigFile();
    void ParseMemory();
    void ParseSections();
    void ParseDefinitions();
    std::string configFile_;
    std::map<configAttribute ,configPath> config_;
    std::vector<memoryDev> memDev_;
};

} // namespace debugger