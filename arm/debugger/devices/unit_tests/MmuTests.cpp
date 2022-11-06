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
    sut.CreateSections(".text",0x8,0x20000000,0x9c);
    sut.WriteData32(0x20000000, 0xFF);
    EXPECT_EQ(sut.ReadData32(0x20000000), 0xFF);
}

} // namespace unittest
} // namespace memory
} // namespace devices