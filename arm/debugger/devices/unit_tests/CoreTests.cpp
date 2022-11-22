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
    {
        std::ofstream fd("/tmp/config.txt", std::ios_base::out);
        std::stringstream ss;
        std::string link = "LinkScript: /tmp/linkscript.ld\nDissAss: /tmp/boot1.list";
        fd.write(link.c_str(), static_cast<long>(link.length()));
        fd.close();
        ss << "MEMORY\n" << "{\n" << "rom      (rx)  : ORIGIN = 0x00000000, LENGTH = 2M\n" <<
           "ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 4M\n" << "}\n";
        fd.open("/tmp/linkscript.ld", std::ios_base::out);
        fd.write(ss.str().c_str(),static_cast<long>(ss.str().length()));
        fd.close();
        std::string data = "00000000 <_Reset>:\n    0:\tea000006 \tb\t20 <Reset_Handler>\n";
        fd.open("/tmp/boot1.list",std::ios_base::out);
        fd.write(data.c_str(),static_cast<long>(data.length()));
        fd.close();
    }
    void TearDown() override
    {
        remove("/tmp/config.txt");
        remove("/tmp/linkscript.ld");
        remove("/tmp/boot1.list");
    }
};

TEST_F(CoreTest, firstTest)
{
    debugger::ElfLoader loader("/tmp/config.txt");
    std::vector<devices::memory::MemMsg> msg = loader.GetMemoryLayout();
    SUT Core(msg);
    Core.SetCoreDebugMode("step");
    Core.StartCore();
    EXPECT_EQ(0,Core.GetTestValue());
}

} // namespace cpu
} // namespace devices
