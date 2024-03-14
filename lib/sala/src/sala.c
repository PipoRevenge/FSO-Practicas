//Código de la  sala

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


//Cambiar los printf por los fprintf(stderr, "Mensaje de error")
//Controlar si la sala no se ha creado
//Funciones internas (No declarar en sala.h) 
//Comentar sala.h
bool estado_sala(){
	if(ptr != NULL){
		return true;
	}else if(ptr == NULL){
		return false;
	}
}

int crea_sala(int capacidad){
	
	//Coprobamos que existe
	if(estado_sala()){
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
	         printf("No se ha podido asignar correctamente un espacio en la memoria");
	         return -1;
	     }
	     
	}else{
	     printf("No ha podido crearse la sala, ya que la capacidad no es válida");
	     return -1;
	}
	
} 


int elimina_sala(){
	
	//Si el puntero es NULL, no hay espacio de memoria que liberar
	//Problema si se elimina dos veces peta //////////////////////////////////////////////////////////////////
	if (!estado_sala()){
	     return -1;
	}else{
	     free(ptr);
	     ptr = NULL; 
	     return 0;
	}
	
}


int capacidad_sala(){
	if(!estado_sala()){
		return -1;
	}
	return capacidad_main;
}

int asientos_libres(){
	if(!estado_sala()){
		return -1;
	}
	return capacidad_main - asientos_ocu;
}

int asientos_ocupados(){
	if(!estado_sala()){
		return -1;
	}
	return asientos_ocu;
}

int estado_asiento(int id_asiento){
	if(!estado_sala()){
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
			printf("Error");
			return -1;
		}
		
		
	}else{	
		printf("Introduzca un valor del 1 a %d (Capacidad)", capacidad_main);
		return -1;
	}
	
}






int reserva_asiento(int id_persona){
	if(!estado_sala()){
		return -1;
	}
	//Controlamos que hay asientos libres
	if (asientos_libres()>0){
	
		//Control de que id es positivo
		if(id_persona < 0){
			
			printf("Introduzca un id válido %d", id_persona);
			return -1;
		}
			         	    	 
	         	         
	         //Recorremos los asientos y reservamos el primero que esté libre
	         for (int i = 0; i < capacidad_main;i++){
	              if (*(ptr+i) == -1) {
	                  *(ptr+i) = id_persona;
			  asientos_ocu++;
			  //printf("\n reservando %d \n", asientos_ocu);	
	                  return i+1;
	              }
	         }
	         	         
	}else{
		printf("Error, no hay asientos libres");
		return -1;
	}
}


int libera_asiento(int id_asiento){
	if(!estado_sala()){
		return -1;
	}
	if(estado_asiento(id_asiento)>0){
		int id_del_asiento = *(ptr+id_asiento-1);
		*(ptr+id_asiento-1) = -1;
		asientos_ocu -= 1;
		return id_del_asiento;
		
	}else{
		//Aqui añadir los dos errores, ya estaba libre o otro error 
		return -1;
	}
	
	

}


//Buscar asiento
//



/*
Apuntes a tener en cuenta:
1. id_persona se puede repetir y debe ser positivo entero 
2. id_asiento es unico 


*/



