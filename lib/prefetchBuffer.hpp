
#include <vector>

// Librearias propias

#include "./CacheLine.hpp"
#include "../constants/constants.hpp"
#include "../lib/CacheRequest.hpp"

using namespace std;

#ifndef PREFETCHBUFFER_H

#define PREFETCHBUFFER_H

#define PREV 0

#define NEXT 1

class PrefetchBuffer
{

private:
  vector<CacheLine> buffer;

  size_t access_time = 0;

  size_t miss_counter = 0;

public:
  PrefetchBuffer()
  {
    this->buffer = vector<CacheLine>(2);
  }

  /**
   * Obtiene el tamaño del buffer
   * @return tamaño del buffer
   */
  long getBufferSize()
  {
    return this->buffer.size();
  }

  /**
   * Obtiene el valor de la linea en la posicion indicada
   * @param index posicion de la linea
   * @return valor de la linea
   */
  CacheLine getLine(long index)
  {
    return this->buffer[index];
  }

  bool checkBuffer(long tag)
  { 
    
    for (long i = 0; i < this->buffer.size(); i++)
    {
      if (this->buffer[i].getTag() == tag)
      {
        this->incrementAccessTime();
        return true;
      }
    }
    
    return false;
  }

  void clearBuffer()
  {
    this->buffer = vector<CacheLine>(2);
  }

  void storeAdjacentBlocks(CacheRequest *request)
  {

    long next, prev;

    long address = request->getBinaryAddress();

    long bitsInBlock = WORD_SIZE * WORDS_PER_BLOCK * 8;

    CacheRequest *aux;

    if (address + bitsInBlock <= MAX_ADDRESS)
    {

      next = address + bitsInBlock;

      aux = new CacheRequest(next, request->getBitsInOffset(), request->getBitsInSet());

      this->buffer[NEXT].setTag(aux->getTag());
      this->buffer[NEXT].setValid(true);
      this->buffer[NEXT].setAccessTime(1);
      this->buffer[NEXT].setAccessCounter(1);
      this->buffer[NEXT].setBlock(aux->getBinaryAddress());

      delete aux;
    }
    else
    {
      this->buffer[NEXT].setValid(false);
    }

    if (address - bitsInBlock >= 0)
    {

      prev = address - bitsInBlock;

      aux = new CacheRequest(prev, request->getBitsInOffset(), request->getBitsInSet());

      this->buffer[PREV].setTag(aux->getTag());
      this->buffer[PREV].setValid(true);
      this->buffer[PREV].setAccessTime(1);
      this->buffer[PREV].setAccessCounter(1);
      this->buffer[PREV].setBlock(aux->getBinaryAddress());

      delete aux;

    }
    else
    {
      this->buffer[PREV].setValid(false);
    }
  }

  size_t getAccessTime()
  {
    return this->access_time;
  }

  size_t getMissCounter()
  {
    return this->miss_counter;
  }

  void incrementAccessTime()
  {
    this->access_time += 1;
  }

  void incrementMissCounter()
  {
    this->miss_counter += 1;
  }
};

#endif // PREFETCHBUFFER_H