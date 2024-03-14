
#!/bin/bash

# Directorios de entrada
LIB_DIR="lib"
TEST_DIR="Test"

# Compilar sala.c en una biblioteca estática
gcc -c $LIB_DIR/sala/src/sala.c -o $LIB_DIR/sala/sala.o
ar rcs $LIB_DIR/sala/libsala.a $LIB_DIR/sala/sala.o

# Compilar el programa de prueba test.c vinculando la biblioteca estática
#gcc $TEST_DIR/test.c -o $TEST_DIR/test -I$LIB_DIR/sala/include -L$LIB_DIR/sala -lsala
gcc $TEST_DIR/test_sala.c -o $TEST_DIR/test_sala -I$LIB_DIR/sala/include -L$LIB_DIR/sala -lsala
# Limpiar archivos intermedios
rm $LIB_DIR/sala/sala.o

echo "Compilación completa"

#"./$TEST_DIR/test"
"./$TEST_DIR/test_sala"
