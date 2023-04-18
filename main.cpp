
/**
 * @brief Programa para emular el funcionamiento de una memoria cache para correspondencia directa y asociativa por conjuntos
 * @author Luis Sandoval - 26.781.082
 * @author Gerardo Diaz - TODO
 * Facultad experimental de ciencias y tecnologia - Universidad de Carabobo
 * Arquitectura del computador - Prof. Jose Canache
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

using namespace std;

// librerias propias

#include "helpers/baseNParser.h"
#include "lib/setAssociativeCache.h"

// variables globales

SetAssociativeCache *globalSetAssociativeCache; // Cache para correspondencia por conjuntos de n vias

// prototipos de funciones

void printMenu();

void setValues();

void printFeatures(short option);

void finalizarPrograma();

void imprimirInformacion();

void readBlocksFromFile();

/**
 * Programa para emular el funcionamiento de una memoria cache para correspondencia directa y
 * asociativa por conjuntos
 */
int main(int argc, char const *argv[])
{

  int input = -1;

  std::cout << "¡Bienvenido al programa de emulacion de una memoria cache! V2.0" << endl;
  BaseNParser::printLongInBinary(255, 9);
  std::cout << endl;

  setValues();
  readBlocksFromFile();

  while (input != 0)
  {

    std::cout << endl;
    printMenu();
    cin >> input;
    std::cout << endl;

    switch (input)
    {

    case 1: // Imprimir prestaciones de la cache
      printFeatures(1);
      break;
    case 2:
      printFeatures(2);
      break;
    case 3:
      readBlocksFromFile();
      break;
    case 4: // Reiniciar valores
      setValues();
      break;
    case 5: // imprimir informacion del programa
      imprimirInformacion();
      break;
    case 0: // Salir
      finalizarPrograma();
      break;
    default:
      std::cout << "¡Opcion invalida!";
    }

    sleep(1);
  }

  return 0;
}

// FUNCIONES EXTERNAS

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

  std::cout << "ingrese el tamaño de la memoria cache en KB (potencia de 2): ";

  cin >> s_cache;

  /**
   * @brief Tamaño del bloque en palabras de 32 bits
   */
  s_block = WORDS_PER_BLOCK;

  std::cout << "ingrese el numero de vias (potencia de 2): ";

  cin >> n_ways;

  if (s_cache % 2 != 0 && s_block % 2 != 0)
  {
    throw std::runtime_error("¡El tamaño de la memoria cache y el tamaño del bloque deben ser multiplos de 2!");
  }

  if (s_cache < 1 || s_block < 1)
  {
    throw std::runtime_error("¡El tamaño de la memoria cache y el tamaño del bloque deben ser mayores a 0!");
  }

  if (n_ways % 2 != 0)
  {
    throw std::runtime_error("¡El numero de vias debe ser multiplo de 2!");
  }

  long blockInCache = s_cache * 1024 / (s_block * 4);

  std::cout << "Numero de bloques en la cache12: " << blockInCache << endl;

  if (n_ways > blockInCache)
  {
    throw std::runtime_error("¡El numero de vias no puede ser mayor al tamaño de la cache!");
  }

  globalSetAssociativeCache = new SetAssociativeCache(s_block, s_cache, n_ways);
}

/**
 * Funcion para imprimir el menu de opciones del programa
 */
void printMenu()
{
  std::cout << "Ingrese la opcion deseada a continuacion(1,2,3,...): " << endl;
  std::cout << " 1 - Informacion cache de correspondencia directa" << endl;
  std::cout << " 2 - Informacion asociativa por conjuntos" << endl;
  std::cout << " 3 - NADA" << endl;
  std::cout << " 4 - cambiar valores" << endl;
  std::cout << " 5 - acerca del programa" << endl;
  std::cout << " 0 - salir" << endl;
  std::cout << "seleccion: > ";
}

/**
 * Funcion para imprimir las prestaciones de la cache
 * @param option Opcion de cache a imprimir
 * @note 1 - Cache de correspondencia directa
 * @note 2 - Cache de asociativa por conjuntos de N vias
 */
void printFeatures(short option)
{

  globalSetAssociativeCache->printFeatures();
}

void finalizarPrograma()
{

  std::cout << "\nFin del programa";

  delete globalSetAssociativeCache;

  exit(0);
}

void imprimirInformacion()
{

  std::cout << "Programa para emular el funcionamiento de una memoria cache para correspondencia directa y asociativa por conjuntos" << endl;

  std::cout << "Autores: " << endl;

  std::cout << "Luis Sandoval - 26.781.082" << endl;

  std::cout << "Gerardo Diaz - TODO" << endl;

  std::cout << "Profesor: Jose Canache" << endl;

  std::cout << "Universidad de Carabobo" << endl;

  std::cout << "Facultad Experimental de Ciencias y Tecnologia" << endl;

  std::cout << "Arquitectura del computador" << endl;
}

/**
 * Funcion para guardar un bloque de la memoria principal en la cache
 * @param input Direccion del bloque a guardar
 */
void readBlocksFromFile()
{

  // Read hex numbers from a file where each number is separated by an endline

  ifstream myFile;

  myFile.open("entradas.in", ios::in);

  if (!myFile.is_open())
  {
    throw runtime_error("¡No se pudo abrir el archivo!");
  }
  cout << "Leyendo archivo..." << endl;
  cout << "------------------" << endl;
  while (!myFile.eof())
  {

    string input;

    // Convert hex to binary

    getline(myFile, input);

    std::cout << "Memory block: " << input << endl;

    long number = BaseNParser::parseHexStringToNumber(input);

    globalSetAssociativeCache->saveBlockInCache(number);

    std::cout << endl
              << "-----------------" << endl;
  }

  long miss_rate = globalSetAssociativeCache->getMissCounter();

  long hit_rate = globalSetAssociativeCache->getHitRate();

  cout << endl
       << "*******************" << endl;

  std::cout << " - Miss rate: " << miss_rate << "%" << endl;

  std::cout << " - Hit rate: " << hit_rate << "%" << endl;

  cout << "*******************" << endl;

  myFile.close();
}