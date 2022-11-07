#include <gtest/gtest.h>
#include "../memory/Sections.hpp"

namespace devices {
namespace memory {
namespace unittest {

class SectionsTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(SectionsTest, firstTest)
{
    Sections sut;
    sut.InitSection(0x20000000, 0x9c);
    EXPECT_EQ(0x9c, sut.GetLmaMapping(0x20000000));
}

} // namespace unittest
} // namespace memory
} // namespace devices
