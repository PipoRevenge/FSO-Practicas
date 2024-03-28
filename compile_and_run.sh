
#!/bin/bash

# Directorios de entrada
LIB_DIR="lib"
PROGRAMS_DIR="programas"
# Compilar sala.c en una biblioteca estática
gcc -c $LIB_DIR/sala/src/sala.c -o $LIB_DIR/sala/sala.o
ar rcs $LIB_DIR/sala/libsala.a $LIB_DIR/sala/sala.o



# Compilar mini-shell.c vinculando la biblioteca estática
gcc $PROGRAMS_DIR/mini-shell/src/mini-shell.c -o $PROGRAMS_DIR/mini-shell/mini-shell.o -I$LIB_DIR/sala/include -L$LIB_DIR/sala -lsala

chmod +x $PROGRAMS_DIR/mini-shell/mini-shell.o
# Compilar sucursal.c
gcc $PROGRAMS_DIR/sucursal/src/sucursal.c -o $PROGRAMS_DIR/sucursal/sucursal


echo "Compilación completa"

"./$PROGRAMS_DIR/sucursal/sucursal"
