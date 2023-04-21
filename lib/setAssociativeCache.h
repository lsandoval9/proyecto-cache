

#include <iostream>
#include <vector>
#include <cmath>

// librerias propias

#include "../base/cache.h"
#include "../lib/CacheLine.h"
#include "../lib/CacheRequest.h"

using namespace std;

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

    this->sets_in_cache = this->blocks_in_cache / this->n_ways;

    this->bitsInSet = log2(this->sets_in_cache);

    this->bitsInTag = ADDRESS_SIZE - bitsInSet - bitsInOffset;

    this->initializeCache();
  }

  /**
   * Guarda un bloque en la caché
   * @param binaryAddress dirección en binario de 32 bits
   */
  bool saveBlockInCache(long binaryAddress)
  {

    CacheRequest *request = new CacheRequest(binaryAddress, this->bitsInOffset, this->bitsInSet);

    long tag, set, offset, address;

    tag = request->getTag();

    set = request->getSet();

    offset = request->getOffset();

    address = request->getBinaryAddress();

    std::cout << "Address: ";
    BaseNParser::printLongInBinary(address, ADDRESS_SIZE);
    std::cout << endl;
    std::cout << "Tag: ";
    BaseNParser::printLongInBinary(tag, this->bitsInTag);
    std::cout << endl;
    std::cout << "Set: ";
    BaseNParser::printLongInBinary(set, this->bitsInSet);
    std::cout << endl;
    std::cout << "Offset: ";
    BaseNParser::printLongInBinary(offset, this->bitsInOffset);
    cout << endl;

    bool inserted = false;

    bool isHit = false;

    size_t lessRecent = 0;

    long currentBlock = n_ways * set;

    long i;

    for (i = currentBlock; i < this->n_ways + currentBlock; ++i)
    {

      bool valid = this->cache[i].getValid();
      cout << "Entrando al for" << endl;

      if (valid && this->cache[i].getTag() == tag)
      {

        this->cache[i].setAccessTime(this->access_time);

        this->access_time++;

        inserted = true;

        isHit = true;

        break;
      }

      if (!valid)
      {

        this->cache[i].setTag(tag);

        this->cache[i].setBlock(address);

        this->cache[i].setValid(true);

        this->cache[i].setAccessTime(this->access_time);

        this->access_time++;

        this->miss_counter++;

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

      cout << "Less recent" << endl;

      this->miss_counter++;
    }

    string hitOrMis = isHit ? "Hit" : "Miss";

    std::cout << "Resultado: " << hitOrMis << endl;

    return isHit;
  }

  void initializeCache()
  {
    this->cache = vector<CacheLine>(this->blocks_in_cache);

    for (int i = 0; i < this->blocks_in_cache; i++)
    {

      this->cache[i] = CacheLine(false);
    }
  }

  string getFeatures()
  {

    string features = "";

    double roundedSize = round(this->getRealSize(this->bitsInTag) * 10) / 10;

    features = "Bloques en cache: " + std::to_string(this->blocks_in_cache) + "\n";

    features += "Conjuntos en cache: " + std::to_string(this->sets_in_cache) + "\n";

    features += "Bits en offset: " + std::to_string(this->bitsInOffset) + "\n";

    features += "Bits en tag: " + std::to_string(this->bitsInTag) + "\n";

    features += "Bits en set: " + std::to_string(this->bitsInSet) + "\n";

    features += "Tamaño efectivo: " + std::to_string((this->blocks_in_cache * WORDS_PER_BLOCK * WORD_SIZE) / 1024) + "KB\n";

    string roundedString = BaseNParser::toFixedString(roundedSize, 1);                  // get the rounded value as a string

    features += "Tamaño real: " + roundedString + "KB\n";

    return features;
  }

  void printFeatures()
  {
    std::ofstream fileCleaner("resultados.out", std::ios::out | std::ios::trunc);

    fileCleaner.close(); // Esta sentencia y la anterior es para limpiar el archivo

    ofstream myFile;

    myFile.open("resultados.out", ios::app); // ahora se abre en modo append

    if (!myFile.is_open())
    {
      throw runtime_error("¡No se pudo abrir el archivo!");
    }

    string features = this->getFeatures();

    std::string output = std::string("  * Caracteristicas de la cache: ") + "\n\n";

    myFile << output;

    myFile << features;

    string hitRate = BaseNParser::toFixedString(this->getHitRate(), 2);
    string missRate = BaseNParser::toFixedString(this->getMissRate(), 2);

    output = std::string("Accesos: ") + std::to_string(this->access_time) + "\n";
    output += std::string("Aciertos: ") + hitRate + "%\n";
    output += std::string("Fallos: ") + missRate + "%\n";

    myFile << output;

    output = std::string("\n * Informacion de bloques: ") + "\n";

    myFile << output;

    for (int i = 0; i < this->sets_in_cache; i++)
    {

      long j = i * this->n_ways;

      output = "\n ********** Conjunto " + std::to_string(i) + '\n';

      myFile << output;

      for (j; j < (i + 1) * this->n_ways; j++)
      {

        output = " * N° Bloque " + std::to_string(j) + '\n';

        myFile << output;

        output = " * Valido: " + std::to_string(this->cache[j].getValid()) + '\n';

        myFile << output;

        output = " * Tag: " + BaseNParser::getBinaryString(this->cache[j].getTag(), this->getBitsInTag()) + '\n';

        myFile << output;

        

        output = " * Dato: " + BaseNParser::getBinaryString(this->cache[j].getBlock(), ADDRESS_SIZE) + "\n";

        myFile << output;

        if ( j + 1 != (i + 1) * this->n_ways ) {
          output = std::string(" ------------------- ") + "\n";

          myFile << output;
        }
      }
    }

    myFile.close();
  }

  void printCacheLines(ofstream *file)
  {

    for (int i = 0; i < this->sets_in_cache; i++)
    {

      long j = i * this->n_ways;

      cout << "Conjunto " << i << endl;

      for (j; j < (i + 1) * this->n_ways; j++)
      {

        cout << "Bloque " << j << endl;

        cout << "Tag: " << this->cache[j].getTag() << endl;

        cout << "Valido: " << this->cache[j].getValid() << endl;

        cout << "Tiempo de acceso: " << this->cache[j].getAccessTime() << endl;

        cout << "Bloque: " << this->cache[j].getBlock() << endl;
      }
    }
  }

  ~SetAssociativeCache()
  {
  }
};

#endif