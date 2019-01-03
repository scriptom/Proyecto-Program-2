#include "alumnos.h"
#include "materias.h"
#include "cursos.h"
#include "functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

/* 
	Aqui se declaran las funciones que se usan como ayudantes para los menus de navegacion de todo el programa
	la definicion de las mismas se encuentra debajo del main. Abajo se muestra un mapa de la navegacion
	de las opciones disponibles en el programa. Cuando un menu no tiene un nivel mas interno, quiere decir que 
	dicho menu tiene ya acciones especificas, y no tiene sino ya regreso a un nivel anterior

	Esquema de navegacion de menu:
	-Menu principal
	|- menuMantenimiento
	|	|- menuAlumnado
	|	|- menuMaterias
	|	|- menuDeCursos
	|- menuInscripciones
	|	|- menuInsConsultas

	Abajo se encuentra la declaracion de las funciones
*/

void menuMantenimiento(void);
	void menuAlumnado(void);
	void menuMaterias(void);
	void menuDeCursos(void);
void menuInscripciones(void);
	void menuInsConsultas(void);
void menuParaConsultas(void);


/*
	Carga la data guardada en archivos de extension (.alp2), e inicializa de una vez los indices del sistema
*/
void cargarDeArchivos(void);

/*
	Guarda la data manejada a lo largo de la ejecucion del programa en archivos (.alp2), para luego cargarlos
	en la proxima ejecucion
*/
void guardarEnArchivos(void);

void main()
{
	TILDES;
	int opt = -1;
	cargarDeArchivos();
	do {
		impCabezado();
		impMenu("Qué desea hacer?", 3, "Mantenimiento", "Inscripciones", "Consultas");

		scanf("%i", &opt);
		switch ( opt ) {
			case 0: break;
			case 1: menuMantenimiento(); break;
			case 2: menuInscripciones(); break;
			case 3: menuParaConsultas(); break;
			default: printf("Opción \"%i\" no reconocida. Marque una opción valida\n", opt); system("pause");
		}
	} while ( opt );
	miflush();
	if ( impSiNo( "Desea guardar lo modificado?" ) )
		guardarEnArchivos();
	printf("Hasta luego!\n");
	system("pause");

	vaciarListaAlumnos(&Al);
	vaciarListaMaterias(&Mat);
	vaciarListaCursos(&Cur);
}

void menuMantenimiento() {
	int opt = -1;
	do {
		impCabezado();
		impMenu("Qué desea gestionar?", 3, "Alumnos", "Materias", "Cursos");

		scanf("%i", &opt);
		miflush();
		switch (opt) {
		case 0: break;
		case 1: menuAlumnado(); break;
		case 2: menuMaterias(); break;
		case 3: menuDeCursos(); break;
		default: printf("Opción \"%i\" no reconocida. Marque una opción válida\n"); system("pause");
		}
	} while (opt);
}

void menuAlumnado(void) {
	int opt = -1, cedula = -1, cantidad = -1;
	Alumno *nuevo = NULL, *res = NULL;
	char nombre[15] = "\0";
	do {
		// mostramos el encabezado
		impCabezado();
		// mostramos las opciones
		impMenu(
			"Estas son las opciones disponibles para los alumnos.\nMarque la opción de acuerdo a la operación que desea realizar", 
			4,
			"Agregar un alumno nuevo",
			"Modificar los datos de un alumno (por cédula)",
			"Eliminar un alumno de la lista (por cédula)",
			"Mostrar lista de Alumnos"
		);
		
		scanf("%i", &opt);
		switch ( opt ) {
			case 0: break; // si es 0, salimos del switch y ya
			case 1:
				// creamos un nuevo alumno y lo insertamos
				nuevo = crearAlumno();
				insertarAlumno(&Al, nuevo);
				system("pause");
				break;
			case 2:
				// solicitamos el numero de cedula 
				printf("Por favor inserte el número de cédula: ");
				scanf("%i",&cedula);
				// (tal vez) obtenemos el alumno en cuestion
				res = obtenerAlumnoPorCedula(Al, cedula);
				if (res) {
					// en caso de que lo tengamos, lo sometemos a edicion
					modificarAlumno(&res);
					if (res->cedula != cedula) {
						// Si la cedula cambio, entonces lo reinsertamos en la lista, porque el orden pudo ser alterado
						elimAlumno(&Al, res->cedula);
						insertarAlumno(&Al, res);
					}
				}
				else printf("El alumno no existe\n");
				system("pause");
				break;
			case 3:
				// solicitamos el numero de cedula a eliminar
				printf("Introduzca el número de cédula a buscar: ");
				scanf("%i", &cedula);
				elimAlumno(&Al, cedula);
				system("pause");
				break;
			case 4:
				miflush();
				printListaAlumno(Al, detalle());
				system("pause");
				break;
			default: printf("Opción \"%i\" no reconocida. Marque una opción válida\n"); 
		}
	} while ( opt );
}	

void menuMaterias(void) {
	/* Esta funcion actua de manera muy similar a menuAlumnados. Ver la documentacion de esa funcion para una explicacion de lo que pasa */
	int opt = -1, codigo = -1;
	Materia *nuevo = NULL, *res = NULL;
	do {
		impCabezado();
		impMenu(
			"Estas son las opciones disponibles para las materias.\nMarque la opción de acuerdo a la operación que desea realizar",
			4,
			"Agregar Materia",
			"Modificar Materia",
			"Eliminar Materia",
			"Mostrar lista de Materias"
		);
		
		scanf( "%i", &opt );
		miflush();
		switch ( opt ) {
			case 0: break;
			case 1:
				nuevo = crearMateria();
				insertarMateria(&Mat, nuevo);
				system("pause");
				break;
			case 2:
				printf("Inserte el código de la materia que desea modificar: ");
				scanf("%i", &codigo);
				res = obtenerMateriaPorCodigo(Mat, codigo);
				if (res) modificarMateria(&res);
				else printf("No se encontró ninguna materia con el código \"%i\"\n", codigo);
				system("pause");
				break;
			case 3:
				printf("Inserte el código de la materia a eliminar: ");
				scanf("%i", &codigo);
				elimMateria(&Mat, codigo);
				system("pause");
				break;
			case 4:
				printf("\t\tLista completa de materias\n");
				printListaMateria(Mat, detalle());
				system("pause");
				break;
			default: printf("Opción \"%i\" no reconocida. Marque una opción válida\n", opt); 
		}
	} while ( opt );
}

void menuDeCursos(void) {
	/* Esta funcion actua de manera muy similar a menuAlumnados. Ver la documentacion de esa funcion para una explicacion de lo que pasa */
	int opt = -1, codigo = -1;
	Curso *nuevo = NULL, *res = NULL;
	do {
		impCabezado();
		impMenu(
			"Estas son las opciones disponibles para las Cursos.\nMarque la opción de acuerdo a la operación que desea realizar",
			4,
			"Agregar Curso",
			"Modificar Curso",
			"Eliminar Curso",
			"Mostrar lista de Cursos"
		);

		scanf("%i", &opt);
		switch (opt) {
		case 0: break;
		case 1:
			nuevo = crearCurso();
			if ( nuevo ) 
				insertarCurso(&Cur, nuevo);
			break;
		case 2:
			printf("Inserte el código del Curso que desea modificar: ");
			scanf("%i", &codigo);
			res = obtenerCursoPorCodigo(Cur, codigo);
			if (res) modificarCurso(&res);
			else {
				printf("No se encontró ningún Curso con el código \"%i\"\n", codigo);
				system("pause");
			}
			break;
		case 3:
			printf("Inserte el código del Curso a eliminar: ");
			scanf("%i", &codigo);
			elimCurso(&Cur, codigo);
			break;
		case 4:
			printf("Lista completa de Cursos");
			printListaCurso(Cur, detalle());
			system("pause");
			break;
		default: printf("Opción \"%i\" no reconocida. Marque una opción válida\n");
		}
	} while (opt);
}

void menuInscripciones(void) {
	// Opcion escogida en un menu
	int opt = -1;
	// Termino de busqueda
	char termino[20];

	do {
		impCabezado();
		impMenu(
			"Opciones disponibles de inscripción",
			7,
			"Consulta de claves (Alumno, Curso)",
			"Inscripción de un alumno en un curso",
			"Inscripción de varios alumnos en un curso",
			"Modificar la nota de un alumno en un curso",
			"Eliminar alumno de un curso",
			"Eliminar un curso",
			"Mover un alumno de un curso"
		);
		scanf("%i", &opt);
		miflush();
		switch (opt) {
		case 0: break;
		case 1: menuInsConsultas(); break;
		default: printf("Opción no reconocida\n");
			break;
		}
	} while (opt);
}
void menuParaConsultas(void) {}

void cargarDeArchivos() {
	// abrimos todos los handlers de los archivos. Los abrimos en modo anexo-lectura-binario par aque se creen si no existen
	FILE *falumno  = fopen("alumnos.alp2", "ab+"),
		 *fmateria = fopen("materias.alp2", "ab+"),
		 *fcurso   = fopen("cursos.alp2", "ab+");

	extraerAlumnosDesdeArchivo(&Al, falumno);
	extraerMateriasDesdeArchivo(&Mat, fmateria);
	extraerCursosDesdeArchivo(&Cur, fcurso);

	// cerramos los handlers
	fclose(falumno);
	fclose(fmateria);
	fclose(fcurso);

}

void guardarEnArchivos() {
	// inicializamos los handlers de archivos
	FILE *falumno = fopen("alumnos.alp2", "wb"),
		 *fmateria = fopen("materias.alp2", "wb"),
		 *fcurso = fopen("cursos.alp2", "wb");

	// asignamos los punteros a las cabezas
	Alumno *A = Al;
	Materia *M = Mat;
	Curso *C = Cur;

	// si no tenemos una lista global vacia, vamos a iterar sobre ella e insertamos
	if (A)
		for ( ; A; A = A->prox )
			fwrite(A, sizeof(Alumno), 1, falumno);
	if (M)
		for ( ; M; M = M->prox )
			fwrite(M, sizeof(Materia), 1, fmateria);
	if (C)
		for ( ; C; C = C->prox )
			fwrite(C, sizeof(Curso), 1, fcurso);

	// cerramos los handlers de archivo
	fclose(falumno);
	fclose(fmateria);
	fclose(fcurso);
}

void menuInsConsultas(void) {
	// Opcion del usuario
	int opt = -1;
	// Termino de busqueda
	char termino[20];
	// Lista de resultados de alumnos
	Alumno *resAlumno = NULL;
	// Lista de resultados de Cursos
	Curso *resCurso = NULL;
	do {
		impCabezado();
		impMenu(
			"Seleccione categoría de búsqueda",
			2,
			"Alumnos por nombre",
			"Cursos por nombre de materia"
		);
		scanf("%i", &opt);
		miflush();
		if (opt < 0 || opt > 2) printf("Opción no reconocida\n");
		else if (opt) {
			printf("Introduzca término de búsqueda: ");
			gets_s(termino);
			if (1 == opt) {
				resAlumno = obtenerAlumnosPorNombre(Al, termino);
				printListaAlumno(resAlumno, detalle());
			}
			else {
				BuscarCursos(termino);
			}
			system("pause");
		}
	} while (opt);

	// liberamos la memoria de las listas de resultados
	if (resAlumno)
		vaciarListaAlumnos(&resAlumno);
	if (resCurso)
		vaciarListaCursos(&resCurso);
}

/* CODIGO A SER USADO EN UN FUTURO
-------------- BUSQUEDA POR NOMBRE -----------------------------
// solicitamos un string para buscar
printf("\nPor favor inserte el nombre a buscar: ");
scanf(" %s", nombre);
// armamos una lista con los alumnos encontrados cuyo nombre contenga el string dado
Alumno *coin = obtenerAlumnosPorNombre(Al, nombre);
// en caso de que la lista tenga elementos, mostramos el detalle de cada uno
if ( coin ) {
	// calculamos la cantidad de alumnos en la lista de coincidencias
	int cantidad = cantidadAlumnos( coin );
	printf("\nResultados para la busqueda de \"%s\"\nSe encontraron %i alumnos:\n", nombre, cantidad);
	// mostramos el detalle de cada uno
	Alumno *c = coin;
	while ( c ) {
		printf("\n----------------------------\n");
		printAlumno( c );
		if ( ! c->prox ) printf("\n----------------------------\n");
		c = c->prox;
	}
}
------------------------- DATOS DE UN ALUMNO -------------------------
// solicitamos un numero de cedula
printf("\nPor favor ingrese el numero de cedula a buscar: ");
scanf("%i", &cedula);
// (tal vez) obtenemos un alumno con la cedula
res = obtenerAlumnoPorCedula(Al, cedula);
if ( res ) {
	// En caso de que se consiga el alumno, lo mostramos en pantalla
	printf("\nSe encontro un alumno con la cedula especificada:");
	printAlumno( res );
} else printf("\nNo se encontro ningun alumno con la cedula especificada");



*/