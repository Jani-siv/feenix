#include <fstream>
#include "ElfLoader.hpp"

namespace debugger {

ElfLoader::ElfLoader(std::string configFile)
{
    configFile_ = configFile;
    ReadConfigFile();
}
void ElfLoader::ReadConfigFile()
{
    std::ifstream fd(configFile_, std::ios_base::in);
    if (!fd.is_open())
    {
        printf("Could not open config file:%s\n",configFile_.c_str());
        return;
    }
    while (!fd.eof())
    {
        std::string line;
        std::getline(fd,line);
        if (line.find('#') > 0)
        {
            auto endpos = line.find(':');
            configAttribute att = line.substr(0,endpos);
            config_[att]= line.substr(endpos+2,line.length()-(endpos+2));
            for (auto& i : config_) {
                printf("DEBUG: %s\n", i.first.c_str());
                printf("DEBUG: %s\n", i.second.c_str());
            }
        }

    }
}
} // namespace debugger