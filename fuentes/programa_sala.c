// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//

#include <assert.h>
#include <stdio.h>


#include "../cabeceras/sala.h"

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


void test_ReservaBasica()
{
	int mi_asiento;
	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500
	

	INICIO_TEST("Reserva básica");
	
	//Creamos la sala con capacidad 500
	crea_sala(CAPACIDAD_CUYAS);
	
	/*
	  Comprobamos si el método capacidad() devuelve el valor que se pasó por 
	  parámetro al crear la sala.
	*/ 
	DebeSerCierto(capacidad()==CAPACIDAD_CUYAS);
	
	
	/*
	  Comprobamos si se reserva correctamente un asiento pasandole el ID_1 = 1500,
	  si se devuelve un número mayor que -1 entonces se reservó correctamente.
	*/
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	
	
	/*
	  Comprobamos si la suma de los asientos libres + los asientos ocupados da 
	  como resultado la capacidad de la sala.
	*/
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	
	/*
	  Comprobamos si "mi_asiento" está ocupado, debe devolver el número 1500,
	  ya que mi_asiento guardó el valor del asiento reservado por ID_1 en
	  mi_asiento=reserva_asiento(ID_1).
	*/
	DebeSerCierto(estado_asiento(499)>0);
	
	
	/*
	  Comprobamos si se libera el asiento correctamente, esto debe devolver el 
	  identificador del asiento liberado
	*/
	DebeSerCierto(libera_asiento(499)==ID_1);
	
	
	/*
	  Volvemos a comprobar si los asientos libres + los asientos ocupados dan
	  la capacidad de la sala
	*/
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	
	
	
	
	elimina_sala();
	FIN_TEST("Reserva básica");
}

void test_PabloMedina1()
{
	int mi_asiento;
	#define CAPACIDAD_SALA 12
	#define ID3 10
	#define ID2 20
	#define ID1 30
	#define ID_2 1
	#define ID_3 2
	#define ID_4 4
	#define ID_5 50
	#define ID_6 60
	#define ID_7 70
	#define ID_8 3
	#define ID_9 16
	#define ID_10 9

	INICIO_TEST("Test Pablo Medina 1");
	
	//Creamos la sala con capacidad para 6 personas
	crea_sala(CAPACIDAD_SALA);
         
	//Realizamos las reservas
	reserva_asiento(ID3);
	reserva_asiento(ID2);
	reserva_asiento(ID1);
	reserva_asiento(ID_2);
	reserva_asiento(ID_3); 
	reserva_asiento(ID_4);
	reserva_asiento(ID_5);
	reserva_asiento(ID_6);
	reserva_asiento(ID_7); 
	reserva_asiento(ID_8);
	reserva_asiento(ID_9);
	reserva_asiento(ID_10); 
	
	/*
	  1º Prueba: Se comprueba si al intentar reservar un asiento con la sala
	             llena devuelve un -1 lo que indica que no se ha podido hacer
	             la reserva
	*/
	DebeSerCierto(reserva_asiento(ID_7) == -1);
	
	/*
	  2º Prueba: Se testea si al comprobar el estado de un asiento que 
	             sobrepasa la capacidad de la sala (Que no existe) devuelve -1,
	             es decir, que se ha producido un error.
	*/
	DebeSerCierto(estado_asiento(14) == -1);
	
	/*
	  3º Prueba: Se testea si al intentar liberar un asiento que 
	             sobrepasa la capacidad de la sala (Que no existe) devuelve -1,
	             es decir, que se ha producido un error.
	*/
	DebeSerCierto(libera_asiento(16) == -1);
	
	/*
	  4º Prueba: Al haber reservado todos los asientos, comprobamos que el 
	             número de los asientos ocupados es igual a la capacidad de 
	             la sala.
	*/
	DebeSerCierto(asientos_ocupados() == capacidad());
	
	/*
	  5º Prueba: Al haber reservado todos los asientos, comprobamos que el 
	             número de asientos libres da 0.
	*/
	DebeSerCierto(asientos_libres() == 0);
	/*
	  En la ficha de la práctica dice que hay que realizar un test para cada
	  función de la librería pero para crear sala y eliminar sala no se me 
	  ocurre ninguna manera de hacerlo.
	*/
	
	elimina_sala();
	FIN_TEST("Test Pablo Medina 1");

}

void test_PabloMedina2()
{


	INICIO_TEST("Test 2");
	int mi_asiento;
	#define CAPACIDAD_SALA 12
	#define ID3 10
	#define ID2 20
	#define ID1 30
	#define ID_2 1
	#define ID_3 2
	#define ID_4 4
	#define ID_5 50
	#define ID_6 60
	#define ID_7 70
	#define ID_8 3
	#define ID_9 16
	#define ID_10 9

	INICIO_TEST("Test Pablo Medina");
	
	//Creamos la sala con capacidad para 6 personas
	crea_sala(CAPACIDAD_SALA);
         
	//Realizamos las reservas
	reserva_asiento(ID3);
	reserva_asiento(ID2);
	reserva_asiento(ID1);
	reserva_asiento(ID_2);
	reserva_asiento(ID_3); 
	reserva_asiento(ID_4);
	reserva_asiento(ID_5);
	reserva_asiento(ID_6);
	reserva_asiento(ID_7); 
	
	
	
	int a[] = {2,3,6};
	int* p = a;
	
	
	/*
	  1º Prueba: Se guarda el estado de la sala actual en el fichero siguiente
	*/
	      guarda_estado_sala("pruebaguardado.txt");
	      
	/*
	  2º Prueba: Se guarda el estado de la sala actual en el fichero siguiente
	*/
	      
	      guarda_estado_parcial_sala("pruebaguardaaa.txt",3,p);
	      //Comprobar archivo
	
	/*
	  3º Prueba: Se guarda el estado de la sala actual en el fichero siguiente
	*/
	      recupera_estado_sala("pruebaguardado.txt");
	      
	      DebeSerCierto(asientos_ocupados() == 9);
	
	/*
	  4º Prueba: Se guarda el estado de la sala actual en el fichero siguiente
	*/
	      recupera_estado_parcial_sala("pruebaguardaaa.txt",3,p);
	      
	      DebeSerCierto(asientos_ocupados() == 2);
	      
	      
	elimina_sala();
	FIN_TEST("Test Pablo Medina 2");
	
	
}

void ejecuta_tests ()
{	 
	
	test_ReservaBasica();
	test_PabloMedina1();
	test_PabloMedina2();
}

void main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
}

