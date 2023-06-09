# Simulador de memoria cache simple

![Facyt](https://i.imgur.com/6dG2xdx.png)

## Arquitectura del computador

### **Prof. José Canache**

### Autores:

- **Luis A. Sandoval - V26.781.082**
- **Gerardo Diaz - V30.388.971**

<br>

## <u>**NOTA**</u>: Los archivos LaTex estan en la carpeta LaTex. En la raiz estan los PDFs finales y en cada carpeta el codigo fuente de cada uno.

<br>
## Introducción

El programa esta diseñado para emular el funcionamiento de una memoria cache sencilla. Permite cambiar valores de forma dinamica y generar reportes.

## **Aclaraciones**

- **IMPORTANTE**: se necesita tener instalado el compilador de C++ **g++** para poder ejecutar el programa con el script **EJECUTAR.sh**, ademas del make. Caso contrario se debera compilar a mano el programa.
- por defecto las palabras son siempre de 32 bits (4 bytes)
- las direcciones son de 32 bits
- los bloques son de 4 palabras
- el archivo de entrada debe llamarse **"entradas.in"** y contener direcciones en hexadecimal de 32 bits, es decir, 8 digitos en hexadecimal en el formato **0xXXXXXXXX**, por ejemplo: **0x00000000**
- el archivo de salida se llamara **"resultados.out"**

## Ejecucion

Para ejecutar el programa se ha creado un archivo en bash para compilar y para ejecutar el programa usando makefile.

Para compilar el programa se debe ejecutar el siguiente comando:

```bash
./EJECUTAR.sh
```

Este script se encarga de compilar el programa y de ejecutarlo, ademas de limpiar los archivos temporales que se generan al compilar.

Tambien es posible ejecutar el programa manualmente, de la siguiente manera:

```bash
  make && ./RUN.out
```

o si no se tiene instalado make:

```bash
  g++ -std=c++11 main.cpp -o RUN.out && ./RUN.out
```

## Configuración

El programa admite un archivo de configuracion llamado config.json, el cual contiene los parametros de la memoria cache, los cuales son:

- **tamaño**(s_cache): tamaño de la memoria cache en KB
- **vias**(n_ways): numero de vias de la memoria cache
- **Politica de reemplazo**(replace_policy): politica de reemplazo de la cache **(0: LRU, 1: LFU, 2: RANDOM)**

ejemplo del archivo:

```json
{
  "s_cache": 1,
  "n_ways": 1,
  "replace_policy": 0
}
```

para indicarle al programa que lea el archivo en vez de solicitar los valores de la cache al usuario, se debe ejecutar el programa con un argumento booleano donde 1 es para leer el archivo y 0. Por ejemplo:

```bash
EJECUTAR.sh 1
```

tambien se puede ejecutar sin el uso del script o del make:

```bash
  make && ./RUN.out 1
```

o si no se tiene instalado make:

```bash
  g++ -std=c++11 main.cpp -o RUN.out && ./RUN.out 1
```

## Funcionamiento

El programa le dara la bienvenida al usuario y le pedira que ingrese los parametros de la memoria cache, correspondientes al tamaño de la memoria cache en KB y el numero de vias. **Ambos parametros deben ser potencias de 2.**

Una vez ingresados el programa leera el archivo "entradas.in" e iniciara la simulacion de la memoria cache con los parametros que ingreso el usuario.

Luego de inicializado se mostrara un menu con las opciones disponibles para el usuario, las cuales son:

- **1** - Releer archivo de direcciones
- **2** - Escribir reporte ('**resultados.out**')
- **3** - Cambiar valores de la cache
- **4** - Acerca del programa
- **0** - Salir

La primera opcion leera el archivo de direcciones, por lo cual es posible agregar direcciones aun si el programa esta en funcionamiento.

La segunda opcion imprimira un reporte en un archivo de salida llamado "resultados.out", el cual contendra las prestaciones de la cache, informacion sobre los accesos y sobre cada bloque presente en la cache.

La tercera opcion permite al usuario cambiar los valores del tamaño y las vias de la memoria cache. Una vez seleccionada, la memoria cache es eliminada y se creara una nueva memoria cache con los valores seleccionados. Tambien se volvera a leer el archivo de direccionas para inicializar la nueva cache.

La cuarta opcion imprimira informacion sobre el programa.

La quinta y ultima opción finalizara el programa.

## Benchmark

Se ha creado un script en Python 3 para correr el ejecutable del archivo llamado 'RUN.out' [(ver arriba como ejecutar el programa)](#compilacion). El script ejecuta el programa como un proceso y mide el uso del CPU, memoria RAM, y el tiempo real de ejecutacion (descartando el tiempo de usuario y del sistema).

**NOTA**: Dependiendo de la version de Python, puede que el script no se ejecute, principalmente en versiones muy actuales.

Tambien puede que en ciertas versiones el script mida el tiempo absoluto del programa, descartando el tiempo de la salida estandar (cout de c++, por ejemplo), la cual es diferida, por lo que el tiempo puede ser mucho menor que en los casos de prueba.