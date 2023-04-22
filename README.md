# Simulador de memoria cache simple

![Facyt](data:image/png;base64,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)

## Arquitectura del computador

### **Prof. José Canache**

### Autores:

- **Luis A. Sandoval - V26.781.082**
- **Gerardo Diaz - V30.388.971**

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

```bash
  g++ main.cpp -o RUN.out && ./RUN.out
```

## Funcionamiento

El programa le dara la bienvenida al usuario y le pedira que ingrese los parametros de la memoria cache, correspondientes al tamaño de la memoria cache en KB y el numero de vias. **Ambos parametros deben ser potencias de 2.**

Una vez ingresados el programa leera el archivo "entradas.in" e iniciara la simulacion de la memoria cache con los parametros que ingreso el usuario.

Luego de inicializado se mostrara un menu con las opciones disponibles para el usuario, las cuales son:

- **1** - Releer archivo de direcciones
- **2** - Escribir reporte
- **3** - Cambiar valores de la cache
- **4** - Acerca del programa
- **0** - Salir

La primera opcion leera el archivo de direcciones, por lo cual es posible agregar direcciones aun si el programa esta en funcionamiento.

La segunda opcion imprimira un reporte en un archivo de salida llamado "resultados.out", el cual contendra las prestaciones de la cache, informacion sobre los accesos y sobre cada bloque presente en la cache.

La tercera opcion permite al usuario cambiar los valores del tamaño y las vias de la memoria cache. Una vez seleccionada, la memoria cache es eliminada y se creara una nueva memoria cache con los valores seleccionados. Tambien se volvera a leer el archivo de direccionas para inicializar la nueva cache.

La cuarta opcion imprimira informacion sobre el programa.

La quinta y ultima opción finalizara el programa.
