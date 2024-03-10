#!/bin/bash
# Directorios de entrada
LIB_DIR="lib"
TEST_DIR="Test"

# Compilar sala.c en una biblioteca estática
gcc -c $LIB_DIR/sala/sala.c -o $LIB_DIR/sala/sala.o
ar rcs $LIB_DIR/libsala.a $LIB_DIR/sala/sala.o

# Compilar el programa de prueba test.c vinculando la biblioteca estática
gcc $TEST_DIR/test.c -o $TEST_DIR/test -I$LIB_DIR/sala -L$LIB_DIR -lsala

# Limpiar archivos intermedios
rm $LIB_DIR/sala/sala.o

echo "Compilación completa"

./Test/test
