#include "assembler.h"
#include "soup.h"
#include "ecolab_epilogue.h"

using namespace std;
using namespace classdesc;

namespace SIMDCPU
{
    Instruction Assembler::parseLine(const std::string& line) {
      istringstream iss(line);
      string opcode, dest, src1, src2;
      iss >> opcode >> dest >> src1 >> src2;
      Instruction r(CPU::Opcodes(enumKey<CPU::Opcodes>(opcode)),
                    CPU::Registers(enumKey<CPU::Registers>(dest)),
                    CPU::Registers(enumKey<CPU::Registers>(src1)),
                    CPU::Registers(enumKey<CPU::Registers>(src2)));

      string next;
      while (iss) {
        iss >> next; // Read next token
        if (next=="#") break; // Comment, ignore rest of the line
        if (enum_keys<CPU::PostOp>().has(next)) 
          r.postOp = enumKey<CPU::PostOp>(next);
        if (enum_keys<CPU::PostPostOp>().has(next)) 
          r.ppop = enumKey<CPU::PostPostOp>(next);
      }
      return r;
    }     

  void Assembler::assembleLines(const std::string& lines)
  {
        istringstream iss(lines);
        string line;
        while (getline(iss, line)) {
          if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
          try
            {
              soup[current++] = parseLine(line).asWord();
            }
          catch(...) {} // absorb any errors in parsing, e.g. unknown opcode, register, etc.
        }
  }

}
