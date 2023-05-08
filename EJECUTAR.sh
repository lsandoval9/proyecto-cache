#!/bin/bash

# Verificar si se proporcionó un parámetro
if [ $# -eq 0 ]; then
  # Si no se proporcionó ningún parámetro, asignar el valor 0
  PARAMETER=0
else
  # Si se proporcionó un parámetro, verificar que sea 0 o 1
  if [ "$1" == "0" ] || [ "$1" == "1" ]; then
    PARAMETER="$1"
  else
    echo "Error: el parámetro debe ser 1 o 0"
    exit 1
  fi
fi

# Compilar y ejecutar el programa
make -s && ./RUN.out "$PARAMETER";

# Eliminar archivos temporales
make -s clean;

# Eliminar ejecutable
rm -f RUN.out main main.o > /dev/null;