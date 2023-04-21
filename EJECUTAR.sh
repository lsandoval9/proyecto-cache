#!/bin/bash

# Compilar y ejecutar el programa
make -s && ./RUN.out;

# Eliminar archivos temporales
make -s clean;

# Eliminar ejecutable
rm -f RUN.out main main.o > /dev/null;