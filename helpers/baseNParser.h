

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef BASENPARSER_H

#define BASENPARSER_H

class BaseNParser
{

private:
  BaseNParser() {}

public:
  ~BaseNParser()
  {
  }

  static void printHex(long dec)
  {
    cout << "0x" << setfill('0') << setw(8) << hex << dec;
  }

  static void printBin(long bin)
  {
    cout << "0b" << setfill('0') << setw(8) << bin << dec;
  }
};

#endif