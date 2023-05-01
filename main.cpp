
/**
 * @brief Programa para emular el funcionamiento de una memoria cache para correspondencia directa y asociativa por conjuntos
 * @author Luis Sandoval - 26.781.082
 * @author Gerardo Diaz - 30.388.971
 * Facultad Experimental de Ciencias y Tecnologia - Universidad de Carabobo
 * Arquitectura del Computador - Prof. Jose Canache
 */

// constantes

#include "./constants/constants.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <map>
#include <bitset>
#include <fstream>
#include <math.h>
#include <vector>
#include <random>
#include <limits>

using namespace std;

// librerias propias

#include "helpers/baseNParser.h"
#include "lib/setAssociativeCache.h"

// variables globales

SetAssociativeCache *globalSetAssociativeCache; // Cache para correspondencia por conjuntos de n vias

// prototipos de funciones

void printMenu();

void setValues();

void finalizarPrograma();

void imprimirInformacion();

void readBlocksFromStructure();

void writeFeatures();

/**
 * Programa para emular el funcionamiento de una memoria cache para correspondencia directa y
 * asociativa por conjuntos
 */
int main(int argc, char const *argv[])
{
  int input = -1;

  std::cout << "¡Bienvenido al programa de emulacion de una memoria cache!" << endl
            << endl;

  setValues();
  readBlocksFromStructure();

  while (input != 0)
  {

    std::cout << endl;
    printMenu();
    cin >> input;
    std::cout << endl;

    switch (input)
    {

    case 1: // Imprimir prestaciones de la cache
      readBlocksFromStructure();
      break;
    case 2:
      writeFeatures();
      break;
    case 3: // Reiniciar valores
      setValues();
      readBlocksFromStructure();
      break;
    case 4: // imprimir informacion del programa
      imprimirInformacion();
      break;
    case 0: // Salir
      finalizarPrograma();
      break;
    default:
      std::cout << "¡Opcion invalida!";
    }
  }

  return 0;
}

// FUNCIONES

/**
 * Funcion para obtener los valores de tamaño de bloque y tamaño de cache
 * @param s_block Tamaño del bloque
 * @param s_cache Tamaño de la cache
 * @param n_ways Numero de vias
 */
void setValues()
{
  long s_block; // Tamaño del bloque en palabras de 32 bits

  long s_cache; // Tamaño de la cache en KBs

  long n_ways; // Numero de vias

  short replacementPolicy; // Politica de reemplazo

  std::cout << "Ingrese el tamaño de la memoria cache en KB (potencia de 2)" << endl;
  std::cout << "> ";

  cin >> s_cache;

  /**
   * @brief Tamaño del bloque en palabras de 32 bits
   */
  s_block = WORDS_PER_BLOCK;

  std::cout << "Ingrese el numero de vias (potencia de 2)" << endl;
  std::cout << "NOTA: 0 es un atajo para completamente asociativa" << endl;
  std::cout << "> ";
  cin >> n_ways;

  std::cout << "Ingrese la politica de reemplazo (0: LRU, 1: LFU, 2: RANDOM)" << endl;
  std::cout << "> ";
  std::cin >> replacementPolicy;

  long blockInCache = s_cache * 1024 / (s_block * 4);

  if (replacementPolicy < 0 || replacementPolicy > 2)
  {
    throw std::runtime_error("¡La politica de reemplazo debe ser 0, 1 o 2!");
  }

  if (n_ways == 0)
  {
    n_ways = blockInCache;
  }

  // chequear que el tamaño de la cache en kilobytes no supere los 32 bits
  if (s_cache > (pow(2, 32) - 1))
  {
    throw std::runtime_error("¡El tamaño de la cache supera el limite de direccionamiento (32 bits)!");
  }

  if ((s_block & (s_block - 1)) != 0)
  {
    throw std::runtime_error("¡El tamaño de la memoria cache debe ser potencia de 2!");
  }

  if (s_cache < 1 || s_block < 1)
  {
    throw std::runtime_error("¡El tamaño de la memoria cache y el tamaño del bloque deben ser mayores a 0!");
  }

  if ((s_cache & (s_cache - 1)) != 0)
  {
    throw std::runtime_error("¡El tamaño de la memoria cache debe ser potencia de 2!");
  }

  if ((n_ways & (n_ways - 1)) != 0)
  {
    throw std::runtime_error("¡El numero de vias debe ser multiplo de 2!");
  }

  if (n_ways > blockInCache)
  {
    throw std::runtime_error("¡El numero de vias no puede ser mayor al tamaño de la cache (en bloques)!");
  }

  globalSetAssociativeCache = new SetAssociativeCache(s_block, s_cache, n_ways, replacementPolicy);
}

/**
 * Funcion para imprimir el menu de opciones del programa
 */
void printMenu()
{
  std::cout << "Ingrese la opcion deseada a continuacion(1,2,3,...): " << endl;
  std::cout << " 1 - Releer archivo de direcciones" << endl;
  std::cout << " 2 - Escribir reporte (resultados.out)" << endl;
  std::cout << " 3 - Cambiar valores de la cache" << endl;
  std::cout << " 4 - Acerca del programa" << endl;
  std::cout << " 0 - Salir" << endl;
  std::cout << "seleccion: > ";
}

/**
 * Finaliza la ejecucion del programa y libera la memoria
 */
void finalizarPrograma()
{
  std::cout << "\nFin del programa" << endl;

  delete globalSetAssociativeCache;

  exit(0);
}

/**
 * Imprime la informacion del programa y de los integrantes del equipo
 */
void imprimirInformacion()
{
  std::cout << "* Programa para emular el funcionamiento de una memoria cache simple" << endl;

  std::cout << "\nAutores: " << endl;

  std::cout << "  * Luis Sandoval - 26.781.082" << endl;

  std::cout << "  * Gerardo Diaz -  30.388.971" << endl;

  std::cout << "Universidad de Carabobo" << endl;

  std::cout << "Facultad Experimental de Ciencias y Tecnologia" << endl;

  std::cout << "Arquitectura del computador" << endl;

  std::cout << "Profesor: Jose Canache" << endl;
}

void readBlocksFromStructure()
{

  globalSetAssociativeCache->clearCache();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<long> dis(0, 4096);
  // std::numeric_limits<long>::max() -> 32bits
  long address;

  // Generate 5000 random hexadecimal addresses
  std::vector<long> myVector;
  for (int i = 0; i < 5000; i++) {
    address = dis(gen);
    myVector.push_back(address);
  }

  /**
   * NOTA: separé la creación del vector y la lectura de las direcciones para poder hacer las pruebas sobre
   * estructuras de datos distintas, en este caso, un vector como dijo el profesor.
  */

  for (int i = 0; i < myVector.size(); i++)
  {
    address = myVector[i];
    std::cout << "Dirección en hexadecimal: " << std::hex << address << std::endl;
    std::cout << "\033[1m" << "Memory block:" << "\033[0m" << " " << std::hex << address << std::endl;
    
    globalSetAssociativeCache->saveBlockInCache(address);
    
    std::cout << std::endl << "-----------------" << std::endl;
  }

  double miss_rate = std::round(globalSetAssociativeCache->getMissRate() * 100) / 100;

  double hit_rate = std::round(globalSetAssociativeCache->getHitRate() * 100) / 100;

  long accessCounter = globalSetAssociativeCache->getAccessTime();

  std::cout << endl
       << "*******************" << endl;

  std::cout << "Operaciones en total: " << std::dec << accessCounter << endl;

  std::cout << " - Tasa de Aciertos: " << std::dec << hit_rate << "%" << endl;

  std:: cout << " * contador de aciertos: " << std::dec << globalSetAssociativeCache->getAccessTime() << endl;

  std::cout << " - Tasa de Fallos: " << std::dec << miss_rate << "%" << endl;

  std:: cout << " * contador de fallos: " << std::dec << globalSetAssociativeCache->getMissCounter() << endl;

  std::cout << "*******************" << endl;
}

/**
 * Funcion para imprimir las prestaciones de la cache
 */
void writeFeatures()
{
  globalSetAssociativeCache->printFeatures();
}