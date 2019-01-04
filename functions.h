#ifndef FUNCIONES_H
#define FUNCIONES_H

/**
 * Devuelve un string totalmente en minusculas
 */
char *minusculas( const char * );

/**
 * Imprime en pantalla un menu, dado un titulo y un array de opciones
 * Recibe un string de titulo y un vector de opciones
 */
void impMenu( const char *, int, ... );

/*
	Abstraccion de funcionalidad de opciones exclusivas. Util para cuando se necesita una opcion rapido
	para determinar un flag de prendido/apagado. Esta funcion se encarga de una vez de la validacion de 
	la entrada del usuario
	Parametros:
		const char *planteamiento : Eleccion a ser mostrada al usuario
	Retorno: int : valor del flag escogido por el usuario
*/
int impSiNo( const char * );

/**
 * Limpia la pantalla e imprime el encabezado de la aplicacion
 */
void impCabezado();

/*
	Funcion de atajo para el mostrado con detalle de una lista cualquiera.
	Sirve tambien para tener consistencia en todos los prompt de detalle
*/
int detalle();

#endif