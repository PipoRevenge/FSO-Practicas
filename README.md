# FSO-Practicas

## Enlace al proyecto en github
El código de esta librería se basa en el proyecto original disponible en [FSO-Practicas](https://github.com/PipoRevenge/FSO-Practicas).

[Práctica 1](https://github.com/PipoRevenge/FSO-Practicas/tree/P1)
## Autores
- Alejandro Sosa Cerdeña (GitHub: [PipoRevenge](https://github.com/PipoRevenge))
- Pablo Medina Quintana (GitHub: [Medichi2002](https://github.com/Medichi2002))

## Descripción

Este proyecto contiene código y pruebas para una biblioteca de gestión de salas. La estructura del proyecto se detalla a continuación.

### Estructura

En primer lugar, creamos un directorio llamado `FSO-Practicas` que contiene los siguientes elementos:

- `lib`: Un directorio que contiene la librería `libsala.a`.
  - `sala`: Directorio que alberga el código fuente de la librería.
    - `include`: Contiene la cabecera `sala.h`.
    - `src`: Contiene el archivo `sala.c`.
    - `libsala.a`: libreria estatica.
- `Test`: Un directorio que contiene el archivo `test_sala.c`, que incluye la batería de pruebas.
- `compile_and_run.sh`: Un script para compilar y ejecutar el código.

### Ejecución del Código y Pruebas

Para ejecutar el código y las pruebas, sigue estos pasos:

1. Descomprime el archivo ZIP si es necesario.
2. Situarse en el directorio del proyecto.
3. Otorga permisos de ejecución al script `compile_and_run.sh` con el comando `chmod +x compile_and_run.sh`.
4. Ejecuta el script `./compile_and_run.sh`.

Este script se encarga de las siguientes tareas:
- Compilar `sala.c` con el comando: `gcc -c lib/sala/src/sala.c -o lib/sala/sala.o`.
- Crear la librería `libsala.a` con el comando: `ar rcs lib/sala/libsala.a lib/sala/sala.o`.
- Compilar la prueba con el comando: `gcc test_sala.c -o test_sala -Ilib/sala/include -Llib/sala -lsala`.

### Llamadas al Sistema

A continuación se detallan algunas llamadas al sistema útiles:

- `ls`: Ver las carpetas del directorio actual.
- `cd`: Avanzar o retroceder de directorio.
- `mkdir`: Crear una carpeta.
- `gedit`: Crear y editar un archivo.
- `cp`: Copiar un archivo.
- `gcc`: Compilar un archivo.
- Ejecución de archivos compilados: `./nombre_del_ejecutable`.

### Metodología

Aquí se comentará principalmente el proceso de elaboración del archivo `sala.c` y el de `test_sala.c` donde se implementan y se testean los métodos de la librería `libsala.a` respectivamente.

En el archivo `sala.c` se hacen dos "include" para incluir las librerías `<stdlib.h>`, `<stdio.h>` y `<stdbool.h>`. A continuación, se declaran tres variables globales: `int* ptr` (Puntero con el que se recorrerá la sala), `int capacidad_main` (Entero positivo que representa la capacidad de la sala) e `int asientos_ocu` (Entero que representa los asientos ocupados de la sala).

#### Funciones
# Gestor de Salas - Librería

Esta librería proporciona funciones para gestionar una sala de forma dinámica. Permite crear una sala con una capacidad determinada, reservar y liberar asientos, y obtener información sobre la ocupación de la sala.

## Funciones

### `int crea_sala(int capacidad)`

Crea una sala con la capacidad especificada. Devuelve la capacidad de la sala creada si tiene éxito, o -1 en caso de error.

### `int elimina_sala()`

Elimina la sala existente. Devuelve 0 si tiene éxito, o -1 si no hay ninguna sala creada.

### `int capacidad_sala()`

Devuelve la capacidad de la sala actual.

### `int asientos_libres()`

Devuelve el número de asientos libres en la sala.

### `int asientos_ocupados()`

Devuelve el número de asientos ocupados en la sala.

### `int estado_asiento(int id_asiento)`

Devuelve el estado del asiento especificado por su ID. Retorna el ID del ocupante si está ocupado, 0 si está libre, o -1 en caso de error.

### `int reserva_asiento(int id_persona)`

Reserva un asiento para la persona con el ID especificado. Devuelve el número de asiento reservado si tiene éxito, o -1 en caso de error.

### `int libera_asiento(int id_asiento)`

Libera el asiento especificado por su ID. Devuelve el ID de la persona que ocupaba el asiento liberado si tiene éxito, o -1 en caso de error.

## Variables Globales

- `int* ptr`: Puntero de memoria para la sala.
- `int capacidad_main`: Capacidad de la sala.
- `int asientos_ocu`: Número de asientos ocupados en la sala.

## Control de Errores

La librería gestiona errores mediante la función `print_error(const char* msg)`, que imprime un mensaje de error en la salida estándar de errores.


## Pruebas Unitarias

### Prueba de `crea_sala()`

- Caso 1: Capacidad válida
- Caso 2: Capacidad no válida
- Caso 3: Sala Existente
- Caso 4: Asignación de memoria exitosa

### Prueba de `elimina_sala()`

- Caso 1: Sala existente
- Caso 2: Sala no existente

### Prueba de `capacidad_sala()`

- Caso 1: Sala con capacidad válida
- Caso 2: Sala sin crear

### Prueba de `asientos_libres()`

- Caso 1: Sala con asientos libres
- Caso 2: Sala sin asientos libres
- Caso 3: Sala sin crear

### Prueba de `asientos_ocupados()`

- Caso 1: Sala con asientos ocupados
- Caso 2: Sala sin asientos ocupados
- Caso 3: Sala sin crear

### Prueba de `estado_asiento()`

- Caso 1: Asiento libre
- Caso 2: Asiento ocupado
- Caso 3: Asiento fuera del rango
- Caso 4: Sala sin crear

### Prueba de `reserva_asiento()`

- Caso 1: Asiento libre disponible
- Caso 2: Asiento no disponible
- Caso 3: ID de persona no válido
- Caso 4: Sala sin crear

### Prueba de `libera_asiento()`

- Caso 1: Asiento ocupado
- Caso 2: Asiento ya libre
- Caso 3: Asiento fuera del rango
- Caso 4: Sala sin crear


