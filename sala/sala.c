//Código de la  sala

#include <stdio.h>  //para printf / fprintf
#include <stdlib.h> //para exit
#include <getopt.h> //para getopt
#include <string.h> //para strlen


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


int crea_sala(int capacidad){
	
	//Controlamos que el parámetro capacidad sea mayor que 0 para poder crear la sala
	if (capacidad > 0){
	
	     //Asignación del espacio en memoria y control de errores
	     ptr = (int*)malloc(capacidad*sizeof(int));
	     if(ptr != NULL){
	         capacidad_main = capacidad;
	         asientos_lib = capacidad;
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
	if (ptr == NULL){
	     return -1;
	}else{
	     free(ptr);
	     return 0;
	}
	
}


int capacidad_sala(){
	return capacidad_main;
}

int asientos_libres(){
	return asientos_lib;
}

int asientos_ocupados(){
	return asientos_ocu;
}


int reserva_asiento(int id_persona){
	
	//Controlamos que hay asientos libres
	if (asientos_ocu != capacidad_main){
	
		//Control de que id es positivo
		if(id_persona < 0){printf("Introduzca un id válido");return -1;}
		
		//**** SOBRA
		//Control de que id no está repetido
	         for (int i = 0; i < capacidad_main;i++){
	              if (*(ptr+i) == id_persona) {printf("Id repetido, pruebe introduciendo otro");return -1;}
	         }	         	    	 
	         	         
	         //Recorremos los asientos y reservamos el primero que esté libre
	         for (int i = 0; i < capacidad_main;i++){
	              if (*(ptr+i) == -1) {
	                  *(ptr+i) = id_persona;
	                  asientos_lib--;
           	         asientos_ocu++;
	                  return i+1;
	              }
	         }
	         	         
	}else{
		printf("Error, no hay asientos libres");
		return -1;
	}
}

int libera_asiento(int id_asiento){
	
	//*******
	//Si el asiento está fuera del rango de la sala (1--capacidad), da error
	if (id_asiento <= capacidad_main && id_asiento > 0){
		
		//Si el asiento ya estaba libre, da error
		if (*(ptr+id_asiento-1) == -1){
			printf("Error, no puede liberar un asiento que está libre");
			return -1;
		}else{	
			int id_del_asiento = *(ptr+id_asiento-1);
			*(ptr+id_asiento-1) = -1;
			asientos_lib += 1;
			asientos_ocu -= 1;
			return id_del_asiento;
		}	
	}else{
		printf("Error, el asiento no puede exceder la capacidad de la sala");
		return -1;
	}
	
}

int estado_asiento(int id_asiento){

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




