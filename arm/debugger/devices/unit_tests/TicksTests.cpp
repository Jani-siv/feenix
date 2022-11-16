#include <gtest/gtest.h>

#include <utility>
#include "../cpu/Ticks.hpp"

namespace devices {
namespace cpu {

class SUT : public Ticks
{
public:
    explicit SUT(std::string runMode) : Ticks(std::move(runMode))
    {

    }
    std::string readLine() override {
        std::string data = "12";
        return data;
    }
};

class TicksTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(TicksTest, stepTest)
{
    SUT sut("step");
    auto num = sut.runClock();
    EXPECT_EQ(num,0xC);
}

TEST_F(TicksTest, freerunTest)
{
    Ticks sut("free");
    auto num = sut.runClock();
    EXPECT_EQ(num,0x1);
}

} // namespace cpu
} // namespace devices
