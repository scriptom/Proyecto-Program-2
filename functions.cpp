#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#include <wchar.h>
#include "functions.h"
/************************/
/* DECLARACIONES VARIAS */
/************************/



char *minusculas(const char *str) {
	// creamos un nuevo string para no alterar el parametro.
	char *min = ( char * )malloc( strlen( str ) );
	// limpiamos la basura de la que se llena min con el malloc
	memset( min, '\0', sizeof( min ) );
	// copiamos los contenidos de str en min
	strcpy( min, str );
	// iteramos sobre min
	for ( int i = 0; min[i]; i++ )
		min[i] = tolower( min[i] ); // por cada letra de min, reasiganle su equivalente minuscula

	return min;
}

void impMenu(const char *titulo, int optlen, ...) {
	// mostramos el texto de ayuda del menu, apodado titulo
	printf("%s\n\n", titulo);
	// Variable que tomara el lugar de cada una de nuestras opciones
	char *opt;
	// Listado de las opciones pasadas a la funcion
	va_list opts;
	// inicializamos argumentos variables
	va_start(opts, optlen);
	// iteramos sobre cada opcion cada, e imprimimos en pantalla el numero que representa, y su texto
	for (int i = 0; i < optlen; i++) {
		opt = va_arg(opts, char*);
		printf("\t%d. %s\n", i + 1, opt);
	}
	// siempre damos la opcion de salir
	printf("\n0. Salir\n");
	// limpiamos la memoria
	va_end(opts);
}

int impSiNo(const char *planteamiento) {
	TILDES;
	printf("\n%s (S/N) \n", planteamiento);
	char o = -1;
	do {
		scanf("%c", &o);
		o = tolower(o);
		if (o != 's' && o != 'n')
			printf("Opción no reconocida");
	} while (o != 's' && o != 'n');
	return o == 's';
}

void impCabezado() {
	system("cls");
	printf("*********************************\n");
	printf("* SISTEMA DE GESTION DE ALUMNOS *\n");
	printf("*********************************\n");
}

int detalle() {	
	return impSiNo("Mostrar con detalle?");
}