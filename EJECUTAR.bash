!#/bin/bash

# Compilar y ejecutar el programa
make -s && ./RUN.out;

# Eliminar archivos temporales
make -s clean;

# Eliminar ejecutable
rm RUN.out;