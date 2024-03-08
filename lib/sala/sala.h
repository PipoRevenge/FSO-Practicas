//Cabecera sala.h

/*
   Función: Crea la sala y establece todos los asientos libres 
   Parámetros: La capacidad que debe soportar la sala
   Return: La capacidad de la sala si ha ido todo bien. -1 si hay algún error.
*/
	int crea_sala(int capacidad);


/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/
	int elimina_sala();


/*
   Función: Reserva asiento en la sala
   Parámetros: Id para
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/
	int reserva_asiento(int id_persona);


/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/

	int libera_asiento(int id_asiento);

	
/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/

	int estado_asiento(int id_asiento);


/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/

	int asientos_libres();
	
/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/
	
	int asientos_ocupados();
	

/*
   Función: Elimina la sala
   Parámetros: No
   Return: 0 si ha ido todo bien. -1 si hay algún error.
*/

	int capacidad_sala();




