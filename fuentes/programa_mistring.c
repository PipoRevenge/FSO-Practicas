//programa para probar la librería mistring
#include <stdio.h>
#include "../cabeceras/mistring.h"

void escribe_cadena(char* cad)
{
	printf("La cadena <%s> y su longitud es %d\n", cad, mi_strlen(cad));
}



void main()
{
	char nombre[100];
	char nombre2[100];
	printf("Escribe un nombre:");
	scanf("%[^\n]s", nombre);
	escribe_cadena(nombre);
	mi_strcpy(nombre2, nombre);
	escribe_cadena(nombre2);
	//probamos 
	
	
	
	
}
