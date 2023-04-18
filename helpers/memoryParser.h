


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef MEMORY_PARSER_H

#define MEMORY_PARSER_H

class MemoryParser
{

  private:
  MemoryParser() {}

  public:

  static long parseKbToBytes(long kb) {
    return kb * 1024;
  }

};

#endif