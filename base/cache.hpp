#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "../constants/constants.hpp"
#include "../lib/prefetchBuffer.hpp"

using namespace std;

#ifndef CACHE_H

#define CACHE_H

class BaseCache
{

protected:
  /**
   * Tamaño del bloque en palabras de 32 bits (4 bytes)
   */
  long s_block;

  /**
   * Tamaño de la caché en kilobytes
   */
  long s_cache;

  /**
   * Cantidad de bloques que caben en la caché
   */
  long blocks_in_cache;

  /**
   * Cantidad de conjuntos que caben en la caché
   */
  long sets_in_cache;

  /**
   * Contador que simula el tiempo de acceso a la caché
   */
  size_t access_time;

  /**
   * Contador de accesos fallidos a la caché
   */
  size_t miss_counter;

  /**
   * Tamaño del desplazamiento en bits (desplazamiento de palabra + desplazamiento de byte)
   */
  long bitsInOffset;

  /**
   * numero de bits para identificar el conjunto en el que se encuentra el bloque
   */
  long bitsInSet;

  /**
   * Tamaño de la etiqueta en bits
   */
  long bitsInTag;

  /**
   * Política de reemplazo
   * 0: LRU (default)
   * 1: FIFO
   * 2: random
   *
   */
  short replacePolicy;

  /**
   * Buffer de prefetching
   */
  PrefetchBuffer *prefetchBuffer;

public:
  BaseCache(long s_block, long s_cache, short replacePolicy = 0)
  {
    this->s_block = s_block;
    this->s_cache = s_cache;
    this->access_time = 0;
    this->miss_counter = 0;
    this->replacePolicy = replacePolicy;

    this->calculateBlocksInCache();

    this->prefetchBuffer = new PrefetchBuffer();
  }

  // metodos virtuales puros

  virtual void saveBlockInCache(long blockAddress) = 0;

  // metodos comunes

  /**
   * @brief Calcula la cantidad de bloques que caben en la caché
   */
  void calculateBlocksInCache()
  {
    long cacheInBytes = this->s_cache * 1024;

    this->blocks_in_cache = cacheInBytes / (this->s_block * 4);
  }

  /**
   * @brief Calcula el tamaño real de la caché en kilobytes
   * @param bitsInTag Tamaño de la etiqueta en bits
   */
  double getRealSize(long bitsInTag)
  {

    double kilobitsInCache = (double)(this->blocks_in_cache * ((this->s_block * WORD_SIZE * 8) + bitsInTag + 1)) / 1024;

    return kilobitsInCache / 8; // return the value in kilobytes
  }

  /**
   * @brief Calcula el porcentaje de accesos fallidos a la caché
   */
  double getMissRate()
  {

    if (this->access_time == 0 && this->prefetchBuffer->getAccessTime() == 0)
    {
      return 0;
    }

    long total_miss = this->miss_counter + this->prefetchBuffer->getMissCounter();

    return ((double)total_miss / (double)this->getTotalAccessTime()) * 100;
  }

  /**
   * @brief Calcula el porcentaje de accesos exitosos a la caché
   */
  double getHitRate()
  {

    if (this->access_time == 0)
    {
      return 0;
    }

    return 100 - this->getMissRate();
  }

  size_t getAccessTime()
  {
    return this->access_time;
  }

  size_t getTotalAccessTime()
  {
    return this->access_time + this->prefetchBuffer->getAccessTime();
  }

  long getSBlock()
  {
    return this->s_block;
  }

  long getSCache()
  {
    return this->s_cache;
  }

  size_t getMissCounter()
  {
    return this->miss_counter;
  }

  long getBitsInOffset()
  {
    return this->bitsInOffset;
  }

  long getBitsInSet()
  {
    return this->bitsInSet;
  }

  long getBitsInTag()
  {
    return this->bitsInTag;
  }

  long getSetsInCache()
  {
    return this->sets_in_cache;
  }

  long getBlocksInCache()
  {
    return this->blocks_in_cache;
  }

  void setSBlock(long s_block)
  {
    this->s_block = s_block;
  }

  void setSCache(long s_cache)
  {
    this->s_cache = s_cache;
  }

  void getReplacePolicy(short replacePolicy)
  {
    this->replacePolicy = replacePolicy;
  }

  void setReplacePolicy(short replacePolicy)
  {
    this->replacePolicy = replacePolicy;
  }

  void setAccessTime(size_t access_time)
  {
    this->access_time = access_time;
  }

  void incrementAccessTime()
  {
    this->access_time++;
  }

  void setBlocksInCache(long blocks_in_cache)
  {
    this->blocks_in_cache = blocks_in_cache;
  }

  void setSetsInCache(long sets_in_cache)
  {
    this->sets_in_cache = sets_in_cache;
  }

  void setBitsInOffset(long bitsInOffset)
  {
    this->bitsInOffset = bitsInOffset;
  }

  void setBitsInSet(long bitsInSet)
  {
    this->bitsInSet = bitsInSet;
  }

  void setBitsInTag(long bitsInTag)
  {
    this->bitsInTag = bitsInTag;
  }

  ~BaseCache()
  {
  }
};

#endif