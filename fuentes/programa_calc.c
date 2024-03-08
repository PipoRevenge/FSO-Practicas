//programa para usar la librería calc
#include <stdio.h>
#include "../cabeceras/calc.h"

void main()
{
	printf("2+3= %d\n", suma(2,3));
	printf("2-3= %d\n", resta(2,3));
	printf("2*3= %d\n", producto(2,3));
	printf("2/3= %f\n", division((float)2,(float)3));
}


