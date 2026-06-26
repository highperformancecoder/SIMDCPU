#include "SIMDCPU.h"
#include "classdesc.h"

namespace SIMDCPU
{
  struct Assembler
  {
    Word current;
    std::vector<Word>& soup=SIMDCPU::soup;
    Assembler(Word start=0) : current(start) {}
    Instruction parseLine(const std::string& line);
    void assembleLines(const std::string& line);
    void addInstruction(Word i) {soup[current++]=i;}
  };
}

#include "assembler.cd"
