#include <gtest/gtest.h>
#include "../cpu/assembler/Execute.hpp"
#include "../registers/Registers.hpp"

namespace devices {
namespace cpu {
namespace assembler {
namespace tests {

class ExecuteTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(ExecuteTest, firstTest)
{
    std::shared_ptr<registers::Registers> reg = std::make_shared<registers::Registers>();
    Execute SUT;

    SUT.executeCommand("B_T2", 0xE006, reg);
    EXPECT_EQ(0x12,reg->readRegister(PC));
    reg->writeRegister(PC,0x12);
    SUT.executeCommand("BL", 0xf000,reg);
    SUT.executeCommand("nope", 0xf809,reg);
    EXPECT_EQ(0x28,reg->readRegister(PC));
}

} //namespace tests
} //namespace assembler
} //namespace cpu
} //namespace devices