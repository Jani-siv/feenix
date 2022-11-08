#pragma once

#include <string>
#include <map>
#include <vector>

#include "devices/memory/MemMsg.hpp"

//todo Move linkerscript in own object file
namespace debugger {

using configAttribute = std::string;
using configPath = std::string;

class ElfLoader {
public:
    explicit ElfLoader(std::string configFile);
    std::vector<devices::memory::MemMsg> GetMemoryLayout() {return memory_;}
    ~ElfLoader()=default;
private:
    void ReadConfigFile();
    void ParseMemory();
    static size_t findFirstChar(std::string& str);
    static size_t findFirstNum(std::string& str);
    void ParseMemoryLines(std::vector<std::string> memoryLines);
    void ParseSections();
    void ParseDefinitions();
    std::string configFile_;
    std::map<configAttribute ,configPath> config_;
    std::vector<devices::memory::MemMsg> memory_;
};

} // namespace debugger