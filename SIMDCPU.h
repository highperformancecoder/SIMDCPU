#ifndef SIMDCPU_H
#define SIMDCPU_H
#include "soup.h"
#include <array>
#include <ostream>

namespace SIMDCPU
{
  class CPU
  {
  public:
    std::vector<Word>& soup=SIMDCPU::soup;
    constexpr static int addrBits = 5;
    constexpr static int numRegisters = 1<<addrBits;
    std::array<Word,CPU::numRegisters> registers;
    void execute();
    void trace();
    
    enum PostPostOp {nopp=0, incr, decr, shiftL, shiftR, full=7};
    enum PostOp {none=0, load, store, jmpz=3};
    enum Registers {PC, data, test, loadAddr, storeAddr, R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11};
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
    unsigned postOp: 2, ppop: 3, reserved: 8;
    Instruction() = default;
    explicit Instruction(Word word) { *this = reinterpret_cast<const Instruction&>(word); }
    Instruction(CPU::Opcodes opcode, CPU::Registers dest, CPU::Registers src1, CPU::Registers src2, CPU::PostOp postOp = CPU::none, CPU::PostPostOp ppop = CPU::nopp)
      : opcode(opcode), dest(dest), src1(src1), src2(src2), postOp(postOp), ppop(ppop), reserved(ppop == CPU::full ? 0xFF : 0)
    {}
    Word asWord() const {return reinterpret_cast<const Word&>(*this);}
    void print(std::ostream& os) const;
  };

  static_assert(sizeof(Instruction) == 4, "Instruction must be 4 bytes");

  inline CPU::Opcodes cmpl(CPU::Opcodes op) {return CPU::Opcodes(~op&0xF);}
  inline CPU::Registers cmpl(CPU::Registers r)
  {return CPU::Registers(~r&(CPU::numRegisters-1));}


  inline std::ostream& operator<<(std::ostream& o, const Instruction& i) {i.print(o); return o;}
}

// clobber descriptor generation, which doesn't handle bit fields.
#define CLASSDESC_pack___SIMDCPU__Instruction
#define CLASSDESC_unpack___SIMDCPU__Instruction
#define CLASSDESC_RESTProcess___SIMDCPU__Instruction
#define CLASSDESC_json_pack___SIMDCPU__Instruction
#define CLASSDESC_json_unpack___SIMDCPU__Instruction

#include "SIMDCPU.cd"

namespace classdesc_access
{
  template <> struct access_pack<SIMDCPU::Instruction>
  {
    template <class T>
    void operator()(classdesc::pack_t& j, const std::string& d, const T& x) 
    {::pack(j,d,reinterpret_cast<const SIMDCPU::Word&>(x));}
  };
  template <> struct access_unpack<SIMDCPU::Instruction>
  {
    template <class T>
    void operator()(classdesc::unpack_t& j, const std::string& d, T& x)
    {::unpack(j,d,reinterpret_cast<typename classdesc::transfer_const<T,SIMDCPU::Word>::type&>(x));}
  };
  
  template <> struct access_RESTProcess<SIMDCPU::Instruction>:
    public classdesc::NullDescriptor<classdesc::RESTProcess_t>{};

  template <> struct access_json_pack<SIMDCPU::Instruction>
  {
    template <class T>
    void operator()(classdesc::json_pack_t& j, const std::string& d, const T& x)
    {::json_pack(j,d,reinterpret_cast<const SIMDCPU::Word&>(x));}
  };
  template <> struct access_json_unpack<SIMDCPU::Instruction>
  {
    template <class T>
    void operator()(classdesc::json_pack_t& j, const std::string& d, T& x)
    {::json_unpack(j,d,reinterpret_cast<typename classdesc::transfer_const<T,SIMDCPU::Word>::type&>(x));}
  };

}

#endif
