#include "ElfLoader.hpp"
#include <fstream>
#include <utility>
#include "devices/memory/MemMsg.hpp"

namespace debugger {

ElfLoader::ElfLoader(std::string configFile)
{
    configFile_ = std::move(configFile);
    ReadConfigFile();
    ParseMemory();
    ParseDissAss();
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
        }
    }
}

void ElfLoader::ParseMemory()
{
    auto pointer = config_.find("LinkScript");
    if (pointer!= config_.end()) {
        std::ifstream fd(pointer->second.c_str(), std::ios_base::in);
        std::string line;
        std::vector<std::string> memoryConfigLines;
        uint8_t saveMemoryDataToString = 0x0;
        while (!fd.eof()) {
            std::getline(fd, line);
            if (line.find('}') < line.length()) {
                saveMemoryDataToString = 0x4;
            }
            else if (saveMemoryDataToString == 0x3 && line.find('}') > line.length()) {
                memoryConfigLines.push_back(line);
            }
            else if (line.find("MEMORY") < line.length()) {
                saveMemoryDataToString = 0x1;
            }
            else if (line.find('{') != line.length() && saveMemoryDataToString == 0x1) {
                saveMemoryDataToString = (saveMemoryDataToString ^ 0x2);
            }
        }
        ParseMemoryLines(memoryConfigLines);
    }
    else
    {
        //todo error handling
        return;
    }
}

size_t ElfLoader::findFirstChar(std::string& str)
{
    for (auto i = 0; i < str.length(); i++)
    {
        if (std::isalpha(str[i]))
        {
            return i;
        }
    }
    return str.length()+1;
}

size_t ElfLoader::findFirstNum(std::string &str)
{
    for (auto i = 0; i < str.length(); i++)
    {
        if (std::isdigit(str[i]))
        {
            return i;
        }
    }
    return str.length()+1;
}

void ElfLoader::ParseMemoryLines(std::vector<std::string> memoryLines)
{
    for (auto& i : memoryLines)
    {
        struct devices::memory::MemoryLayout layout;
        devices::memory::MemMsg message;
        /*Parsing file is ugly*/
        i = i.substr(findFirstChar(i), i.length()- findFirstChar(i));
        auto pos = i.find(' ');
        layout.name  = i.substr(0,pos);
        i = i.substr(i.find('(')+1, i.length()-i.find('(')+1);
        layout.permission = i.substr(0, i.find(')'));
        i = i.substr(i.find("0x")+2,i.length()-i.find("0x")+2);
        layout.startingAddress = std::stoul(i.substr(0,i.find(' ')-1));
        i = i.substr(i.find('='),i.length()-i.find('='));
        if (i.find('M') != std::string::npos)
        {
            layout.dataLength = 1000000;
            i = i.substr(findFirstNum(i), i.length()- findFirstNum(i)-1);
            layout.dataLength *= std::stoi(i);
        }
        else if (i.find('K') != std::string::npos)
        {
            layout.dataLength = 1000;
            i = i.substr(findFirstNum(i), i.length()- findFirstNum(i)-1);
            layout.dataLength *= std::stoi(i);
        }
        else
        {
            i = i.substr(findFirstNum(i), i.length()- findFirstNum(i));
            layout.dataLength = std::stoi(i);
        }
        message.SaveLayout(layout);
        memory_.push_back(message);
    }
}
void ElfLoader::ParseDissAss()
{
    //todo combine file opening in own function
    auto pointer = config_.find("DissAss");
    if (pointer!= config_.end()) {
        std::ifstream fd(pointer->second.c_str(), std::ios_base::in);
        std::string originline;
        devices::memory::DissAss dissAss;
        while(!fd.eof())
        {
            std::getline(fd, originline);
            if (findFirstNum(originline) > 1 && findFirstNum(originline) < originline.length() && findFirstChar(originline) > 1)
            {

                (findFirstChar(originline) < findFirstNum(originline))?
                originline = FirstIsChar(originline):
                    originline = FirstIsNum(originline);

                std::string address = originline.substr(0, originline.find(':'));
                std::string value = originline.substr(originline.find(":\t") + 2, originline.length() - originline.find(":\t"));
                auto pos = value.find(" ");
                if (pos < 6)
                {
                if (value.at(pos+1) != ' ' && pos+1 < value.length())
                {
                    //special case two 16 bits in one line
                    AddTwoAddressAndValue(address,value,dissAss);
                }
                else {
                AddOneAddressAndValue(address,value,dissAss);
                }
                }
            }
        }
        auto it = memory_.begin();
        it->SavePayload(dissAss);
    }
}
std::string ElfLoader::FirstIsChar(std::string originline)
{
    return originline.substr(findFirstChar(originline), originline.find(" \t") - findFirstChar(originline));
}
std::string ElfLoader::FirstIsNum(std::string originline)
{
    return originline.substr(findFirstNum(originline), originline.find(" \t") - findFirstNum(originline));
}
void ElfLoader::AddOneAddressAndValue(std::string address, std::string value,devices::memory::DissAss& dissAss)
{
    //printf("DEBUG:%s:%s\n", address.c_str(), value.c_str());
    std::pair<devices::memory::addr ,devices::memory::payload > test;
    value = value.substr(0, value.find(' '));
    test = std::make_pair(std::stoul(address, nullptr, 16), std::stoul(value, nullptr, 16));
    dissAss.dissAssData.push_back(test);

}
void ElfLoader::AddTwoAddressAndValue(std::string address, std::string value,devices::memory::DissAss& dissAss)
{
    std::string val1 = value.substr(0,value.find(' ')+1);
    std::string val2 = value.substr(value.find(' ')+1,value.length());
    AddOneAddressAndValue(address,val1,dissAss);
    uint16_t addr = std::stoul(address, nullptr) + 0x2;
    std::string address2 = std::to_string(addr);
    AddOneAddressAndValue(address2,val2,dissAss);
}

} // namespace debugger
