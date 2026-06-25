#include "SIMDCPU.h"

namespace SIMDCPU
{
  void CPU::execute()
  {
    Instruction instr(soup[(registers[PC]++)&soupMask]);
    auto x=registers[instr.src1], y=registers[instr.src2];
    unsigned op=instr.opcode;
    const Word one=~Word(0);
    registers[instr.dest] =
      x&y&(one*((op&8)==8)) |
      ~x&y&(one*((op&2)==2)) |
      x&~y&(one*((op&4)==4)) |
      ~(x|y)&(one*((op&1)==1));
    if (instr.shift)
      registers[instr.dest] = instr.shiftDir? registers[instr.dest] >> 1: registers[instr.dest] << 1;
    switch (instr.postOp)
      {
      case none: break;
      case load: registers[data]=soup[registers[loadAddr]&soupMask];
        if (instr.incr) registers[loadAddr]++;
        break;
      case store: soup[registers[storeAddr]&soupMask]=registers[data];
        if (instr.incr) registers[storeAddr]++;
        break;
      case jmpz: if (registers[test]==0)
          registers[PC]++;
        break;
      }
    
  }
}
