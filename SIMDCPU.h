#ifndef SIMDCPU_H
#define SIMDCPU_H
#include "soup.h"

namespace SIMDCPU
{
  class CPU
  {
  public:
    constexpr static int addrBits = 5;
    constexpr static int numRegisters = 1<<addrBits;
    Word registers[numRegisters];
    void execute();

    enum ShiftDir {left, right};
    enum PostOp {none, load, store, jmpz};
    enum Registers {PC, PCprime, data, test, loadAddr, storeAddr, R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10};
    enum Opcodes {
      Zero=0x0,
      Not1Nor2=0x1,
      Not1And2=0x2,
      Not1=0x3,
      Not2And1=0x4,
      Not2=0x5,
      Xor=0x6,
      Not1OrNot2=0x7,
      And=0x8,
      Eq=0x9,
      Copy2=0xA,
      Not1Or2=0xB,
      Copy1=0xC,
      Not2Or1=0xD,
      Or=0xE,
      One=0xF,
    };
  };

  struct Instruction
  {
    unsigned opcode: 4;
    unsigned dest: CPU::addrBits, src1: CPU::addrBits, src2: CPU::addrBits;
    unsigned postOp: 2, incr: 1, shift: 1, shiftDir: 1, reserved: 3;
    Instruction() = default;
    explicit Instruction(Word word) { *this = reinterpret_cast<const Instruction&>(word); }
    Instruction(CPU::Opcodes opcode, CPU::Registers dest, CPU::Registers src1, CPU::Registers src2, CPU::PostOp postOp = CPU::none, bool incr = false, bool shift = false, CPU::ShiftDir shiftDir = CPU::left)
      : opcode(opcode), dest(dest), src1(src1), src2(src2), postOp(postOp), incr(incr), shift(shift), shiftDir(shiftDir) {}
    Word asWord() const {return reinterpret_cast<const Word&>(*this);}
  };

  static_assert(sizeof(Instruction) == 4, "Instruction must be 4 bytes");

}
#endif
