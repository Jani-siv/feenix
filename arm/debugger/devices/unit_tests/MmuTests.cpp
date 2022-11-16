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
    sut.WriteData32(0x20000000, 0xDEADBEEF);
    EXPECT_EQ(sut.ReadData32(0x20000000), 3735928559);
}

} // namespace unittest
} // namespace memory
} // namespace devices
