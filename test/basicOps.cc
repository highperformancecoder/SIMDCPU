#include <gtest/gtest.h>

#include "../SIMDCPU.h"

using namespace SIMDCPU;

struct TestCPU: public CPU, public testing::Test {};

TEST_F(TestCPU, TestZero) {
  soup[0]=Instruction(Zero, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], 0);
}

TEST_F(TestCPU, TestNot1Nor2) {
  soup[0]=Instruction(Not1Nor2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R1] & ~registers[R2]);
}

TEST_F(TestCPU, TestNot2And1) {
  soup[0]=Instruction(Not2And1, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1] & ~registers[R2]);
}

TEST_F(TestCPU, TestNot2) {
  soup[0]=Instruction(Not2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R2]);
}

TEST_F(TestCPU, TestNot1And2) {
  soup[0]=Instruction(Not1And2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R1] & registers[R2]);
}

TEST_F(TestCPU, TestXor) {
  soup[0]=Instruction(Xor, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1] ^ registers[R2]);
}

TEST_F(TestCPU, TestNot1) {
  soup[0]=Instruction(Not1, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R1]);
}

TEST_F(TestCPU, TestNot1OrNot2) {
  soup[0]=Instruction(Not1OrNot2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R1] | ~registers[R2]);
}

TEST_F(TestCPU, TestAnd) {
  soup[0]=Instruction(And, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1] & registers[R2]);
}

TEST_F(TestCPU, TestEq) {
  soup[0]=Instruction(Eq, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~(registers[R1] ^ registers[R2]));
}

TEST_F(TestCPU, TestCopy1) {
  soup[0]=Instruction(Copy1, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1]);
}

TEST_F(TestCPU, TestNot2Or1) {
  soup[0]=Instruction(Not2Or1, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1]|~registers[R2]);
}

TEST_F(TestCPU, TestCopy2) {
  soup[0]=Instruction(Copy2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R2]);
}

TEST_F(TestCPU, TestNot1Or2) {
  soup[0]=Instruction(Not1Or2, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~registers[R1]|registers[R2]);
}


TEST_F(TestCPU, TestOr) {
  soup[0]=Instruction(Or, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], registers[R1]|registers[R2]);
}

TEST_F(TestCPU, TestOne) {
  soup[0]=Instruction(One, R0, R1, R2).asWord();
  registers[PC]=0;
  registers[R1]=0b10101010;
  registers[R2]=0b11001100;
  execute();
  EXPECT_EQ(registers[R0], ~Word(0));
}



