//Cabecera sala.h

/*
   Función: Crea una sala y establece todos los asientos libres 
   Parámetros: La capacidad que debe soportar la sala
   Return: La capacidad de la sala si ha ido todo bien. 
   	  Devuelve -1 si hay algún error.
*/
	int crea_sala(int capacidad);


/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien.
   	  Devuelve -1 si hay algún error.
*/
	int elimina_sala();


/*
   Función: Reserva el primer asiento libre disponible en la sala
   Parámetros: Id a almacenar en la posición de memoria (Debe ser entero positivo)
   Return: Devuelve el número de asiento si se ha podido reservar. 
      	  Devuelve -1 si hay algún error.
*/
	int reserva_asiento(int id_persona);


/*
   Función: Libera un asiento de la sala
   Parámetros: Id de asiento que se va a liberar (rango: 1-capacidad)
   Return: Si se ha podido liberar, devuelve el id de la persona que ocupaba el asiento. 
   	  Devuelve -1 si hay algún error.
*/

	int libera_asiento(int id_asiento);

	
/*
   Función: Muestra el estado de un asiento
   Parámetros: Id del asiento para comprobar si está ocupado o libre (rango: 1-capacidad)
   Return: Devuelve el id de la persona si el asiento está ocupado. 
   	  Devuelve 0 si está libre. 
   	  Devuelve -1 si hay algún error.
*/

	int estado_asiento(int id_asiento);


/*
   Función: Muestra el número de asientos libres
   Parámetros: No
   Return: Devuelve el número de asientos libres que hay en la sala.
           Devuelve -1 si hay algún error.
   
*/

	int asientos_libres();
	
/*
   Función: Muestra el número de asientos ocupados
   Parámetros: No
   Return: Devuelve el número de asientos ocupados que hay en la sala.
           Devuelve -1 si hay algún error.
   
*/
	
	int asientos_ocupados();
	

/*
   Función: Muestra la capacidad de la sala
   Parámetros: No
   Return: Devuelve la capacidad de la sala.
           Devuelve -1 si hay algún error.
*/

	int capacidad_sala();



