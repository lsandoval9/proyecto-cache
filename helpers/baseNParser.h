
#include "../constants/constants.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <map>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef BASENPARSER_H

#define BASENPARSER_H

/**
 * @brief clase para parsear numeros hexadecimales a binarios y viceversa
 * tambien permite imprimir numeros con una base especifica
 */
class BaseNParser
{

private:
  BaseNParser() {}

public:
  ~BaseNParser()
  {
  }

  /**
   * @brief transforma un string de numeros hexadecimales a un numero decimal
   * @param hexString string de numeros hexadecimales
   * @return numero decimal (long)
   */
  static long parseHexStringToNumber(string hexString)
  {
    long hexNumber = stol(hexString, nullptr, 16);

    return hexNumber;
  }

  /**
   * @brief convierte un numero decimal (long) a binario y lo imprime
   * @param number numero decimal a convertir
   * @param bits cantidad de bits que tendra el numero binario. Si number es menor al numero de bits, se rellena con ceros a la izquierda
   */
  static void printLongInBinary(long number, long bits)
  {

    std::bitset<32> binary(number);             // convierte el número a binario con 32 bits
    std::string binaryStr = binary.to_string(); // convierte el número binario a una cadena de caracteres

    // si la cantidad de bits es menor a 32, se recorta la cadena para que tenga la cantidad de bits especificada
    if (bits < 32)
    {
      binaryStr = binaryStr.substr(32 - bits);
    }

    std::cout << "0b" << std::setfill('0') << std::setw(bits) << binaryStr;
  }

  /**
   * @brief convierte un numero decimal (long) a binario y lo imprime
   * con una cantidad de bits especifica
   */
  static string getBinaryString(long number, long bits)
  {

    std::bitset<32> binary(number);             // convierte el número a binario con 32 bits
    std::string binaryStr = binary.to_string(); // convierte el número binario a una cadena de caracteres

    // si la cantidad de bits es menor a 32, se recorta la cadena para que tenga la cantidad de bits especificada
    // 32 es el tamaño maximo de la direccion en bits
    if (bits < 32)
    {
      binaryStr = binaryStr.substr(32 - bits);
    }

    return binaryStr;
  }

  /**
   * @brief convierte un numero decimal (long) a binario y transforma cada bit en un caracter
   * @returns string con los caracteres 0 y 1
   */
  static string toFixedString(double number, int precision)
  {

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << number;
    return out.str();
  }
};

#endif