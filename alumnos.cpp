#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumnos.h"
#include "cursos.h"
#include "functions.h"

/*
	La documentacion acerca de lo que hace cada funcion esta en alumnos.h
	Aqui se explica instruccion por instruccion lo que hace cada una
*/

Alumno *Al = NULL;
AlumC *IndAlumno = NULL;

Fecha crearFecha() {
	// asumimos que la fecha es invalida inicialmente
	int esValida = 0;
	// fecha a devolver
	Fecha fecha;
	// mientras sea invalida la fecha, volvemos a llenar los datos (Posible optimizacion seria solamente pedir el dato erroneo)
	while( ! esValida ) {
		
		// solicitamos el dia (1-31)
		printf("\tDia: ");
		scanf( "%hu%*c", &(fecha.dia) );
		// solicitamos el mes (1-12)
		printf("\tMes: ");
		scanf( "%hu%*c", &(fecha.mes) );
		// solicitamos el año (mayor a 1970)
		printf("\tAño: ");
		scanf( "%hu%*c", &(fecha.ano) );

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
	printf("Informacion del alumno: %s %s\n", A->nombre, A->apellido);
	printf("\tNombre completo: %s %s\n", A->nombre, A->apellido);
	printf("\tCedula: %i\n", A->cedula);
	if ( detalle ) {
		printf("\tFecha Nacimiento: %hi/%hi/%hi\n", A->fechaNac.dia, A->fechaNac.mes, A->fechaNac.ano);
		printf("\tTelefono: %s\n", A->telefono);
		printf("\tCorreo: %s\n", A->correo);
		printf("\tDireccion: %s\n", A->direccion);
	}
}

void printListaAlumno(Alumno *A, int detalle) {
	
	// solamente actuamos si la lista no esta vacia
	if (!A) {
		printf("\tLista vacia\n");
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

	// insertamos el alumno en el indice de alumnos
	insertarAlumC( crearIndiceAl( A ) );

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
	// Como los alumnos deben estar insertados por cedula (menor-mayor), podemos salir si no hay elemento actual o si la cedula actual es mayor a la cedula a buscar
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
		// comparamos el nombre en minusculas del alumno actual con el nombre en minusculas a buscar
		// si esta, lo insertamos en la lista de coincidencias
		if ( strstr( minusculas( A->nombre ), nombre ) ) 
			insertarAlumno( &coincidencias, extraerAlumno(P, A->cedula) );
		// vamos al siguiente alumno de la lista
		A = A->prox;
	}

	// regresamos lo que sea que hayamos encontrado
	return coincidencias;
}

Alumno *crearAlumno(void) {
	// declaramos el nuevo alumno a insertar, y un auxiliar para saber si el alumno existe
	Alumno *A = new Alumno, *existe = NULL;

	// solicitamos el nombre del alumno
	printf( "Nombre del alumno: " );
	gets_s( A->nombre );

	// solicitamos el apellido del alumno
	printf( "Apellido del alumno: " );
	gets_s( A->apellido );

	// solicitamos la cedula del alumno hasta que esta sea una cedula unica (No este en el sistema)
	do {
		
		printf( "Cedula de identidad del alumno: " );
		scanf( "%i%*c", &(A->cedula) );
		existe = obtenerAlumnoPorCedula( Al, A->cedula );
		if ( existe )
			printf("El alumno con la cedula \"%i\" ya existe, pertence a %s\n Por favor ingrese otro numero de cedula\n", existe->cedula, existe->nombre);
	} while( existe );

	
	// solicitamos la direccion del alumno
	printf( "Direccion: " );
	gets_s( A->direccion );

	// solicitamos el numero telefonico del alumno
	printf( "Telefono: " );
	gets_s( A->telefono );

	// solicitamos los datos de la fecha de nacimiento del alumno
	printf( "Fecha Nacimiento: \n" );
	A->fechaNac = crearFecha();

	// solicitamos el correo electronico del alumno
	printf( "Correo Electronico: " );
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
				"Estas son las opciones disponibles para los alumnos.\nMarque la opcion de acuerdo a la operacion que desea realizar",
				6,
				"Editar numero de cedula",
				"Editar el nombre del alumno",
				"Editar la direccion del alumno",
				"Editar numero de telefono",
				"Editar fecha de nacimiento",
				"Editar correo electronico"
			);
			scanf("%i%*c", &opt);
			switch ( opt ) {
				case 0: break;
				case 1:
					do {
						printf("Introduzca el nuevo numero de cedula para %s. Actual: %d: ", (*P)->nombre, (*P)->cedula);
						scanf("%i%*c", &(cedula));
						if (existe = obtenerAlumnoPorCedula(Al, cedula))
							printf("Error al cambiar el numero de cedula: Un alumno con esa cedula ya existe en el sistema: %s %s\n", existe->nombre, existe->apellido);
					} while ( existe );
					printf("Cedula cambiada con exito\n");
					system("pause");
					break;
				case 2:
					printf("Introduzca un nuevo nombre para %s: ", (*P)->nombre);
					gets_s( (*P)->nombre );
					printf("Introduzca un nuevo apellido para %s. Actual: %s: ", (*P)->nombre, (*P)->apellido);
					gets_s( (*P)->apellido );
					printf("Nombres y apellido cambiados con exito\n");
					system("pause");
					break;
				case 3:
					printf("Introduzca una nueva direccion para %s. Actual: %s: ", (*P)->nombre, (*P)->direccion);
					gets_s( (*P)->direccion );
					printf("Direccion cambiada con exito\n");
					system("pause");
					break;
				case 4:
					printf("Introduzca un nuevo numero de telefono para %s. Actual: %s: ", (*P)->nombre, (*P)->telefono);
					gets_s( (*P)->telefono );
					printf("Numero de telefono cambiado con exito\n");
					system("pause");
					break;
				case 5:
					printf("Introduzca una nueva fecha de nacimiento para %s. Actual: %hi/%hi/%hi: ", (*P)->nombre, (*P)->fechaNac.ano, (*P)->fechaNac.mes, (*P)->fechaNac.dia);
					(*P)->fechaNac = crearFecha();
					printf("Fecha de nacimiento cambiada con exito\n");
					system("pause");
					break;
				case 6:
					printf("Introduzca un nuevo correo electronico para %s. Actual: %s: ", (*P)->nombre, (*P)->correo);
					gets_s( (*P)->correo );
					printf("Correo electronico cambiado con exito\n");
					system("pause");
					break;
				default: 
					printf("Opcion no reconocida. Vuelva a intentar\n");
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
		printf( "No se encontro a ningun alumno con la cedula '%i'\n", cedula );
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

int inscribirEnCurso(Alumno *A, Curso *C) {
	// copia del indice de cursos por año
	CursosY *cursos = IndCurso;
	// copia del indice de cursos dictados
	CursosS *indice = NULL;
	// copia de la lista de alumnos en un curso
	CursosA *alumnos = NULL;
	// (posiblemente) un puntero a los cursos de un año
	CursosY *cursosAno = NULL;

	if (C && A) {
		// obtenemos el puntero del año
		cursosAno = obtenerPunteroInd(C->ano);
		if (!cursosAno)
			// si no obtuvimos nada, lo creamos
			cursosAno = CrearCursosY(C->ano);
		
		// obtenemos el listado de cursos dictados
		indice = cursosAno->cursosDictados;

		// buscamos secuencialmente el indice cuyo curso tenga el codigo de nuestro curso
		// si no hay, nos quedamos con el ultimo indice (que por descarte contiene nuestro curso)
		while ( indice->prox ) {
			// buscamos el curso en cuestion entre los cursos dictados
			if (indice->curso &&
				indice->curso->codigo == C->codigo) break;
			indice = indice->prox;
		}

		return insertarCursosA(&(indice->alumnos), crearCursosA(A));
	}

	return 0;
}

CursosA *EstaInscrito(CursosA* Puntero,int Cedula){
	CursosA *T = Puntero;
	while (T){
		if (((T->alumno)->cedula) == Cedula)
			return T;
		else T= T->prox;
	}
	return NULL;
}

void BuscarAlumnos(){
	impCabezado();
	Alumno *Lista = Al;
	Alumno *P = NULL;
	char Nombre[15];
	printf("\nIntroduzca el nombre del alumno que desea buscar\n");
	gets_s(Nombre);
	P = obtenerAlumnosPorNombre(Lista,Nombre);
	if (Lista) printListaAlumno(P,detalle());
	else printf("No se han encontrado ningun alumno con ese nombre\n");
	system("Pause");
}

AlumC *crearIndiceAl(Alumno *A) {
	AlumC *indice = new AlumC;
	indice->prox = NULL;
	indice->materias = NULL;
	indice->alumno = A;

	return indice;
}

void insertarAlumC( AlumC *nodo ) {
	AlumC *global = IndAlumno;
	if ( ! IndAlumno ) IndAlumno = nodo;
	else {
		while ( global->prox )
			global = global->prox;
		
		global->prox = nodo;
	}
}

int BuscarAlumnoCursosA(CursosA *Cab,Alumno *AlumnoBuscado){
	CursosA *T = Cab;
	while (T){
		if (T->alumno == AlumnoBuscado) return 1;
		T->prox;
	}
	return 0;
}
