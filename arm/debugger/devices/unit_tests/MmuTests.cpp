#include <gtest/gtest.h>
#include "../memory/Mmu.hpp"
#include "../../ElfLoader.hpp"

namespace devices {
namespace memory {
namespace unittest {
//todo setup and teardown in own class
class MmuTest : public testing::Test
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
        std::string data = "00000000 <_Reset>:\n    0:\tea000006 \tb\t20 <Reset_Handler>\n";
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

TEST_F(MmuTest, memoryAllocation)
{
    debugger::ElfLoader loader("/tmp/config.txt");
    Mmu sut;
    std::vector<MemMsg> msg = loader.GetMemoryLayout();
    sut.CreateMemory(msg);
    sut.WriteData32(0x0, 0xDEAD);
    EXPECT_EQ(sut.ReadData32(0x0), 0xDEAD);
}

} // namespace unittest
} // namespace memory
} // namespace devices
