

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// constantes

#include "../constants/constants.hpp"

// librerias propias

#include "../base/cache.hpp"
#include "../helpers/baseNParser.hpp"

using namespace std;

#ifndef CACHE_REQUEST_H

#define CACHE_REQUEST_H

/**
 * Clase que representa una solicitud de la cache hecha por el CPU
 */
class CacheRequest
{

private:
  /**
   * Direccion en binario de 32 bits
   */
  long binaryAddress;
  /**
   * Tag de la request
   */
  long tag;
  /**
   * Conjunto de la request
   */
  long set;
  /**
   * Desplazamiento de la request
   */
  long offset;

  // number of bits

  /**
   * Numero de bits para el tag
   */
  size_t bitsInTag;
  /**
   * Numero de bits para el conjunto
   */
  size_t bitsInSet;
  /**
   * Numero de bits para el desplazamiento
   */
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

  /**
   * Imprime los valores de la request en binario
   */
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

  ~CacheRequest()
  {
  }
};

#endif