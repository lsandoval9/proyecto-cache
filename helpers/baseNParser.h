
#include "../constants/constants.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <map>
#include <bitset>
#include <fstream>

using namespace std;

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

  static long parseHexStringToNumber(string hexString)
  {
    
    long hexNumber = stol(hexString, nullptr, 16);

    cout << "Hex number: " << hexNumber << endl;

    return hexNumber;
    
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