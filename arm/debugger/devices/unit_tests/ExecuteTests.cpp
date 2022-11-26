#include <gtest/gtest.h>
#include "../cpu/assembler/Execute.hpp"
#include "../registers/Registers.hpp"
#include "../memory/Mmu.hpp"
namespace devices::memory {
class MEM : public Mmu
{
public:
    MEM() = default;
    ~MEM() = default;
    void WriteData32(uint32_t address, uint32_t data) override
    {
        data_.emplace_back(address, data);
    }
    uint32_t ReadData32(uint32_t address) override
    {
        return GetData();
    }
    uint32_t GetData()
    {
        uint32_t val = data_.at(datapoint).second;
        datapoint++;
        return val;
    }
    std::vector<std::pair<uint32_t, uint32_t>> data_;
    uint8_t datapoint = 0;
};
} // namespace

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
    std::shared_ptr<registers::Registers> reg = std::make_shared<registers::Registers>();
    Execute SUT;
};

TEST_F(ExecuteTest, firstTest)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    reg->writeRegister(PC,0x2);
    SUT.executeCommand("B_T2", 0xE006, reg,mem);
    EXPECT_EQ(0x12,reg->readRegister(PC));
    reg->writeRegister(PC,0x2c);
    SUT.executeCommand("B_T2", 0xE007, reg,mem);
    EXPECT_EQ(0x3e,reg->readRegister(PC));
}

TEST_F(ExecuteTest, BLPlus)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    reg->writeRegister(PC,0x12);
    SUT.executeCommand("BL", 0xf000,reg,mem);
    SUT.executeCommand("nope", 0xf809,reg,mem);
    EXPECT_EQ(0x28,reg->readRegister(PC));
}

TEST_F(ExecuteTest, BLMinus)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    reg->writeRegister(PC,0x28);
    SUT.executeCommand("BL", 0xf400,reg,mem);
    SUT.executeCommand("nope", 0xC009,reg,mem);
    EXPECT_EQ(0x12,reg->readRegister(PC));
}

TEST_F(ExecuteTest, Push_t1Reg7LR)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    reg->writeRegister(0x7,0x28);
    reg->writeRegister(LR,0x24);
    reg->writeRegister(MSP,0x20);
    SUT.executeCommand("PUSH_T1", 0xb580,reg,mem);
    //2 commands 0x20 - 0x1C
    EXPECT_EQ(0x1C,reg->readRegister(MSP));
    //override command ReadData32 First is R7 and then LR
    EXPECT_EQ(0x28,mem->ReadData32(0x0));
    EXPECT_EQ(0x24,mem->ReadData32(0x0));
}

TEST_F(ExecuteTest, Push_t1_07regNoLR)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    for (uint32_t i = 0x0; i < 0x8; i++)
    {
        reg->writeRegister(i,i);
    }
    reg->writeRegister(LR,0x24);
    reg->writeRegister(MSP,0x20);
    SUT.executeCommand("PUSH_T1", 0xb4FF,reg,mem);
    EXPECT_EQ(0x10,reg->readRegister(MSP));
    for (auto i=0x0; i < 0x8; i++)
    {
        EXPECT_EQ(i,mem->ReadData32(0x0));
    }
}
//af00 ADD_T1_SP_IMM
TEST_F(ExecuteTest, Add_t1_sp_imm_zerovalue_to_r7)
{
    std::shared_ptr<memory::Mmu> mem = std::make_shared<memory::MEM>();
    reg->writeRegister(MSP,0x20);
    reg->writeRegister(7,0x00);
    SUT.executeCommand("ADD_T1_SP_IMM", 0xaf00,reg,mem);
    EXPECT_EQ(0x20,reg->readRegister(7));
}

} //namespace tests
} //namespace assembler
} //namespace cpu
} //namespace devices
