#include <gtest/gtest.h>

#include <utility>
#include "../cpu/Core.hpp"
#include "../../ElfLoader.hpp"

namespace devices {
namespace cpu {

class TIC : public Ticks
{
public:
    explicit TIC(std::string runMode) : Ticks(std::move(runMode)){}
    std::string readLine() override {
        std::string data = "1";
        return data;
    }
};
//todo need modify this test class so override is better
class SUT : public Core
{
public:
    explicit SUT(std::vector<devices::memory::MemMsg> msg) : Core(std::vector<devices::memory::MemMsg>(std::move(msg))){}
    void dumpMemoryInFile(std::string filename, uint32_t startAddress, uint32_t len) override{}
    uint32_t comm{};
    [[nodiscard]] uint32_t GetTestValue() const {return comm;}
    std::shared_ptr<Ticks> clock_;
    void SetCoreDebugMode(const std::string& mode) override {
        clock_ = std::make_shared<TIC>("step");
    }
    void StartCore() override {
        while(true)
        {
            uint64_t tic = clock_->runClock();
            for (auto i = 0; i<tic; i++)
            {
                uint32_t address = ReadPCRegister();
                uint32_t command = GetCommandFromMemory(address);
                comm = command;
            }
            break;
        }
    }
};



class CoreTest : public testing::Test
{
public:
    void SetUp() override
    {}
    void TearDown() override
    {}
};

TEST_F(CoreTest, firstTest)
{
    debugger::ElfLoader loader("/home/jani/feenix/arm/debugger/config.txt");
    std::vector<devices::memory::MemMsg> msg = loader.GetMemoryLayout();
    SUT Core(msg);
    Core.SetCoreDebugMode("step");
    Core.StartCore();
    EXPECT_EQ(3925868550,Core.GetTestValue());
}

} // namespace cpu
} // namespace devices
