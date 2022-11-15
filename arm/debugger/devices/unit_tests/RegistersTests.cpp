#include <gtest/gtest.h>
#include "../registers/Registers.hpp"

namespace devices {
namespace registers {
namespace unittest {

class RegistersTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(RegistersTest, readRegister)
{
    Registers sut;
    EXPECT_EQ(0x0,sut.readRegister(0x0));
    EXPECT_EQ(0xFFFFFFFF,sut.readRegister(0xFF));
}

TEST_F(RegistersTest, writeRegister)
{
    Registers sut;
    sut.writeRegister(0x5,0xDEADBEEF);
    EXPECT_EQ(0xDEADBEEF,sut.readRegister(0x5));
}

} // namespace unittest
} // namespace registers
} // namespace devices
