


#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// constantes

#include "../constants/constants.h"

// librerias propias


using namespace std;

#ifndef CACHE_LINE_H

#define CACHE_LINE_H

/**
 * Clase que representa una linea de la cache
*/
class CacheLine {
  private:
  /**
   * Tag de la linea
  */
    long tag;
    /**
     * Indica si la linea es valida
    */
    bool valid = false;

    /**
     * Valor del bloque
    */
    long block;
    /**
     * Tiempo de acceso
     * -1 si no ha sido accedido
    */
    size_t accessTime;
  public:

    CacheLine(){
      this->valid = false;
    }

    CacheLine(bool valid) {
      this->valid = valid;
      this->accessTime = -1;
    }

    CacheLine(long tag, bool valid, long offset, long set) {
      this->tag = tag;
      this->valid = valid;
      this->block = block;
    }

    // getters y setters

    long getTag() {
      return this->tag;
    }

    bool getValid() {
      return this->valid;
    }

    long getBlock() {
      return this->block;
    }

    long getAccessTime() {
      return this->accessTime;
    }


    void setTag(long tag) {
      this->tag = tag;
    }

    void setValid(bool valid) {
      this->valid = valid;
    }

    void setBlock(long block) {
      this->block = block;
    }

    void setAccessTime(size_t accessTime) {
      this->accessTime = accessTime;
    }

    ~CacheLine() {

    }
};

#endif