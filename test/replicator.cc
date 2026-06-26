#include <gtest/gtest.h>

#include "../SIMDCPU.h"

#include <iostream>

using namespace SIMDCPU;
using namespace std;

struct TestCPU: public CPU, public testing::Test {};

TEST_F(TestCPU, Replicator) {
  soup[0]=Instruction(Copy1, R0, PC, PC, none, decr).asWord(); // load start
  soup[1]=Instruction(Copy1, loadAddr, PC, PC).asWord();
  soup[2]=Instruction(Copy1, R0, R0, R0).asWord(); // template search pattern
  soup[3]=Instruction(Copy1, loadAddr, loadAddr, loadAddr, load, incr).asWord(); // load search pattern to data
  soup[4]=Instruction(Copy1, R2, data, data).asWord(); // end of search pattern
  soup[5]=Instruction(Copy1, R1, PC, PC).asWord(); // find loop
  soup[6]=Instruction(Copy1, loadAddr, loadAddr, loadAddr, load, incr).asWord(); // load search pattern to data  
  soup[7]=Instruction(Eq, test, R2, data, jmpz).asWord(); // if not equal, goto find loop
  soup[8]=Instruction(Copy1, PC, R1,R1).asWord(); // goto find loop
  soup[9]=Instruction(Copy1, R2, loadAddr, loadAddr).asWord(); // R2 = end
  soup[10]=Instruction(Copy1, loadAddr, R0, R0).asWord();
  soup[11]=Instruction(Copy1, R1, PC, PC).asWord(); // copy loop
  soup[12]=Instruction(Copy1, loadAddr, loadAddr, loadAddr, load, incr).asWord();
  soup[13]=Instruction(Copy1, storeAddr, storeAddr, storeAddr, store, incr).asWord();
  soup[14]=Instruction(Xor, test, PC, R2, jmpz).asWord();
  soup[15]=Instruction(Copy1, PC, R1, R1).asWord(); // goto copy loop
  soup[16]=Instruction(Not1, cmpl(R0), cmpl(R0), cmpl(R0), jmpz, full).asWord(); //complementary template at end

  registers[PC]=0;
  registers[storeAddr]=20;
  for (int i=0; i<500 && registers[PC]<17; ++i)
    execute();
  for (int i=0; i<17; ++i)
    {
      //cout<<i<<endl;
      EXPECT_EQ(soup[i], soup[i+20]);
    }
}
