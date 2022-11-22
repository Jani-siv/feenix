#include <gtest/gtest.h>
#include <fstream>
#include "../../ElfLoader.hpp"

namespace debugger {
namespace unittest {

class ElfLoaderTest : public testing::Test
{
public:
    void SetUp() override
    {
        std::ofstream fd("/tmp/config.txt", std::ios_base::out);
        std::stringstream ss;
        std::string link = "LinkScript: /tmp/linkscript.ld\nDissAss: /tmp/boot1.list";
        fd.write(link.c_str(), static_cast<long>(link.length()));
        fd.close();
        ss << "MEMORY\n" << "{\n" << "rom      (rx)  : ORIGIN = 0x00000000, LENGTH = 2M\n" <<
           "ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 4M\n" << "}\n";
        fd.open("/tmp/linkscript.ld", std::ios_base::out);
        fd.write(ss.str().c_str(),static_cast<long>(ss.str().length()));
        fd.close();
        std::string data = "00000000 <_Reset>:\n"
                           "   0:\te006      \tb.n\t10 <Reset_Handler>\n"
                           "   2:\te007      \tb.n\t14 <Undefined_Instruction>\n";
        fd.open("/tmp/boot1.list",std::ios_base::out);
        fd.write(data.c_str(),static_cast<long>(data.length()));
        fd.close();
    }
    void TearDown() override
    {
        remove("/tmp/config.txt");
        remove("/tmp/linkscript.ld");
        remove("/tmp/boot1.list");
    }
};

TEST_F(ElfLoaderTest, firstTest)
{
    ElfLoader sut("/tmp/config.txt");
    auto mem = sut.GetMemoryLayout();
    for (auto i : mem)
    {
        auto payload = i.GetPayloadForMemory();
        for (auto j : payload)
        {
            for (auto k : j.dissAssData)
            {
                EXPECT_EQ(0xE006,k.second);
                break;
            }
        }
    }
    EXPECT_FALSE(sut.GetMemoryLayout().empty());
}

} // namespace unittest
} // namespace devices
