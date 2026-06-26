#include "soup.h"
#include "assembler.h"
#include "pythonBuffer.h"
#include "ecolab_epilogue.h"

namespace SIMDCPU
{
  Word instruction(CPU::Opcodes op, int dest, int src1, int src2, CPU::PostOp postOp, CPU::PostPostOp ppop)
  {
    return Instruction(op,CPU::Registers(dest),CPU::Registers(src1),CPU::Registers(src2),postOp,ppop).asWord();
  }
  Word reg(CPU::Registers reg)
  {
    return Word(reg);
  }

  CLASSDESC_ADD_FUNCTION(instruction);
  CLASSDESC_ADD_FUNCTION(reg);
  
  //CLASSDESC_ADD_GLOBAL(soup); // crashes when access directly from python. Use Assembler::soup instead
  CLASSDESC_DECLARE_TYPE(Assembler);
  CLASSDESC_DECLARE_TYPE(CPU);
 
  using Opcodes=CPU::Opcodes;
  using Registers=CPU::Registers;
  using PostOp=CPU::PostOp;
  using PostPostOp=CPU::PostPostOp;
  CLASSDESC_ADD_ENUM(Opcodes);
  CLASSDESC_ADD_ENUM(Registers);
  CLASSDESC_ADD_ENUM(PostOp);
  CLASSDESC_ADD_ENUM(PostPostOp);

  CLASSDESC_PYTHON_MODULE(SIMDTierra);
}
