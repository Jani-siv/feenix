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

TEST_F(MemoryTest, firstTest)
{
    EXPECT_TRUE(true);
}

} // namespace unittest
} // namespace memory
} // namespace devices
