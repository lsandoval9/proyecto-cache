
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

  bool checkBuffer(long tag) {
    for (long i = 0; i < this->buffer.size(); i++) {
      if (this->buffer[i].getTag() == tag && this->buffer[i].getValid()) {
        return true;
      }
    }

    return false;
  }


  void clearBuffer() {
    this->buffer = vector<CacheLine>(2);
  }
};

#endif // PREFETCHBUFFER_H