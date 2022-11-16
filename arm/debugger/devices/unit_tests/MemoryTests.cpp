#include <gtest/gtest.h>
#include "../memory/Memory.hpp"

namespace devices {
namespace memory {
namespace unittest {

class MemoryTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(MemoryTest, IOmemory)
{
    Memory sut;
    sut.allocateMemory(0x1000,"RW");
    sut.WriteMemory32(0x0, 0xA01BABCD);
    EXPECT_EQ(0xA01BABCD, sut.ReadMemory32(0x0));
    EXPECT_EQ(0x0, sut.ReadMemory32(0x5000));
    Memory sut1;
    sut1.allocateMemory(0x1000, "R");
    sut1.WriteMemory32(0x0, 0xBEEF);
    EXPECT_EQ(0x0, sut1.ReadMemory32(0x0));
    EXPECT_EQ(0x1000, sut1.GetMemorySize());
}

} // namespace unittest
} // namespace memory
} // namespace devices
