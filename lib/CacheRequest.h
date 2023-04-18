

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// constantes

#include "../constants/constants.h"

// librerias propias

#include "../base/cache.h"

using namespace std;

#ifndef CACHE_REQUEST_H

#define CACHE_REQUEST_H

// a template to store the size in bits of the address, tag, set, and offset

class CacheRequest
{

private:
  long binaryAddress;
  long tag;
  long set;
  long offset;

  // number of bits

  size_t bitsInTag;
  size_t bitsInSet;
  size_t bitsInOffset;

public:
  /**
   * @param address Posicion del conjunto en memoria
   * @param offsetBits Numero de bits para el desplazamiento
   * @param setBits Numero de bits para el conjunto
   */
  CacheRequest(long binaryAddress, long offsetBits, long setBits)
  {

    this->binaryAddress = binaryAddress;

    this->offset = binaryAddress & ((1 << offsetBits) - 1);

    this->set = (binaryAddress >> offsetBits) & ((1 << setBits) - 1);

    this->tag = binaryAddress >> (offsetBits + setBits);

    this->bitsInOffset = offsetBits;
    this->bitsInSet = setBits;
    this->bitsInTag = ADDRESS_SIZE - offsetBits - setBits;

    this->print();
  }

  long getTag()
  {
    return this->tag;
  }

  long getSet()
  {
    return this->set;
  }

  long getOffset()
  {
    return this->offset;
  }

  long getBinaryAddress()
  {
    return this->binaryAddress;
  }

  void print()
  {
  }

  void printRequest()
  {
    std::cout << "Address: ";
    BaseNParser::printLongInBinary(this->binaryAddress, ADDRESS_SIZE);
    std::cout << std::endl;

    std::cout << "Tag: ";
    BaseNParser::printLongInBinary(this->tag, this->bitsInTag);
    std::cout << std::endl;

    std::cout << "Set: ";
    BaseNParser::printLongInBinary(this->set, this->bitsInSet);
    std::cout << std::endl;

    std::cout << "Offset: ";
    BaseNParser::printLongInBinary(this->offset, this->bitsInOffset);
    std::cout << std::endl;

  }

  void printBits(long number, int numBits)
  {
    for (int bitIndex = numBits - 1; bitIndex >= 0; bitIndex--)
    {
      std::cout << ((number >> bitIndex) & 1);
    }
  }

  ~CacheRequest()
  {
  }
};

#endif