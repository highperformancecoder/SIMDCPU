#include <gtest/gtest.h>

#include "../SIMDCPU.h"

#include <iostream>

using namespace SIMDCPU;
using namespace std;

struct TestCPU: public CPU, public testing::Test {};

TEST_F(TestCPU, Add) {
  // program for R0=R0+R1
  soup[0]=Instruction(Copy1, R2, PC, PC).asWord();
  soup[1]=Instruction(And, test, R0, R1, none, false, true, left).asWord();
  soup[2]=Instruction(Xor, R0, R0, R1).asWord();
  soup[3]=Instruction(Copy1, R1, test, test, jmpz).asWord();
  soup[4]=Instruction(Copy1, PC, R2, R2).asWord();
  registers[PC]=0;
  auto x=0b10101010, y=0b11001100;
  registers[R0]=x;
  registers[R1]=y;
  for (int i=0; i<10; ++i)
    {
      if (registers[PC]>4) break;
      cout<<"PC="<<registers[PC]<<" R0="<<registers[R0]<<" R1="<<registers[R1]<<" test="<<registers[test]<<endl;
      execute();
    }
  EXPECT_EQ(registers[R0], x+y);
}

