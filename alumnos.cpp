#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumnos.h"
#include "functions.h"
#include <locale.h>

/*
	La documentacion acerca de lo que hace cada funcion esta en alumnos.h
	Aqui se explica instruccion por instruccion lo que hace cada una
*/

Alumno *Al = NULL;


Fecha crearFecha() {
	// asumimos que la fecha es invalida inicialmente
	int esValida = 0;
	// fecha a devolver
	Fecha fecha;
	// mientras sea invalida la fecha, volvemos a llenar los datos (Posible optimizacion seria solamente pedir el dato erroneo)
	while( ! esValida ) {
		// solicitamos el dia (1-31)
		printf("\tDía: \n");
		scanf( "%hu", &(fecha.dia) );
		// solicitamos el mes (1-12)
		printf("\tMes: \n");
		scanf( "%hu", &(fecha.mes) );
		// solicitamos el año (mayor a 1970)
		printf("\tAño: \n");
		scanf( "%hu", &(fecha.ano) );

		/* 
			Validaciones. Si una falla, las demas tienen que fallar 
			Si bien se podria hacer en una instruccion, siento que asi es mas facil de leer, asi como mas ordenado
		*/
		esValida = fecha.ano > 1970;
		esValida = esValida && (fecha.mes > 0 && fecha.mes <= 12);
		esValida = esValida && (fecha.dia > 0 && fecha.dia <= 31);

		// si es invalida, hay que hacerselo saber al usuario
		if ( ! esValida )
			printf("Formato de fecha incorrecto. Por favor vuelva a ingresar los datos\n");
	}

	// regresamos
	return fecha;
}

void printAlumno(Alumno *A, int detalle) {
	if (!A) return; // solamente actuamos si el alumno no es NULL
	printf("Información del alumno: %s %s\n", A->nombre, A->apellido);
	printf("\tNombre completo: %s %s\n", A->nombre, A->apellido);
	printf("\tCédula: %i\n", A->cedula);
	if ( detalle ) {
		printf("\tFecha Nacimiento: %hhu/%hhu/%hhu\n", A->fechaNac.dia, A->fechaNac.mes, A->fechaNac.ano);
		printf("\tTeléfono: %s\n", A->telefono);
		printf("\tCorreo: %s\n", A->correo);
		printf("\tDirección: %s\n", A->direccion);
	}
}

void printListaAlumno(Alumno *A, int detalle) {
	// solamente actuamos si la lista no esta vacia
	if (!A) {
		printf("\tLista vacía\n");
		return; 
	}
	printf("----------------------------\n\n");
	// mostramos la informacion de este alumno como nos la planteen
	printAlumno(A, detalle);
	// si tenemos mas alumnos, llamamos recursivamente con el siguiente, caso contrario, cerramos la tablita y salimos de la pila
	if (A->prox) printListaAlumno(A->prox, detalle);
	else printf("----------------------------\n");
}

int cantidadAlumnos( Alumno *A ) {
	// si el alumno es nulo, regresamos 0, sino aumentamos uno a la cuenta
	return A ? cantidadAlumnos(A->prox) +1 : 0; 
}

void insertarAlumno(Alumno **P, Alumno *A) {
	// si no hay Cabeza, se asigna al A alumno y regresamos
	if (!*P) {
		*P = A;
		return;
	}

	// si el primer elemento de la cabeza cumple con las condiciones, reasignamos la cabeza y regresamos
	if ((*P)->cedula > A->cedula) {
		A->prox = *P;
		*P = A;
		return;
	}

	// empezamos a iterar
	Alumno *t = *P;
	while (t && t->prox) {
		if (t->prox->cedula > A->cedula) {
			// si encontramos uno mayor que la cedula, lo insertamos
			A->prox = t->prox;
			t->prox = A;
			return;
		} 
		else
			t = t->prox;
	}

	// si no hemos insertado hasta este punto, es el ultimo.
	t->prox = A;
}

Alumno *obtenerAlumnoPorCedula(Alumno *A, int cedula) {
	// Como los alumnos deben estar insertados por cedula (menor-mayor), podemos salir si no hay elemento actual o si la cédula actual es mayor a la cédula a buscar
	if ( ( ! A ) || A->cedula > cedula ) return NULL;

	// si no regresamos null, entonces comparemos la cedula. Si hay coincidencia regresamos el alumno, caso contrario vamos con el siguiente
	return A->cedula == cedula ? A : obtenerAlumnoPorCedula( A->prox, cedula );
}


Alumno *obtenerAlumnosPorNombre(Alumno *P, char *nombre ) {
	// declaramos la lista que devolveremos al final
	Alumno *coincidencias = NULL, *A = P;
	nombre = minusculas( nombre );
	// iteramos sobre la lista de alumnos dada
	while ( A ) {
		// comparamos el nombre en minúsculas del alumno actual con el nombre en minúsculas a buscar
		// si está, lo insertamos en la lista de coincidencias
		if ( strstr( minusculas( A->nombre ), nombre ) ) insertarAlumno( &coincidencias, extraerAlumno(P, A->cedula) );
		// vamos al siguiente alumno de la lista
		A = A->prox;
	}

	// regresamos lo que sea que hayamos encontrado
	return coincidencias;
}

Alumno *crearAlumno(void) {
	// declaramos el nuevo alumno a insertar, y un auxiliar para saber si el alumno existe
	Alumno *A = new Alumno, *existe = NULL;

	miflush(); // limpiamos el buffer de entrada

	// solicitamos el nombre del alumno
	printf( "Nombre del alumno: " );
	gets_s( A->nombre );

	// solicitamos el apellido del alumno
	printf( "Apellido del alumno: " );
	gets_s( A->apellido );

	// solicitamos la cedula del alumno hasta que esta sea una cedula unica (No este en el sistema)
	do {
		printf( "Cédula de identidad del alumno: " );
		scanf( "%i", &(A->cedula) );
		existe = obtenerAlumnoPorCedula( Al, A->cedula );
		if ( existe )
			printf("El alumno con la cédula \"%i\" ya existe, pertence a %s\n Por favor ingrese otro número de cédula\n", existe->cedula, existe->nombre);
	} while( existe );

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// solicitamos la direccion del alumno
	printf( "Dirección: " );
	gets_s( A->direccion );

	// solicitamos el numero telefonico del alumno
	printf( "Teléfono: " );
	gets_s( A->telefono );

	// solicitamos los datos de la fecha de nacimiento del alumno
	printf( "Fecha Nacimiento: " );
	A->fechaNac = crearFecha();

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// solicitamos el correo electronico del alumno
	printf( "Correo Electrónico: " );
	gets_s( A->correo );

	// inicializamos el proximo elemento de este alumno como nulo
	A->prox = NULL;

	// devolvemos
	return A;
}

void modificarAlumno(Alumno **P) {
	// nada mas actuamos si no tenemos un puntero a nulo
	if (*P) {
		int opt = -1, cedula = -1;
		Alumno *existe = NULL;

		// salimos cuando la opcion sea 0
		do {
			// mostramos el encabezado
			impCabezado();
			printAlumno(*P);
			impMenu(
				"Estas son las opciones disponibles para los alumnos.\nMarque la opción de acuerdo a la operación que desea realizar",
				6,
				"Editar número de cédula",
				"Editar el nombre del alumno",
				"Editar la dirección del alumno",
				"Editar número de teléfono",
				"Editar fecha de nacimiento",
				"Editar correo electrónico"
			);
			scanf("%i", &opt);
			miflush();
			switch ( opt ) {
				case 0: break;
				case 1:
					do {
						printf("Introduzca el nuevo número de cédula para %s. Actual: %d: ", (*P)->nombre, (*P)->cedula);
						scanf("%i", &(cedula));
						if (existe = obtenerAlumnoPorCedula(Al, cedula))
							printf("Error al cambiar el numero de cédula: Un alumno con esa cédula ya existe en el sistema: %s %s\n", existe->nombre, existe->apellido);
					} while ( existe );
					printf("Cédula cambiada con éxito\n");
					system("pause");
					break;
				case 2:
					printf("Introduzca un nuevo nombre para %s: ", (*P)->nombre);
					gets_s( (*P)->nombre );
					printf("Introduzca un nuevo apellido para %s. Actual: %s: ", (*P)->nombre, (*P)->apellido);
					gets_s( (*P)->apellido );
					printf("Nombres y apellido cambiados con éxito\n");
					system("pause");
					break;
				case 3:
					printf("Introduzca una nueva dirección para %s. Actual: %s: ", (*P)->nombre, (*P)->direccion);
					gets_s( (*P)->direccion );
					printf("Dirección cambiada con éxito\n");
					system("pause");
					break;
				case 4:
					printf("Introduzca un nuevo número de teléfono para %s. Actual: %s: ", (*P)->nombre, (*P)->telefono);
					gets_s( (*P)->telefono );
					printf("Número de teléfono cambiado con éxito\n");
					system("pause");
					break;
				case 5:
					printf("Introduzca una nueva fecha de nacimiento para %s. Actual: %hi/%hi/%hi: ", (*P)->nombre, (*P)->fechaNac.ano, (*P)->fechaNac.mes, (*P)->fechaNac.dia);
					(*P)->fechaNac = crearFecha();
					printf("Fecha de nacimiento cambiada con éxito\n");
					system("pause");
					break;
				case 6:
					printf("Introduzca un nuevo correo electrónico para %s. Actual: %s: ", (*P)->nombre, (*P)->correo);
					gets_s( (*P)->correo );
					printf("Correo electrónico cambiado con éxito\n");
					system("pause");
					break;
				default: 
					printf("Opción no reconocida. Vuelva a intentar\n");
			}
		} while ( opt );
	}
}

void elimAlumno(Alumno **P, int cedula) {
	if (! *P) return; // regresamos si el listado esta vacio
	if ((*P)->cedula > cedula) return; // como estan ordenados, podemos salir si la cedula a buscar es mas pequeña que la primera
	Alumno *del; // declaramos un auxiliar de eliminacion
	if ((*P)->cedula == cedula) {
		// si la cedula coincide con el primer elemento, tenemos que eliminar la cabeza
		del = *P;
		*P = (*P)->prox;
		if (impSiNo("Seguro que desea eliminar este alumno?"))
			delete del;
		return;
	}

	// ayudante para iterar
	Alumno  *alumno = *P;
	// iteramos hasta el ultimo elemento
	while ( alumno && alumno->prox ) {
		// podemos salir temprano si la cedula del proximo es mayor que la cedula a buscar
		if (alumno->prox->cedula > cedula) break;

		if (alumno->prox->cedula == cedula) {
			// si la cedula del proximo en la lista coincide, entonces tenemos que eliminarlo
			del = alumno->prox;
			alumno->prox = del->prox;
			if (impSiNo("Seguro que desea eliminar este alumno?"))
				delete del;
			return;
		}

		alumno = alumno->prox;
	}
}

void consultarAlumno(Alumno **P, int cedula) {
	Alumno *alumno = obtenerAlumnoPorCedula(*P, cedula);
	if (alumno)
		printAlumno(alumno);
	else 
		printf( "No se encontró a ningún alumno con la cédula '%i'\n", cedula );
}

void vaciarListaAlumnos(Alumno **P) {
	if (*P) {
		vaciarListaAlumnos(&((*P)->prox));
		delete (*P);
	}
}

void extraerAlumnosDesdeArchivo(Alumno **P, FILE *f) {
	// reservamos memoria
	Alumno *A = new Alumno;
	// leemos registro
	fread(A, sizeof Alumno, 1, f);
	// comprobamos que no sea fin de archivo
	if ( ! feof(f) ) {
		// volvemos el siguiente nulo
		A->prox = NULL;
		// insertamos
		insertarAlumno(P, A);
		// llamamos recursivamente
		extraerAlumnosDesdeArchivo(P, f);
	}
	else delete A; // si llegamos a fin de archivo, liberemos la memoria (no lo hacemos siempre porque la memoria declarada aqui fue insertada
}

Alumno *extraerAlumno(Alumno *A, int cedula) {
	// Alumno a extraer de la lista
	Alumno *objetivo = obtenerAlumnoPorCedula(A, cedula),
		// Alumno a devolver
		   *extraido = new Alumno;

	// si no obtuvimos nada, limpiamos la memoria reservada y regresamos nulo
	if ( ! objetivo ) {
		delete extraido;
		return NULL;
	}

	// copiamos todos los campos, y nulificamos el puntero a proximo
	strcpy_s(extraido->nombre, sizeof(objetivo->nombre), objetivo->nombre);
	strcpy_s(extraido->apellido, sizeof(objetivo->apellido), objetivo->apellido);
	strcpy_s(extraido->direccion, sizeof(objetivo->direccion), objetivo->direccion);
	strcpy_s(extraido->telefono, sizeof(objetivo->telefono), objetivo->telefono);
	strcpy_s(extraido->correo, sizeof(objetivo->correo), objetivo->correo);
	extraido->prox = NULL;
	extraido->cedula = objetivo->cedula;
	extraido->fechaNac = objetivo->fechaNac;

	// regresamos
	return extraido;
}