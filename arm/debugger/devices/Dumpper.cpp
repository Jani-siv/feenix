#include "Dumpper.hpp"

#include <utility>
#include <sstream>
#include <map>

namespace devices {

void Dumpper::DumpMemoryDataToFile(std::vector<uint32_t>& data) const
{
    std::vector<uint16_t> data16{};
    for (auto &i : data)
    {
        uint16_t low = (i & 0x0000FFFF);
        i = i >> 16;
        uint16_t high = i;
        data16.push_back(high);
        data16.push_back(low);
    }
    DumpMemoryDataToFile(data16);
}

void Dumpper::DumpMemoryDataToFile(std::vector<uint16_t>& data) const
{
    std::vector<uint8_t> data8{};
    for (auto& i : data)
    {
        uint8_t low = (i & 0x00FF);
        i = i >> 8;
        uint8_t high = i;
        data8.push_back(high);
        data8.push_back(low);
    }

    DumpMemoryDataToFile(data8);
}

void Dumpper::DumpMemoryDataToFile(std::vector<uint8_t>& data) const
{
    std::stringstream ss;
    size_t counter = 0;
    for (auto &i : data)
    {
        ss << std::hex << ConvertUint8ToString(i) << " ";
        if ((counter+1) %8 == 0)
        {
            ss << "\n";
        }
        else if (counter+1 % 2 == 0)
        {
            ss << " ";
        }
        counter++;
    }
    std::string dumpData;
    dumpData = ss.str();
    WriteData(dumpData);
}

void Dumpper::SetDumpFilename(std::string filename)
{
    filename_ = std::move(filename);
}

std::string Dumpper::ConvertUint8ToString(uint8_t num) const
{
    std::map<uint8_t, std::string> mapper;
    mapper[0x0]="0";
    mapper[0x1]="1";
    mapper[0x2]="2";
    mapper[0x3]="3";
    mapper[0x4]="4";
    mapper[0x5]="5";
    mapper[0x6]="6";
    mapper[0x7]="7";
    mapper[0x8]="8";
    mapper[0x9]="9";
    mapper[0xa]="A";
    mapper[0xb]="B";
    mapper[0xc]="C";
    mapper[0xd]="D";
    mapper[0xe]="E";
    mapper[0xf]="F";
    std::string data{};
    uint8_t low = (num & 0x0F);
    num = num >> 4;
    uint8_t high = num;
    auto it = mapper.find(high);
    data = it->second;
    it = mapper.find((low));
    data += it->second;
    return data;
}

void Dumpper::WriteData(const std::string& dumpData) const
{
    std::fstream fd("/tmp/" + filename_, std::ios_base::out);
    fd.write(dumpData.c_str(),static_cast<long>(dumpData.length()));
    fd.close();
}

} // namespace devices
