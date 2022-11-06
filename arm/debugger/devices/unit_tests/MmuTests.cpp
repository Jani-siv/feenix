#include <gtest/gtest.h>
#include "../memory/Mmu.hpp"

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
    sut.CreateMemory("RAM", 0x20000000, 2000000, "RW");
    sut.CreateSections(".text",0x20000000,0x9c);
    sut.WriteData8(0x20000000, 0xBE);
    EXPECT_EQ(sut.ReadData8(0x20000000), 0xBE);
    sut.WriteData16(0x20000000, 0xBEEF);
    EXPECT_EQ(sut.ReadData16(0x20000000), 0xBEEF);
    sut.WriteData32(0x20000000, 0xDEADBEEF);
    EXPECT_EQ(sut.ReadData32(0x20000000), 0xDEADBEEF);
}

} // namespace unittest
} // namespace memory
} // namespace devices
