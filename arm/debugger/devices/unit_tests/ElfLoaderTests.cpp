#include <gtest/gtest.h>
#include "../../ElfLoader.hpp"

namespace debugger {
namespace unittest {

class ElfLoaderTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(ElfLoaderTest, firstTest)
{
    ElfLoader sut("/home/jani/feenix/arm/debugger/config.txt");
    EXPECT_TRUE(true);
}

} // namespace unittest
} // namespace devices
