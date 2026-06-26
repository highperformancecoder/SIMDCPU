#include "SIMDCPU.h"
#include "SIMDCPU.cd"
#include "ecolab_epilogue.h"
using namespace std;
using namespace classdesc;

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
    switch (instr.postOp)
      {
      case none: break;
      case load:
        registers[data]=soup[registers[loadAddr]&soupMask];
        break;
      case store:
        soup[registers[storeAddr]&soupMask]=registers[data];
        break;
      case jmpz:
        if (registers[test]==0 && instr.ppop!=full) // special case ppop=full, turns this into a nop
          registers[PC]++;
        break;
      }
    switch (instr.ppop)
      {
      case nopp: break;
      case incr: registers[instr.dest]++; break;
      case decr: registers[instr.dest]--; break;
      case shiftL: registers[instr.dest]<<=1; break;
      case shiftR: registers[instr.dest]>>=1; break;
      }
  }

  void CPU::trace()
  {
    Instruction instr(soup[(registers[PC])&soupMask]);
    cout << "PC="<<registers[PC]<<": "<<instr<<" ";
    auto x=registers[instr.src1], y=registers[instr.src2];
    execute();
    cout <<registers[instr.dest]<<"←"<<x<<","<<y<<endl;
  }
  
  void Instruction::print(std::ostream& os) const
  {
    os << enumKey<CPU::Opcodes>(opcode) << " " <<
      enumKey<CPU::Registers>(dest)<<","<<
      enumKey<CPU::Registers>(src1)<<","<<
      enumKey<CPU::Registers>(src2);
    if (postOp!=CPU::none || ppop!=CPU::nopp)
      os << "; ";
    if (postOp!=CPU::none)
      os << enumKey<CPU::PostOp>(postOp);
    if (ppop!=CPU::nopp)
      os << " " << enumKey<CPU::PostPostOp>(ppop);
  }
}
