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
//todo armv7-m tests
//  command[0xF0000000] = "AND_IMM"; //todo TST need add for this
// command[0x75A00000] = "ADC_T2";

TEST_F(AssemblerTest, assemblerThumbInstructioSet)
{
    Assembler sut;
    std::map<uint32_t,std::string> command;
    command[0x4140] = "ADC_REG";
    command[0x1C00] = "ADD_T1_IMM";
    command[0x3000] = "ADD_T2_IMM";
    command[0x1800] = "ADD_T1_REG";
    command[0x4400] = "ADD_T2_REG";
    command[0xA800] = "ADD_T1_SP_IMM";
    command[0xAF00] = "ADD_T1_SP_IMM";
    command[0xB000] = "ADD_T2_SP_IMM";
    command[0x4468] = "ADD_T1_SP_REG";
    command[0x4485] = "ADD_T2_SP_REG";
    command[0xA000] = "ADR";
    command[0x4000] = "AND_REG";
    command[0x1000] = "ASR_IMM";
    command[0x4100] = "ASR_REG";
    command[0xD000] = "B_T1"; //todo SVC
    command[0xE000] = "B_T2";
    command[0x4380] = "BIC_REG";
    command[0xBE00] = "BKPT";
    command[0x4700] = "BX";
    command[0x42C0] = "CMN";
    command[0x2800] = "CMP_IMM";
    command[0x4280] = "CMP_T1_REG";
    command[0x4500] = "CMP_T2_REG";
    command[0x4040] = "EOR";
    command[0xC800] = "LDM";
    command[0x6800] = "LDR_T1_IMM";
    command[0x9800] = "LDR_T2_IMM";
    command[0x4800] = "LDR_T1_LIT";
    command[0x5800] = "LDR_T1_REG";
    for (auto& i : command) {
        EXPECT_EQ(sut.ExecuteThumb(i.first), i.second);
    }
}

} //namespace assembler
} //namespace cpu
} //namespace devices
