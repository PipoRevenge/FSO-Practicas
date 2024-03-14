#include <stdio.h>  //para printf / fprintf
#include <stdlib.h> //para exit
#include <getopt.h> //para getopt
#include <string.h> //para strlen
#include <stdbool.h>

/*Variables globales*/

//Puntero de memoria
int* ptr;
//Capacidad de la sala
int capacidad_main;
//Asientos ocupados
int asientos_ocu;
//Asientos libres
int asientos_lib;

// Control de salida de errores
void print_error(const char* msg){
	//Cambiar esto para que salga por canal
	//fprintf(stderr, "ERROR: %s\n", msg)
}
// Control de salida de advertencias
#define print_warning(msg) fprintf(stderr, "ADVERTENCIA: %s\n", msg)

//Funciones internas (No declarar en sala.h) 
//Comentar sala.h
bool estado_sala(){
	if(ptr != NULL){
		return true;
	}else {
		return false;
	}
}

int crea_sala(int capacidad){
	
	//Comprobamos que la sala no exista
	if(estado_sala()){
		print_error("La sala ya ha sido creada.");
		return -1;
	}
	
	//Controlamos que el parámetro capacidad sea mayor que 0 para poder crear la sala
	if (capacidad > 0){
	
	     //Asignación del espacio en memoria y control de errores
	     ptr = (int*)malloc(capacidad*sizeof(int));
	     if(ptr != NULL){
	         capacidad_main = capacidad;

	         asientos_ocu=0;
	         for (int i = 0; i<capacidad;i++){
		     *(ptr+i) = -1;
	         }
	         return capacidad;
	         
	     }else{
	         print_error("No se ha podido asignar correctamente un espacio en la memoria");
	         return -1;
	     }
	     
	}else{
	     print_error("No ha podido crearse la sala, ya que la capacidad no es válida");
	     return -1;
	}
	
} 


int elimina_sala(){
	
	//Si el puntero es NULL, no hay espacio de memoria que liberar
	//Problema si se elimina dos veces peta //////////////////////////////////////////////////////////////////
	if (!estado_sala()){
	     print_error("La sala no existe.");
	     return -1;
	}else{
	     free(ptr);
	     ptr = NULL; 
	     return 0;
	}
	
}


int capacidad_sala(){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	return capacidad_main;
}

int asientos_libres(){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	return capacidad_main - asientos_ocu;
}

int asientos_ocupados(){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	return asientos_ocu;
}

int estado_asiento(int id_asiento){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	//Si el asiento está fuera del rango de la sala (1--capacidad), da error
	if (id_asiento <= capacidad_main && id_asiento > 0){
		
		//Si el asiento está ocupado, devuelve el id del ocupante
		if (*(ptr+id_asiento-1) > -1){
			return *(ptr+id_asiento-1);
		
		//Si el asiento está libre se devuelve 0
		} else if(*(ptr+id_asiento-1) == -1){
			return 0;
			
		//Si ocurre algún tipo de error devueve -1
		} else{	
			print_error("Error desconocido.");
			return -1;
		}
		
		
	}else{	
		print_error("Introduzca un valor del 1 a la capacidad de la sala.");
		return -1;
	}
	
}

int reserva_asiento(int id_persona){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	//Controlamos que hay asientos libres
	if (asientos_libres()>0){
	
		//Control de que id es positivo
		if(id_persona < 0){
			
			print_error("Introduzca un id válido.");
			return -1;
		}
			         	    	 
	         	         
	         //Recorremos los asientos y reservamos el primero que esté libre
	         for (int i = 0; i < capacidad_main;i++){
	              if (*(ptr+i) == -1) {
	                  *(ptr+i) = id_persona;
			  asientos_ocu++;
	                  return i+1;
	              }
	         }
	         	         
	}else{
		print_error("Error, no hay asientos libres.");
		return -1;
	}
}


int libera_asiento(int id_asiento){
	if(!estado_sala()){
		print_error("La sala no ha sido creada.");
		return -1;
	}
	if(estado_asiento(id_asiento)>0){
		int id_del_asiento = *(ptr+id_asiento-1);
		*(ptr+id_asiento-1) = -1;
		asientos_ocu -= 1;
		return id_del_asiento;
		
	}else{
		print_error("El asiento no está ocupado.");
		return -1;
	}
	
}


