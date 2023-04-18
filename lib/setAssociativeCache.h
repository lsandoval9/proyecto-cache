

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// librerias propias

#include "../base/cache.h"
#include "../lib/CacheLine.h"
#include "../lib/CacheRequest.h"

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef SETASSOCIATIVECACHE_H

#define SETASSOCIATIVECACHE_H

class SetAssociativeCache : public BaseCache
{

private:
  long n_ways;

  vector<CacheLine> cache;

  long sets_in_cache;

public:
  SetAssociativeCache(long s_block, long s_cache, long n_ways) : BaseCache(s_block, s_cache)
  {

    this->n_ways = n_ways;

    this->bitsInOffset = log2(this->s_block * WORD_SIZE);

    this->sets_in_cache = this->blocks_in_cache / this->n_ways;

    this->bitsInTag = ADDRESS_SIZE - bitsInSet - bitsInOffset;

    this->sets_in_cache = this->blocks_in_cache / this->n_ways;

    this->initializeCache();
  }

  /**
   * Guarda un bloque en la caché
   * @param binaryAddress dirección en binario de 32 bits
   */
  void saveBlockInCache(long binaryAddress)
  {

    CacheRequest *request = new CacheRequest(binaryAddress, this->bitsInOffset, this->bitsInSet);

    long tag, set, offset, address;

    tag = request->getTag();

    set = request->getSet();

    offset = request->getOffset();

    address = request->getBinaryAddress();

    bool inserted = false;

    // insert bits in cache using LRU

    size_t lessRecent = 0;

    long currentBlock = n_ways * set;

    for (int i = currentBlock; i < this->n_ways + currentBlock; ++i)
    {

      bool valid = this->cache[i].getValid();

      if (!valid)
      {

        this->cache[i].setTag(tag);

        this->cache[i].setBlock(address);

        this->cache[i].setValid(false);

        this->cache[i].setAccessTime(this->access_time);

        this->access_time++;

        inserted = true;

        break;
      }

      if (this->cache[i].getAccessTime() < this->cache[lessRecent].getAccessTime())
      {

        lessRecent = i;
      }
    }

    if (!inserted)
    {

      this->cache[lessRecent].setTag(tag);

      this->cache[lessRecent].setBlock(address);

      this->cache[lessRecent].setValid(true);

      this->cache[lessRecent].setAccessTime(this->access_time);

      this->access_time++;
    }
  }

  void initializeCache()
  {

    cout << "Bloques en cache: " << this->blocks_in_cache << endl;

    cout << "Conjuntos en cache: " << this->sets_in_cache << endl;

    cout << "Bits en offset: " << this->bitsInSet << endl;

    this->cache = vector<CacheLine>(this->blocks_in_cache);

    for (int i = 0; i < this->blocks_in_cache; i++)
    {

      this->cache[i] = CacheLine(false);
    }

  }

  void printFeatures()
  {
  }

  ~SetAssociativeCache()
  {
  }
};

#endif