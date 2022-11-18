#include "../../devices/cpu/assembler/Assembler.hpp"
#include <gtest/gtest.h>

namespace devices {
namespace cpu {
namespace assembler {

class AssemblerTest : public testing::Test
{
public:
    void SetUp() override{}
    void TearDown() override{}
};

TEST_F(AssemblerTest, firstTest)
{
    Assembler sut;
    std::map<uint32_t,std::string> command;
    command[0x41400000] = "ADC_T1";
    command[0x75A00000] = "ADC_T2";
    command[0x1C000000] = "ADD_T1_IMM";
    command[0x30000000] = "ADD_T2_IMM";
    command[0x18000000] = "ADD_T1_REG";
    command[0x44000000] = "ADD_T2_REG";
    command[0xA8000000] = "ADD_T1_SP_IMM";
    command[0xB0000000] = "ADD_T2_SP_IMM";
    command[0x44680000] = "ADD_T1_SP_REG";
    command[0x44850000] = "ADD_T2_SP_REG";
    command[0xA0000000] = "ADR";
    command[0xF0000000] = "AND_IMM"; //todo TST need add for this
    command[0x40000000] = "AND_REG";
    command[0x10000000] = "ASR_IMM";
    command[0x41000000] = "ASR_REG";
    for (auto& i : command) {
        EXPECT_EQ(sut.Execute(i.first), i.second);
    }
}

} //namespace assembler
} //namespace cpu
} //namespace devices
