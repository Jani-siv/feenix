#include <gtest/gtest.h>
#include "../Dumpper.hpp"

namespace devices {
namespace unittest {

class DumpperTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(DumpperTest, firstest)
{
    Dumpper sut;
    sut.SetDumpFilename("testing.txt");
    std::vector<uint8_t> test;
    for (uint16_t i = 0x00; i < 0x100; i++)
    {
        test.push_back(i);
    }
    sut.DumpMemoryDataToFile(test);
}

} // namespace unittest
} // namespace devices
