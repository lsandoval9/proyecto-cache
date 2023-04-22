# Makefile para compilar archivos en el directorio actual 

# Nombre del ejecutable. Deseable en mayusculas
TARGET = RUN.out
# Bibliotecas incluidas, la biblioteca math.h es una muy comun
LIBS = -lm
# Compilador utilizado, por ejemplo icc, pgcc , gcc
CC = g++
# Banderas del compilador, por ejemplo -DDEBUG -02 -03 -wall -g
CFLAGS = -gcc

# Palabras que usa el Makefile que podrian ser el nombre de un Programa
.PHONY: default all clean

# Compilacion por defecto
default: $(TARGET)
all: default

# Incluye los archivos .o y .c que estan en el directorio actual
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Incluye los archivos.h que estan en el directorio actual
HEADERS = $(wildcard *.h)

# compila automaticamente solo archivos fuente que se han Modificado
# $< es el primer prerrequisito, generalmente el archivofuente
# $@ nombre del archivo que se esta generando, archivo objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Preserva archivos intermedios
.PRECIOUS: $(TARGET) $(OBJECTS)

# Enlaza objetos y crea el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

# Borra archivos .o
clean:
	-rm -f *.o core

# Borra archivos .o y el ejecutable
cleanall: clean
	-rm -f $(TARGET)