#include <gtest/gtest.h>

#include "../SIMDCPU.h"
#include "ecolab_epilogue.h"
#include <iostream>

using namespace SIMDCPU;
using namespace std;

struct TestCPU: public CPU, public testing::Test {};

TEST_F(TestCPU, Add) {
  // program for R0=R0+R1
  soup[0]=Instruction(Copy1, R2, PC, PC).asWord();
  soup[1]=Instruction(And, test, R0, R1, none, CPU::shiftL).asWord();
  soup[2]=Instruction(Xor, R0, R0, R1).asWord();
  soup[3]=Instruction(Copy1, R1, test, test, jmpz).asWord();
  soup[4]=Instruction(Copy1, PC, R2, R2).asWord();
  registers[PC]=0;
  auto x=0b10101010, y=0b11001100;
  registers[R0]=x;
  registers[R1]=y;
  for (int i=0; i<10 && registers[PC]<5; ++i)
      execute();
  EXPECT_EQ(registers[R0], x+y);
}

