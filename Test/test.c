#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"
#include <stdbool.h>
// Función para imprimir un mensaje de error
void print_error(const char* message) {
  fprintf(stderr, "ERROR: %s\n", message);
}
//Función estado_sala para el depurar
/*
void estado_sala() {
    printf("Capacidad de la sala: %d\n", capacidad_sala());
    printf("Número de asientos ocupados: %d\n", asientos_ocupados());
    printf("Número de asientos libres: %d\n", asientos_libres());
    
    printf("Representación de los asientos:\n");
    for (int i = 0; i < capacidad_sala(); i++) {
        if (*(ptr + i) != -1) {
            printf("[%d] ", i + 1);
        }
    }

    printf("\n");
}
*/
// Función para probar la función crea_sala
void test_crea_sala() {
	
	// Caso 1: Capacidad válida

	int capacidad = 10;
	int resultado = crea_sala(capacidad);
	if (resultado != capacidad) {
		print_error("crea_sala no devolvió la capacidad correcta");
	}
	elimina_sala();
	
	// Caso 2: Capacidad no válida
	capacidad = -1;
	resultado = crea_sala(capacidad);
	if (resultado != -1) {
		print_error("crea_sala no devolvió un error para una capacidad negativa");
	}

    	// Caso 3: Sala Existente
    	crea_sala(capacidad);
	resultado = crea_sala(capacidad);
	if (resultado != -1) {
		print_error("crea_sala no devolvió un error para crear sala sobre una sala existente");
	}
	
	// Caso 4: Asignación de memoria exitosa
	capacidad = 10;
	resultado = crea_sala(capacidad);
	if (resultado != capacidad) {
		print_error("crea_sala no pudo asignar memoria correctamente");
	}
	elimina_sala();
	/*								Preguntar
	printf("Caso 5 \n");
	// Caso 5: Asignación de memoria fallida
	capacidad = 1000000000;
	resultado = crea_sala(capacidad);
	if (resultado != -1) {
		print_error("crea_sala no devolvió un error para una asignación de memoria fallida");
	}
	elimina_sala();
	*/
	return;
}


/*
Función: elimina_sala
Escenarios:
	Sala existente
	Sala no existente
	Liberación de memoria exitosa?
*/
// Función para probar la función elimina_sala
void test_elimina_sala() {

	// Caso 1: Sala existente
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = elimina_sala();
	if (resultado != 0) {
		print_error("elimina_sala no pudo eliminar la sala existente");
	}

	// Caso 2: Sala no existente

	resultado = elimina_sala();
	if (resultado != -1) {
		print_error("elimina_sala no devolvió un error para una sala no existente");
	}
}

/*
Función: capacidad_sala
Escenarios:
Sala con capacidad válida
Sala sin crear
*/


// Función para probar la función capacidad_sala
void test_capacidad_sala() {
	// Caso 1: Sala con capacidad válida
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = capacidad_sala();
	if (resultado != capacidad) {
		print_error("capacidad_sala no devolvió la capacidad correcta");
	}
	elimina_sala();

	// Caso 2: Sala sin crear
	resultado = capacidad_sala();
	if (resultado != -1) {
		print_error("capacidad_sala no devolvió un error para una sala no creada");
	}
}

/*
Función: asientos_libres
Escenarios:
Sala con asientos libres
Sala sin asientos libres
Sala sin crear
*/

// Función para probar la función asientos_libres
void test_asientos_libres() {
	// Caso 1: Sala con asientos libres
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = asientos_libres();
	if (resultado != capacidad) {
		print_error("asientos_libres no devolvió la cantidad correcta de asientos libres");
	}

	// Caso 2: Sala sin asientos libres
	for (int i = 1; i <= capacidad+1; i++) {
		reserva_asiento(i+1);
		
	}
	
	resultado = asientos_libres();
	if (resultado != 0) {
		print_error("asientos_libres no devolvió 0 para una sala sin asientos libres");
	}
	elimina_sala();

	// Caso 3: Sala sin crear
	resultado = asientos_libres();
	if (resultado != -1) {
		print_error("asientos_libres no devolvió un error para una sala no creada");
	}
}


/*
Función: asientos_ocupados
Escenarios:
Sala con asientos ocupados
Sala sin asientos ocupados
Sala sin crear
*/




// Función para probar la función asientos_ocupados
void test_asientos_ocupados() {
	// Caso 1: Sala con asientos ocupados
	int capacidad = 10;
	crea_sala(capacidad);
	for (int i = 1; i <= capacidad+1; i++) {
		reserva_asiento(i+1);
	}
	int resultado = asientos_ocupados();
	printf("\n %d \n", resultado);
	if (resultado != capacidad) {
		print_error("asientos_ocupados no devolvió la cantidad correcta de asientos ocupados");
	}

	// Caso 2: Sala sin asientos ocupados
	for (int i = 0; i < capacidad; i++) {
		libera_asiento(i+1);
	}
	resultado = asientos_ocupados();
	if (resultado != 0) {
	printf("\n %d \n", resultado);
		print_error("asientos_ocupados no devolvió 0 para una sala sin asientos ocupados");
	}
	elimina_sala();

	// Caso 3: Sala sin crear
	resultado = asientos_ocupados();
	if (resultado != -1) {
		print_error("asientos_ocupados no devolvió un error para una sala no creada");
	}
}
/*
Función: estado_asiento
Escenarios:
Asiento libre
Asiento ocupado
Asiento fuera del rango
Sala sin crear
*/


// Función para probar la función estado_asiento
void test_estado_asiento() {
	// Caso 1: Asiento libre
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = estado_asiento(1);
	if (resultado != 0) {
		print_error("estado_asiento no devolvió 0 para un asiento libre");
	}

	// Caso 2: Asiento ocupado
	reserva_asiento(1);
	resultado = estado_asiento(1);
	if (resultado != 1) {
		print_error("estado_asiento no devolvió el ID correcto para un asiento ocupado");
	}

	// Caso 3: Asiento fuera del rango
	resultado = estado_asiento(capacidad + 1);
	if (resultado != -1) {
		print_error("estado_asiento no devolvió un error para un asiento fuera del rango");
	}
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = estado_asiento(1);
	if (resultado != -1) {
		print_error("estado_asiento no devolvió un error para una sala no creada");
	}
}

/*
Función: reserva_asiento
Escenarios:
Asiento libre disponible
Asiento no disponible
ID de persona no válido
Sala sin crear

Falta:
reservar con el mismo id ?
*/



// Función para probar la función reserva_asiento
void test_reserva_asiento() {
	// Caso 1: Asiento libre disponible
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = reserva_asiento(1);
	if (resultado != 1) {
		print_error("reserva_asiento no devolvió el número de asiento correcto para un asiento libre");
	}

	// Caso 2: Asiento no disponible
	resultado = reserva_asiento(1);
	for (int i = 1; i<capacidad; i++){
		reserva_asiento(i);
	
	}
	resultado=reserva_asiento(1);
	if (resultado != -1) {
		print_error("reserva_asiento no devolvió un error para un asiento no disponible");
	}
	elimina_sala();
	crea_sala(capacidad);
	// Caso 3: ID de persona no válido
	resultado = reserva_asiento(-1);
	if (resultado != -1) {
		print_error("reserva_asiento no devolvió un error para un ID de persona no válido");
	}
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = reserva_asiento(1);
	if (resultado != -1) {
		print_error("reserva_asiento no devolvió un error para una sala no creada");
	}
}
/*
Función: libera_asiento
Escenarios:
Asiento ocupado
Asiento ya libre
Asiento fuera del rango
Sala sin crear
*/

// Función para probar la función libera_asiento
void test_libera_asiento() {
	// Caso 1: Asiento ocupado
	int capacidad = 10;
	crea_sala(capacidad);
	reserva_asiento(1);
	int resultado = libera_asiento(1);
	if (resultado != 1) {
		print_error("libera_asiento no devolvió el ID correcto para un asiento liberado");
	}

	// Caso 2: Asiento ya libre
	resultado = libera_asiento(1);
	if (resultado != -1) {
		print_error("libera_asiento no devolvió un error para un asiento ya liberado");
	}

	// Caso 3: Asiento fuera del rango
	resultado = libera_asiento(capacidad + 1);
	if (resultado != -1) {
		print_error("libera_asiento no devolvió un error para un asiento fuera del rango");
	}
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = libera_asiento(1);
	if (resultado != -1) {
		print_error("libera_asiento no devolvió un error para una sala no creada");
	}
}






/* Main */

int main() {
	// Ejecutar las pruebas
	printf("Prueba de crea_sala:\n");
	test_crea_sala();
	printf("Prueba de elimina_sala:\n");
	test_elimina_sala();
	printf("Prueba de capacidad_sala:\n");
	test_capacidad_sala();
	printf("Prueba de asientos_libres:\n");
	test_asientos_libres();
	printf("Prueba de asientos_ocupados:\n");
	test_asientos_ocupados();
	printf("Prueba de estado_asiento:\n");
	test_estado_asiento();
	printf("Prueba de reserva_asiento:\n");
	test_reserva_asiento();
	printf("Prueba de libera_asiento:\n");
	test_libera_asiento();
	
	return 0;
}

