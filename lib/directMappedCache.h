

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

#ifndef WORD_SIZE

#define WORD_SIZE 32

#endif

#ifndef DIRECTMAPPEDCACHE_H

#define DIRECTMAPPEDCACHE_H

class DirectMappedCache {

  private:

    long s_block;

    long s_cache;


  public:

    DirectMappedCache(long s_block, long s_cache) {
      
    }

    void getFeatures() {
      
      cout << endl << "Cache de correspondencia directa:" << endl;
      cout << R"(+--------+--------+--------+--------+--------+
| Etiqueta | Bloque de cache | Desplazamiento  |
+--------+--------+--------+--------+----------+)" << endl;

    }

    ~DirectMappedCache() {

    }

};

#endif