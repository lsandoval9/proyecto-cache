

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

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
  /**
   * Número de vías de la caché
   */
  long n_ways;

  /**
   * Vector con las líneas de la caché
   */
  vector<CacheLine> cache;

  /**
   * Número de conjuntos de la caché
   */
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

  SetAssociativeCache(long s_block, long s_cache, long n_ways, short replacePolicy) : BaseCache(s_block, s_cache, replacePolicy)
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
   * @param replacePolicy política de reemplazo (0: LRU, 1: FIFO, 2: LFU, 3: Random)
   */
  void saveBlockInCache(long binaryAddress)
  {

    CacheRequest *request = new CacheRequest(binaryAddress, this->bitsInOffset, this->bitsInSet);

    long tag, set, offset, address;

    tag = request->getTag();

    set = request->getSet();

    offset = request->getOffset();

    address = request->getBinaryAddress();

    std::cout << "\033[1m"
              << "Address: "
              << "\033[0m";
    BaseNParser::printLongInBinary(address, ADDRESS_SIZE);
    std::cout << std::endl;
    std::cout << "\033[1m"
              << "Tag: "
              << "\033[0m";
    BaseNParser::printLongInBinary(tag, this->bitsInTag);
    std::cout << std::endl;
    std::cout << "\033[1m"
              << "Set: "
              << "\033[0m";
    BaseNParser::printLongInBinary(set, this->bitsInSet);
    std::cout << std::endl;
    std::cout << "\033[1m"
              << "Offset: "
              << "\033[0m";
    BaseNParser::printLongInBinary(offset, this->bitsInOffset);
    std::cout << std::endl;

    long currentBlock = n_ways * set;

    bool isHit = false;

    switch (this->replacePolicy)
    {
    case 0:
      isHit = this->insertBlockLRU(currentBlock, tag, address);
      break;
    case 1:
      isHit = this->insertBlockLFU(currentBlock, tag, address);
      break;
    case 2:
      isHit = this->insertBlockRandom(currentBlock, tag, address);
      break;
    }

    string hitOrMis = isHit ? "Hit" : "Miss";

    std::cout << "\033[1m"
              << "H/M: "
              << "\033[0m" << hitOrMis << std::endl;
  }

  /**
   * Inserta un bloque en la caché con política de reemplazo LFU
   * LFU consiste en reemplazar el bloque que menos veces se ha usado
   * @param currentBlock bloque actual
   * @param tag etiqueta del bloque
   * @param address dirección binaria
   */
  bool insertBlockLFU(long currentBlock, long tag, long address)
  {

    bool inserted = false;

    bool isHit = false;

    long leastUsed = currentBlock;

    for (long i = currentBlock; i < this->n_ways + currentBlock; ++i)
    {

      bool valid = this->cache[i].getValid();

      cout << "tag: " << this->cache[i].getTag() << endl;
      cout << "address: " << address << endl;

      if (valid && this->cache[i].getTag() == tag)
      {

        this->cache[i].setAccessCounter(this->cache[i].getAccessCounter() + 1);

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

        this->cache[i].setAccessCounter(1);

        this->access_time++;

        this->miss_counter++;

        this->cache[i].setAccessCounter(1);

        inserted = true;

        break;
      }

      if (this->cache[i].getAccessCounter() < this->cache[leastUsed].getAccessCounter())
      {

        leastUsed = i;
      }
    }

    if (!inserted)
    {

      this->cache[leastUsed].setTag(tag);

      this->cache[leastUsed].setBlock(address);

      this->cache[leastUsed].setValid(true);

      this->cache[leastUsed].setAccessCounter(1);

      this->cache[leastUsed].setAccessTime(this->access_time);

      this->access_time++;

      this->miss_counter++;

      cout << "Replaced block: " << leastUsed << endl;
      cout << "Tag: " << this->cache[leastUsed].getAccessCounter() << endl;
    }

    return isHit;
  }

  /**
   * Inserta un bloque en la caché con política de reemplazo LRU
   * LRU consiste en reemplazar el bloque que menos recientemente se ha usado
   * @param currentBlock bloque actual
   * @param tag etiqueta del bloque
   * @param address dirección binaria
   */
  bool insertBlockLRU(long currentBlock, long tag, long address)
  {

    bool inserted = false;

    bool isHit = false;

    long leastRecent = currentBlock;

    for (long i = currentBlock; i < this->n_ways + currentBlock; ++i)
    {

      bool valid = this->cache[i].getValid();

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

      if (this->cache[i].getAccessTime() < this->cache[leastRecent].getAccessTime())
      {

        leastRecent = i;
      }
    }

    if (!inserted)
    {

      this->cache[leastRecent].setTag(tag);

      this->cache[leastRecent].setBlock(address);

      this->cache[leastRecent].setValid(true);

      this->cache[leastRecent].setAccessTime(this->access_time);

      this->access_time++;

      this->miss_counter++;
    }

    return isHit;
  }

  /**
   * Inserta un bloque en la caché con política de reemplazo Random
   * Random consiste en reemplazar un bloque aleatorio. En este caso se obtiene un
   * número aleatorio entre el bloque actual y el bloque actual más el número de vías para reemplazar el conjunto
   * @param currentBlock bloque actual
   * @param tag etiqueta del bloque
   * @param address dirección binaria
   */
  bool insertBlockRandom(long currentBlock, long tag, long address)
  {

    bool inserted = false;

    bool isHit = false;

    long randomBlock;

    std::random_device rd; // obtain a random number from hardware

    std::mt19937 gen(rd()); // seed the generator

    long randomTopExclusive = (currentBlock + n_ways) - 1;

    std::uniform_int_distribution<> distr(currentBlock, randomTopExclusive); // define the range

    randomBlock = distr(gen);

    cout << "Random block: " << randomBlock << endl;

    for (long i = currentBlock; i < this->n_ways + currentBlock; ++i)
    {

      bool valid = this->cache[i].getValid();

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
    }

    if (!inserted)
    {

      this->cache[randomBlock].setTag(tag);

      this->cache[randomBlock].setBlock(address);

      this->cache[randomBlock].setValid(true);

      this->cache[randomBlock].setAccessTime(this->access_time);

      this->access_time++;

      this->miss_counter++;
    }

    return isHit;
  }

  /**
   * Funcion para inicializar la caché
   * Inserta líneas vacías en el vector de líneas de la cache con
   * valid = false y access_time = -1 (-1 indica que no ha sido accedida)
   */
  void initializeCache()
  {
    this->cache = vector<CacheLine>(this->blocks_in_cache);

    for (int i = 0; i < this->blocks_in_cache; i++)
    {

      this->cache[i] = CacheLine(false);
    }
  }

  /**
   * Función para obtener las características de la caché
   * @returns string con las características de la caché
   */
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

    string roundedString = BaseNParser::toFixedString(roundedSize, 1); // get the rounded value as a string

    features += "Tamaño real: " + roundedString + "KB\n";

    return features;
  }

  /**
   * Funcion para imprimir las características de la caché
   */
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

        // cout << "Tag: " << this->cache[j].getTag() << endl;

        myFile << output;

        // cout << "Dato: " << this->cache[j].getBlock() << endl;

        output = " * Dato: " + BaseNParser::getBinaryString(this->cache[j].getBlock(), ADDRESS_SIZE) + "\n";

        myFile << output;

        if (j + 1 != (i + 1) * this->n_ways)
        {
          output = std::string(" ------------------- ") + "\n";

          myFile << output;
        }
      }
    }

    myFile.close();
  }

  void clearCache()
  {
    this->access_time = 0;
    this->miss_counter = 0;

    for (int i = 0; i < this->blocks_in_cache; i++)
    {

      this->cache[i] = CacheLine(false);
    }
  }

  /**
   * Destructor de la clase
   * Libera la memoria del vector de líneas de la caché
   */
  ~SetAssociativeCache()
  {

    this->cache.clear();         // esto es para eliminar cada elemento. No libera la memoria
    this->cache.shrink_to_fit(); // Esto es para liberar la memoria
  }
};

#endif