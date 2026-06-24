#include "SIMDCPU.h"
#include "soup.h"
#include "soup.cd"
#include "classdesc.h"

using namespace std;
using namespace classdesc;

namespace SIMDCPU
{
  class Assembler
  {
    Word current;
    public:
    Assembler(Word start=0) : current(start) {}
    Instruction parseLine(const std::string& line) {
      istringstream iss(line);
      string opCode, dest, src1, src2;
      iss >> opcode >> dest >> src1 >> src2;
      Instruction r(enumKey<CPU::Opcode>(opcode),
                    enumKey<CPU::Registers>(dest),
                    enumKey<CPU::Registers>(src1),
                    enumKey<CPU::Registers>(src2));

      string next;
      while (iss) {
        iss >> next; // Read next token
        if (next=="#") break; // Comment, ignore rest of the line
        if (enum_keys<CPU::PostOp>().has(next)) 
          r.postOp = enumKey<CPU::PostOp>(next);
        if (next=="shift") r.shift = 1;
        if (enum_keys<CPU::ShiftDir>().has(next)) 
          r.shiftDir = enumKey<CPU::ShiftDir>(next);
        if (next=="incr") r.incr = 1;
      }
      return r;
    }     
  };
}
