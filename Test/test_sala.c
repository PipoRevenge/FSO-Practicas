// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//
#include "sala.h"
#include <assert.h>
#include <stdio.h>

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
 	// fflush fuerza que se imprima el mensaje anterior
	// sin necesidad de utilizar un salto de línea
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n");
}
// Función para probar la función crea_sala
void test_crea_sala() {
	INICIO_TEST("crea_sala");
	// Caso 1: Capacidad válida
	int capacidad = 10;
	int resultado = crea_sala(capacidad);
	DebeSerCierto(resultado == capacidad);
	elimina_sala();

	// Caso 2: Capacidad no válida
	capacidad = -1;
	resultado = crea_sala(capacidad);
	DebeSerCierto(resultado == -1);

	// Caso 3: Sala Existente
	crea_sala(capacidad);
	resultado = crea_sala(capacidad);
	DebeSerCierto(resultado == -1);
	
	// Caso 4: Asignación de memoria exitosa
	capacidad = 10;
	resultado = crea_sala(capacidad);
	DebeSerCierto(resultado == capacidad);
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

	FIN_TEST("crea_sala");
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
	INICIO_TEST("elimina_sala");
	// Caso 1: Sala existente
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = elimina_sala();
	DebeSerCierto(resultado == 0);

	// Caso 2: Sala no existente
	resultado = elimina_sala();
	DebeSerCierto(resultado == -1);

	FIN_TEST("elimina_sala");
}

/*
Función: capacidad_sala
Escenarios:
Sala con capacidad válida
Sala sin crear
*/


// Función para probar la función capacidad_sala
void test_capacidad_sala() {
	INICIO_TEST("capacidad_sala");
	// Caso 1: Sala con capacidad válida
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = capacidad_sala();
	DebeSerCierto(resultado == capacidad);

	elimina_sala();

	// Caso 2: Sala sin crear
	resultado = capacidad_sala();
	DebeSerCierto(resultado == -1);

	FIN_TEST("capacidad_sala");
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
	INICIO_TEST("asientos_libres");
	// Caso 1: Sala con asientos libres
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = asientos_libres();
	DebeSerCierto(resultado == capacidad);

	// Caso 2: Sala sin asientos libres
	for (int i = 1; i <= capacidad+1; i++) {
		reserva_asiento(i+1);
	}
	
	resultado = asientos_libres();
	DebeSerCierto(resultado == 0);
	elimina_sala();

	// Caso 3: Sala sin crear
	resultado = asientos_libres();
	DebeSerCierto(resultado == -1);

	FIN_TEST("asientos_libres");
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
	INICIO_TEST("asientos_ocupados");
	// Caso 1: Sala con asientos ocupados
	int capacidad = 10;
	crea_sala(capacidad);
	for (int i = 1; i <= capacidad+1; i++) {
		reserva_asiento(i+1);
	}
	int resultado = asientos_ocupados();

	DebeSerCierto(resultado == capacidad);

	// Caso 2: Sala sin asientos ocupados
	for (int i = 0; i < capacidad; i++) {
		libera_asiento(i+1);
	}
	resultado = asientos_ocupados();
	DebeSerCierto(resultado == 0);
	elimina_sala();

	// Caso 3: Sala sin crear
	resultado = asientos_ocupados();
	DebeSerCierto(resultado == -1);

	FIN_TEST("asientos_ocupados");
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
	INICIO_TEST("estado_asiento");
	// Caso 1: Asiento libre
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = estado_asiento(1);
	DebeSerCierto(resultado == 0);

	// Caso 2: Asiento ocupado
	reserva_asiento(1);
	resultado = estado_asiento(1);
	DebeSerCierto(resultado > 0);

	// Caso 3: Asiento fuera del rango
	resultado = estado_asiento(capacidad + 1);
	DebeSerCierto(resultado == -1);
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = estado_asiento(1);
	DebeSerCierto(resultado == -1);

	FIN_TEST("estado_asiento");
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
	INICIO_TEST("reserva_asiento");
	// Caso 1: Asiento libre disponible
	int capacidad = 10;
	crea_sala(capacidad);
	int resultado = reserva_asiento(1);
	DebeSerCierto(resultado >= 0);

	// Caso 2: Asiento no disponible
	resultado = reserva_asiento(1);
	for (int i = 1; i<capacidad; i++){
		reserva_asiento(i);
	
	}
	resultado=reserva_asiento(1);
	DebeSerCierto(resultado == -1);
	elimina_sala();
	crea_sala(capacidad);
	// Caso 3: ID de persona no válido
	resultado = reserva_asiento(-1);
	DebeSerCierto(resultado == -1);
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = reserva_asiento(1);
	DebeSerCierto(resultado == -1);

	FIN_TEST("reserva_asiento");
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
	INICIO_TEST("libera_asiento");
	// Caso 1: Asiento ocupado
	int capacidad = 10;
	crea_sala(capacidad);
	reserva_asiento(1);
	int resultado = libera_asiento(1);
	DebeSerCierto(resultado == 1);

	// Caso 2: Asiento ya libre
	resultado = libera_asiento(1);
	DebeSerCierto(resultado == -1);

	// Caso 3: Asiento fuera del rango
	resultado = libera_asiento(capacidad + 1);
	DebeSerCierto(resultado == -1);
	elimina_sala();

	// Caso 4: Sala sin crear
	resultado = libera_asiento(1);
	DebeSerCierto(resultado == -1);

	FIN_TEST("libera_asiento");
}






void test_ReservaBasica()
{
	int mi_asiento;
	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500

	INICIO_TEST("Reserva básica");
	crea_sala(CAPACIDAD_CUYAS);
	DebeSerCierto(capacidad_sala()==CAPACIDAD_CUYAS);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	DebeSerCierto(estado_asiento(mi_asiento)>0);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	elimina_sala();
	FIN_TEST("Reserva básica");
}


void ejecuta_tests ()
{
	test_ReservaBasica();
	test_crea_sala();
	test_elimina_sala();
	test_capacidad_sala();
	test_asientos_libres();
	test_asientos_ocupados();
	test_estado_asiento();
	test_reserva_asiento();
	test_libera_asiento();
	// Añadir nuevos tests 
}

int main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
	return 0;
}
