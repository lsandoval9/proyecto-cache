
/**
 * @brief Programa para emular el funcionamiento de una memoria cache para correspondencia directa y asociativa por conjuntos
 * @author Luis Sandoval - 26.781.082
 * @author Gerardo Diaz - TODO
 * @organization Arquitectura del computador - Prof. Jose Canache
*/

#ifndef WORD_SIZE

#define WORD_SIZE 32 // Tamaño de la palabra en bits - las palabras usualmente son de 32 bits o 64 bits

#endif


#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>

// librerias propias

#include "helpers/baseNParser.h"
#include "lib/setAssociativeCache.h"
#include "lib/directMappedCache.h"

using namespace std;

// prototipos de funciones

void print_menu();

void set_values(long &s_block, long &s_cache, long &n_ways);

void cache_features(long s_block, long s_cache, long n_ways);

/**
 * Programa para emular el funcionamiento de una memoria cache para correspondencia directa y
 * asociativa por conjuntos
 */
int main(int argc, char const *argv[])
{

  short input = 20;

  long s_block;

  long s_cache;

  long n_ways;

  set_values(s_block, s_cache, n_ways);

  while (input != 0)
  {

    cout << endl;
    print_menu();
    cin >> input;

    switch (input)
    {

    case 1:
      cache_features(s_block, s_cache, n_ways);
      break;
    case 2:
      cout << "Opcion 2";
      break;
    case 3:
      cout << "Opcion 3";
      break;
    case 4:
      set_values(s_block, s_cache, n_ways);
      break;

    case 5:
      cout << "Programa para emular el funcionamiento de una memoria cache para correspondencia directa y asociativa por conjuntos" << endl;
      cout << "Hecho por Luis Sandoval - 26.781.082" << endl;
      cout << "Hecho por Gerardo Diaz - TODO" << endl;
      cout << "Arquitectura del computador - Prof. Jose Canache" << endl;
      break;

    default:
      cout << "¡Opcion invalida!";
    }
  }

  return 0;
}



// FUNCIONES EXTERNAS

/**
 * Funcion para obtener los valores de tamaño de bloque y tamaño de cache
 * @param s_block tamaño del bloque en palabras (referencia)
 * @param s_cache tamaño de la cache en KB (referencia)
 */
void set_values(long &s_block, long &s_cache, long &n_ways) {

  cout << "ingrese el tamaño de la memoria cache en KB (potencia de 2): ";

  cin >> s_cache;

  cout << "ingrese el tamaño del bloque en palabras (potencia de 2): ";

  cin >> s_block;

  cout << "ingrese el numero de vias (potencia de 2): ";

  cin >> n_ways;

  if (s_cache % 2 != 0 && s_block % 2 != 0)
  {
    throw "¡El tamaño de la memoria cache y el tamaño del bloque deben ser multiplos de 2!";
  }

  if (s_cache < 1 || s_block < 1)
  {
    throw "¡El tamaño de la memoria cache y el tamaño del bloque deben ser mayores a 0!";
  }

  if (s_cache % s_block != 0)
  {
    throw "¡El tamaño de la memoria cache debe ser multiplo del tamaño del bloque!";
  }

  if (n_ways % 2 != 0)
  {
    throw "¡El numero de vias debe ser multiplo de 2!";
  }

  if (WORD_SIZE % s_block != 0)
  {
    throw "¡El tamaño de la palabra debe ser multiplo del tamaño del bloque!";
  }

}

/**
 * Funcion para imprimir el menu de opciones del programa
*/
void print_menu()
{
  cout << "Ingrese la opcion deseada a continuacion(1,2,3): " << endl;
  cout << " 1 - ver prestaciones de la cache" << endl;
  cout << " 2 - cache de correspondencia directa" << endl;
  cout << " 3 - cache asociativa por conjuntos" << endl;
  cout << " 4 - asignar bloque de la cache" << endl;
  cout << " 5 - cambiar valores" << endl;
  cout << " 6 - acerca del programa" << endl;
  cout << " 0 - salir" << endl;
  cout << "seleccion: ";
}


void cache_features(long s_block, long s_cache, long n_ways) {

  // SetAssociativeCache *cache = new SetAssociativeCache();

  DirectMappedCache *cache = new DirectMappedCache(s_block, s_cache);

  cache->getFeatures();

}