#include <gtest/gtest.h>
#include "../cpu/Core.hpp"

namespace devices {
namespace cpu {

class CoreTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
    devices::cpu::Core Core;
};

TEST_F(CoreTest, firstTest)
{
    EXPECT_TRUE(true);
}

} // namespace cpu
} // namespace devices
