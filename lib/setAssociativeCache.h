

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// librerias propias

#include "../base/cache.h"

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef SETASSOCIATIVECACHE_H

#define SETASSOCIATIVECACHE_H

class SetAssociativeCache : public BaseCache {

  private:

    long n_ways;

  public:

    SetAssociativeCache(long s_block, long s_cache, long n_ways) : BaseCache(s_block, s_cache) {
      this->n_ways = n_ways;
    }

    void getFeatures() {

    }

    ~SetAssociativeCache() {

    }

};

#endif