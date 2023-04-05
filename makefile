# Makefile para compilar archivos en el directorio actual 
#nombre del ejecutable. Deseable en mayusculas

TARGET = RUN.out
#Bibliotecas incluidas, la biblioteca math.h es una muy comun
LIBS = -lm
#Compilador utilizado, por ej icc, pgcc , gcc
CC = g++
#Banderas del compilador, por ej -DDEBUG -02 -03 -wall -g
CFLAGS = -gcc

# Palabras que usa el Makefile que podrian ser el nombre de un Programa
.PHONY: default all clean
# compilacion por defecto

default: $(TARGET)
all: default
# incluye los archivos .o y .c que estan en el directorio actual
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
# incluye los archivos.h que estan en el directorio actual
HEADERS = $(wildcard *.h)
# compila automaticamente solo archivos fuente que se han Modificado
# $< es el primer prerrequisito, generalmente el archivofuente
#$@ nombre del archivo que se esta generando, archivo objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
#preserva archivos intermedios
.PRECIOUS: $(TARGET) $(OBJECTS)
# enlaza objetos y crea el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@
# borra archivos .o
clean:
	-rm -f *.o core
#borra archivos .o y el ejecutable
cleanall: clean
	-rm -f $(TARGET)