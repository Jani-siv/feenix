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

TEST_F(AssemblerTest,testArea)
{
    Assembler sut;
    EXPECT_EQ(sut.ExecuteThumb(0x0050),"LSL_T1_IMM");
}

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
    command[0xD000] = "B_T1";
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
    command[0x7800] = "LDRB_T1_IMM";
    command[0x5C00] = "LDRB_T1_REG";
    command[0x8800] = "LDRH_T1_IMM";
    command[0x5A00] = "LDRH_T1_REG";
    command[0x5600] = "LDRSB_T1_REG";
    command[0x5E00] = "LDRSH_T1_REG";
    command[0x0050] = "LSL_T1_IMM";
    command[0x4080] = "LSL_T1_REG";
    command[0x0800] = "LSR_T1_IMM";
    command[0x40C0] = "LSR_T1_REG";
    command[0x2000] = "MOV_T1_IMM";
    command[0x4600] = "MOV_T1_REG";
    command[0x0000] = "MOV_T2_REG";
    command[0x4340] = "MUL_T1";
    command[0x43C0] = "MVN_T1_REG";
    command[0x4300] = "ORR_T1_REG";
    command[0xBC00] = "POP_T1";
    command[0xB400] = "PUSH_T1";
    command[0x41C0] = "ROR_T1_REG";
    command[0x4240] = "RSB_T1_IMM";
    command[0x4180] = "SBC_T1_REG";
    command[0xC000] = "STM_T1";
    command[0x6000] = "STR_T1_IMM";
    command[0x9000] = "STR_T2_IMM";
    command[0x5000] = "STR_T1_REG";
    command[0x7000] = "STRB_T1_IMM";
    command[0x5400] = "STRB_T1_REG";
    command[0x8000] = "STRH_T1_IMM";
    command[0x5200] = "STRH_T1_REG";
    command[0x1E00] = "SUB_T1_IMM";
    command[0x3800] = "SUB_T2_IMM";
    command[0x1A00] = "SUB_T1_REG";
    command[0xB080] = "SUB_T1_SP_IMM";
    command[0xDF00] = "SVC_T1";
    command[0x4200] = "TST_T1_REG";

    for (auto& i : command) {
        EXPECT_EQ(sut.ExecuteThumb(i.first), i.second);
    }
}

} //namespace assembler
} //namespace cpu
} //namespace devices
