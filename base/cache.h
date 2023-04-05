#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef CACHE_H

#define CACHE_H

class BaseCache {

  private:

    long s_block;

    long s_cache;


    public:

      BaseCache(long s_block, long s_cache) {
        this->s_block = s_block;
        this->s_cache = s_cache;
      }

      virtual void getFeatures() = 0;

      long getSBlock() {
        return this->s_block;
      }

      long getSCache() {
        return this->s_cache;
      }

      void setSBlock(long s_block) {
        this->s_block = s_block;
      }

      void setSCache(long s_cache) {
        this->s_cache = s_cache;
      }

      ~BaseCache() {

      }

};

#endif