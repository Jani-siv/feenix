#include <gtest/gtest.h>
#include "../memory/Mmu.hpp"
#include "../../ElfLoader.hpp"
debugger::ElfLoader loader("/home/jani/feenix/arm/debugger/config.txt");
namespace devices {
namespace memory {
namespace unittest {

class MmuTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(MmuTest, memoryAllocation)
{
    Mmu sut;
    std::vector<MemMsg> msg = loader.GetMemoryLayout();
    sut.CreateMemory(msg);
    sut.CreateSections(".text",0x20000000,0x9c);
    sut.WriteData8(0x20000000, 0xBE);
    EXPECT_EQ(sut.ReadData8(0x20000000), 0xBE);
    sut.WriteData16(0x20000000, 0xBEEF);
    EXPECT_EQ(sut.ReadData16(0x20000000), 0xBEEF);
    sut.WriteData32(0x20000000, 0xDEADBEEF);
    EXPECT_EQ(sut.ReadData32(0x20000000), 0xDEADBEEF);
    printf("Name: %s\n",sut.getMemoryName(0x0).c_str());
    printf("Name: %s\n",sut.getMemoryName(0x20000000).c_str());
}

} // namespace unittest
} // namespace memory
} // namespace devices
