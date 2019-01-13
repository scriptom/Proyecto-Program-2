#include "functions.h"
#include "alumnos.h"
#include "materias.h"
#include "cursos.h"
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
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- menuConsultaAlumno
	|	|- menuMaterias
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- menuConsultaMateria
	|	|- menuDeCursos
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- (ejecucion directa)
	|	|	|- menuConsultaCurso
	|- menuInscripciones
	|	|- menuInsConsultas
	|   |- menuSingleInscripcion
	|   |- menuMultiInscripcion
	|   |- menuModificarNota
	|   |- menuModificarEstatus
	|   |- (ejecucion directa)
	|   |- menuMoverAlumno

	Abajo se encuentra la declaracion de las funciones
*/

void menuMantenimiento(void);
	void menuAlumnado(void);
		void menuConsultaAlumno(void);
	void menuMaterias(void);
		void menuConsultaMateria(void);
	void menuDeCursos(void);
		void menuConsultaCurso(void);
void menuInscripciones(void);
	void menuInsConsultas(void);
	void menuSingleInscripcion(void);
	void menuMultiInscripcion(void);
	void menuModificarNota(void);
	void menuModificarEstatus(void);
	void menuMoverAlumno(void);
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

/*
	Completa los registros de indice no completados por la carga de data de archivos
*/
void completarIndice(FILE *);

void main()
{
	int opt = -1;
	cargarDeArchivos();
	do {
		
		impCabezado();
		printf("Programa desarrollado por Tom%cs El Fakih y Robert Gonz%clez\n", 160, 160);
		impMenu("Que desea hacer?", 3, "Mantenimiento", "Inscripciones", "Consultas");

		scanf("%i%*c", &opt);
		switch ( opt ) {
			case 0: break;
			case 1: menuMantenimiento(); break;
			case 2: menuInscripciones(); break;
			case 3: menuParaConsultas(); break;
			default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
		}
	} while ( opt );
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
		impMenu("Que desea gestionar?", 3, "Alumnos", "Materias", "Cursos");

		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: menuAlumnado(); break;
		case 2: menuMaterias(); break;
		case 3: menuDeCursos(); break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
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
			"Estas son las opciones disponibles para los alumnos.\nMarque la opcion de acuerdo a la operacion que desea realizar", 
			4,
			"Agregar un alumno nuevo",
			"Modificar los datos de un alumno (por cedula)",
			"Eliminar un alumno de la lista (por cedula)",
			"Consultar"
		);
		
		scanf("%i%*c", &opt);
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
				printf("Por favor inserte el numero de cedula: ");
				scanf("%i%*c",&cedula);
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
				printf("Introduzca el numero de cedula a buscar: ");
				scanf("%i%*c", &cedula);
				elimAlumno(&Al, cedula);
				system("pause");
				break;
			case 4: menuConsultaAlumno();
				break;
			default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); 
		}
	} while ( opt );
}

void menuConsultaAlumno(void) {
	int opt = -1,
		cedula = -1;
	Alumno *A = NULL;
	do {
		impCabezado();
		impMenu("Que clase de consulta de alumno desea realizar?", 2, "Todos los alumnos", "Datos de un alumno individual");
		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: printListaAlumno(Al, detalle());
			system("pause");
			break;
		case 2: printf("Introduzca el numero de cedula del alumno: ");
			scanf("%i%*c", &cedula);
			if (A = obtenerAlumnoPorCedula(Al, cedula))
				printAlumno(A, detalle());
			else
				printf("No se encontro ningun alumno con la cedula %i\n", cedula);
			system("pause");
			break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); 

		}
	} while (opt);
}

void menuMaterias(void) {
	/* Esta funcion actua de manera muy similar a menuAlumnados. Ver la documentacion de esa funcion para una explicacion de lo que pasa */
	int opt = -1, codigo = -1;
	Materia *nuevo = NULL, *res = NULL;
	do {
		
		impCabezado();
		impMenu(
			"Estas son las opciones disponibles para las materias.\nMarque la opcion de acuerdo a la operacion que desea realizar",
			4,
			"Agregar Materia",
			"Modificar Materia",
			"Eliminar Materia",
			"Consultar"
		);
		
		scanf( "%i%*c", &opt );
		switch ( opt ) {
			case 0: break;
			case 1:
				nuevo = crearMateria();
				insertarMateria(&Mat, nuevo);
				system("pause");
				break;
			case 2:
				printf("Inserte el codigo de la materia que desea modificar: ");
				scanf("%i%*c", &codigo);
				res = obtenerMateriaPorCodigo(Mat, codigo);
				if (res) modificarMateria(&res);
				else printf("No se encontro ninguna materia con el codigo \"%i\"\n", codigo);
				system("pause");
				break;
			case 3:
				printf("Inserte el codigo de la materia a eliminar: ");
				scanf("%i%*c", &codigo);
				elimMateria(&Mat, codigo);
				system("pause");
				break;
			case 4: menuConsultaMateria();
				break;
			default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); 
		}
	} while ( opt );
}

void menuConsultaMateria(void) {
	int opt = -1,
		codigo = -1;
	Materia *M = NULL;
	do {
		impCabezado();
		impMenu("Que clase de consulta de materia desea realizar?", 2, "Todas las materias", "Datos de una materia individual");
		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: printListaMateria(Mat, detalle());
			system("pause");
			break;
		case 2: printf("Introduzca el codigo de la materia: ");
			scanf("%i%*c", &codigo);
			if (M = obtenerMateriaPorCodigo(Mat, codigo))
				printMateria(M, detalle());
			else
				printf("No se encontro ninguna materia con el codigo %i\n", codigo);
			system("pause");
			break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt);

		}
	} while (opt);
}

void menuDeCursos(void) {
	/* Esta funcion actua de manera muy similar a menuAlumnados. Ver la documentacion de esa funcion para una explicacion de lo que pasa */
	int opt = -1, codigo = -1;
	Curso *nuevo = NULL, *res = NULL;
	do {
		
		impCabezado();
		impMenu(
			"Estas son las opciones disponibles para los Cursos.\nMarque la opcion de acuerdo a la operacion que desea realizar",
			4,
			"Agregar Curso",
			"Modificar Curso",
			"Eliminar Curso",
			"Consultar"
		);

		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1:
			nuevo = crearCurso();
			if ( nuevo ) 
				insertarCurso(&Cur, nuevo);
			break;
		case 2:
			printf("Inserte el codigo del Curso que desea modificar: ");
			scanf("%i%*c", &codigo);
			res = obtenerCursoPorCodigo(Cur, codigo);
			if (res) modificarCurso(&res);
			else {
				printf("No se encontro ningun Curso con el codigo \"%i\"\n", codigo);
				system("pause");
			}
			break;
		case 3:
			printf("Inserte el codigo del Curso a eliminar: ");
			scanf("%i%*c", &codigo);
			elimCurso(&Cur, codigo);
			break;
		case 4: menuConsultaCurso();
			break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt);
		}
	} while (opt);
}

void menuConsultaCurso(void) {
	int opt = -1,
		codigo = -1;
	Curso *C = NULL;
	do {
		impCabezado();
		impMenu("Que clase de consulta de curso desea realizar?", 2, "Todos los cursos", "Datos de un curso individual");
		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: printListaCurso(Cur, detalle());
			system("pause");
			break;
		case 2: printf("Introduzca el codigo del curso: ");
			scanf("%i%*c", &codigo);
			if (C = obtenerCursoPorCodigo(Cur, codigo))
				printCurso(C, detalle());
			else
				printf("No se encontro ningun curso son el codigo %i\n", codigo);
			system("pause");
			break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt);

		}
	} while (opt);
}

void menuInscripciones(void) {
	// Opcion escogida en un menu
	int opt = -1, codigo = -1;;
	do {
		
		impCabezado();
		impMenu(
			"Opciones disponibles de inscripcion",
			7,
			"Consulta de claves (Alumno, Curso)",
			"Inscripcion de un alumno en un curso",
			"Inscripcion de varios alumnos en un curso",
			"Modificar la nota de un alumno en un curso",
			"Modificar estatus de inscripcion",
			"Eliminar un curso",
			"Mover un alumno de un curso a otro"
		);
		scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: menuInsConsultas(); break;
		case 2: menuSingleInscripcion(); break;
		case 3: menuMultiInscripcion(); break;
		case 4: menuModificarNota(); break;
		case 5: menuModificarEstatus(); break;
		case 6: printf("Ingrese el codigo del curso a eliminar: ");
			scanf("%i%*c", &codigo);
			elimCurso(&Cur, codigo);
		case 7: menuMoverAlumno(); break;
		default: printf("Opcion no reconocida\n");
			break;
		}
	} while (opt);
}

void menuParaConsultasAlumno(void){
	int opt = -1;
	do {
		
		impCabezado();
		impMenu("Que desea consultar sobre un alumno?", 3,
			"Mostrar su record academico",
			"Mostrar las veces que curso una materia especifica",
			"Calcular su promedio y el numero de materias reprobadas y retiradas"
			);

	scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: ImprimirRecordAcademicoAlumno(); break;
		case 2: BuscarRepeticionesDeCursos(); break;
		case 3: CalcularPromedio(); break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
		}
	} while (opt);
}
void menuParaConsultaCurso(void) {
	int opt = -1;
	do {
		
		impCabezado();
		impMenu("¿Que desea consultar sobre un curso?", 2,
			"Consultar numero de alumnos inscritos, numero de aprobados,                     reprobados y retirados",
			"Informacion del curso y de los alumnos inscritos"
			);

	scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: DatosDelCurso(); break;
		case 2: PrintOrdenAlfabeticoAlumnosApellido(); break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
		}
	} while (opt);

}

void menuParaConsultaMateria(void){
int opt = -1;
char str[] = "Mostrar la informacion de los alumnos que cursaron la materia en un             a%co especifico";
	do {
		
		impCabezado();
		sprintf(str, str, 164);
		impMenu("Que desea consultar?", 3,
			"Mostrar la cantidad de alumnos que ha cursado esta materia, el                  promedio por curso y la cantidad de retirados y reprobados",
			str,
			"Mostrar los alumnos que obtuvieron la calificacion mas alta y la                informacion del curso en el que se encuntran"
			);

	scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: InformacionHistoricaMateria(); break;
		case 2:	InformacionDeUnaMateria(); break;
		case 3: AlumnosNotaMaxima(); break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
		}
	} while (opt);
}

void menuParaConsultas(void) {
	int opt = -1;
	do {
		
		impCabezado();
		impMenu("Que desea consultar?", 5,
			"Buscar a un alumno por nombre",
			"Buscar la informacion de una materia mediante su nombre",
			"Informacion de un alumno por su cedula",
			"Informacion de un curso por su codigo",
			"Informacion de una materia por su codigo"
			);

	scanf("%i%*c", &opt);
		switch (opt) {
		case 0: break;
		case 1: BuscarAlumnos(); break;
		case 2: BuscarCursosPorNombre(); break;
		case 3: menuParaConsultasAlumno(); break;
		case 4: menuParaConsultaCurso(); break;
		case 5: menuParaConsultaMateria(); break;
		default: printf("Opcion \"%i\" no reconocida. Marque una opcion valida\n", opt); system("pause");
		}
	} while (opt);

}

void cargarDeArchivos() {
	// abrimos todos los handlers de los archivos. Los abrimos en modo anexo-lectura-binario para que se creen si no existen
	FILE *falumno = fopen("alumnos.alp2", "ab+"),
		*fmateria = fopen("materias.alp2", "ab+"),
		*fcurso   = fopen("cursos.alp2", "ab+"),
		*findice  = fopen("indice.alp2", "ab+");

	extraerAlumnosDesdeArchivo(&Al, falumno);
	extraerMateriasDesdeArchivo(&Mat, fmateria);
	extraerCursosDesdeArchivo(&Cur, fcurso);

	completarIndice(findice);
	//completarIndiceCursos(findcurs);

	// cerramos los handlers
	fclose(falumno);
	fclose(fmateria);
	fclose(fcurso);
	fclose(findice);

}

void completarIndice(FILE *f) {
	// Ayudante para sacar los datos
	ArchivoNotas notas;
	fread(&notas, sizeof ArchivoNotas, 1, f);
	if (!feof(f)) {
		Alumno *a = obtenerAlumnoPorCedula(Al, notas.cedula);
		Curso *c = obtenerCursoPorCodigo(Cur, notas.codigoCurso);
		inscribirEnCurso(a, c);
		modificarNotaAlumno(a, c, notas.nota);
		modificarEstatusAlumno(a, c, notas.estatus);
		completarIndice(f);
	}
}

void guardarEnArchivos() {
	// inicializamos los handlers de archivos
	FILE *falumno  = fopen("alumnos.alp2", "wb"),
		 *fmateria = fopen("materias.alp2", "wb"),
		 *fcurso   = fopen("cursos.alp2", "wb"),
		 *findice  = fopen("indice.alp2", "wb");

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

	// Variable especial para guardar las notas
	ArchivoNotas notas;
	if (IndCurso) {
		CursosY *CY = IndCurso;
		// iteramos sobre los cursos de cada año
		while (CY) {
			CursosS *cursos = CY->cursosDictados;
			while (cursos) {
				CursosA *alumnos = cursos->alumnos;
				while (alumnos) {
					notas.cedula = alumnos->alumno->cedula;
					notas.codigoCurso = cursos->curso->codigo;
					notas.nota = alumnos->nota;
					notas.estatus = alumnos->estatus;
					// guardamos en el archivo
					fwrite(&notas, sizeof(ArchivoNotas), 1, findice);
					alumnos = alumnos->prox;
				}
				cursos = cursos->prox;
			}
			CY = CY->prox;
		}
	}

	// cerramos los handlers de archivo
	fclose(falumno);
	fclose(fmateria);
	fclose(fcurso);
	fclose(findice);
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
			"Seleccione categoria de busqueda",
			2,
			"Alumnos por nombre",
			"Cursos por nombre de materia"
		);
		scanf("%i%*c", &opt);
		if (opt < 0 || opt > 2) printf("Opcion no reconocida\n");
		else if (opt) {
			printf("Introduzca termino de busqueda: ");
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

void menuSingleInscripcion(void) {
	int cedula = -1, codigo = -1, exito = -1, salir = 1;
	Alumno *A = NULL;
	Curso *C = NULL;
	do {
		
		impCabezado();
		printf("Ingrese la cedula del alumno a inscribir: ");
		scanf( "%i%*c", &cedula );
		if ( ! ( A = obtenerAlumnoPorCedula( Al, cedula ) ) ) {
			putchar('\n');
			printf("El numero de cedula %d no existe en el sistema\n", cedula);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		printf("Ingrese el codigo del curso al cual insertar el alumno: ");
		scanf( "%i%*c", &codigo );
		if ( ! ( C = obtenerCursoPorCodigo( Cur, codigo ) ) ) {
			putchar('\n');
			printf("El curso de codigo %d no existe en el sistema\n", codigo);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}

		// para este punto deberiamos tener una cedula y codigo validos
		exito = inscribirEnCurso(A, C);

		if ( ! exito )
			printf("Ocurrio un error al intentar inscribir el alumno al curso\n");
		else
			printf("El alumno fue inscrito con exito\n");
		salir = 1;
		system("pause");
	} while ( ! salir );

}

void menuMultiInscripcion(void) {
	int cedula = -1, codigo = -1, exito = -1, salir = 1, numAlum = 1;
	Alumno *A = NULL;
	Curso *C = NULL;
	do {
		
		impCabezado();
		printf("Ingrese el codigo del curso al que se insertaran alumnos: ");
		scanf("%i%*c", &codigo);
		if (!(C = obtenerCursoPorCodigo(Cur, codigo))) {
			putchar('\n');
			printf("No existe ningun curso con el codigo %d\n", codigo);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		printf("Ingrese los numeros de cedula de los alumnos a insertar\n");
		printf("Cuando quiera detenerse, ingrese cero (0)\n");
		do {
			printf("Cedula del alumno #%d: ", numAlum);
			scanf("%i%*c", &cedula);
			if (!cedula) break;
			if (!(A = obtenerAlumnoPorCedula(Al, cedula))) {
				printf("No existe ningun alumno con la cedula %d\n", cedula);
				continue;
			}
			else {
				exito = inscribirEnCurso(A, C);
				if (!exito)
					printf("Ocurrio un error al intentar inscribir el alumno al curso\n");
				else {
					numAlum++;
					printf("El alumno fue inscrito con exito\n");
				}
			}
		} while (1);
		system("pause");
	} while (!salir);
}

void menuModificarNota(void) {
	int salir = 1, cedula = -1, codigo = -1;
	Alumno *alumno = NULL;
	Curso *curso = NULL;
	do {
		impCabezado();
		printf("Ingrese la cedula del alumno cuya nota se alterara: ");
		scanf("%i%*c", &cedula);
		if (!(alumno = obtenerAlumnoPorCedula(Al, cedula))) {
			printf("No se consiguio ningun alumno con la cedula %d\n", cedula);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		printf("Ingrese el codigo del curso que cursa el alumno: ");
		scanf("%i%*c", &codigo);
		if ( ! (curso = obtenerCursoPorCodigo(Cur, codigo))) {
			printf("No se consiguio ningun curso con el codigo %d\n", codigo);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		// verificamos que siquiera este inscrito el alumno en el curso
		if (EstaInscrito(ubicarListaAlumnos(curso), alumno->cedula))
			// en caso de que lo este, entonces podemos cargar la modificacion
			modificarNotaAlumno(alumno, curso);
		else printf("El alumno %s no se encuentra inscrito en %s (%d)", alumno->nombre, obtenerMateriaPorCodigo(Mat, curso->codMat)->nombre, curso->ano);
		salir = 1;
		system("pause");
	} while (!salir);
}

void menuModificarEstatus(void) {
	int salir = -1, cedula = -1, codigo = -1;
	Alumno *alumno = NULL;
	Curso *curso = NULL;
	do {
		impCabezado();
		printf("Ingrese la cedula del alumno cuyo estatus se modificara: ");
		scanf("%i%*c", &cedula);
		if (!(alumno = obtenerAlumnoPorCedula(Al, cedula))) {
			printf("No se consiguio ningun alumno con la cedula %d\n", cedula);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		printf("Ingrese el codigo del curso del alumno: ");
		scanf("%i%*c", &codigo);
		if (!(curso = obtenerCursoPorCodigo(Cur, codigo))) {
			printf("No se consiguio ningun curso con el codigo %d\n", codigo);
			salir = !impSiNo("Desea volver a intentar?");
			continue;
		}
		if (EstaInscrito(ubicarListaAlumnos(curso), alumno->cedula)) {
			modificarEstatusAlumno(alumno, curso);
		}
		else {
			printf("El alumno %s no se encuentra inscrito en %s (%d)\n", alumno->nombre, obtenerMateriaPorCodigo(Mat, curso->codMat)->nombre, curso->ano); printf("El alumno %s no se encuentra inscrito en %s (%d)", alumno->nombre, obtenerMateriaPorCodigo(Mat, curso->codMat)->nombre, curso->ano);
		}
		salir = 1;
		system("pause");
	} while (!salir);
}

void menuMoverAlumno(void) {
	int salir = -1, cedula = -1, codigoFuente = -1, codigoDestino = -1, exito = -1;
	Alumno *alumno = NULL;
	Curso *fuente = NULL, *destino= NULL;
	do {
		impCabezado();
		printf("Introduzca la cedula del alumno a mover: ");
		scanf("%i%*c", &cedula);
		if (!(alumno = obtenerAlumnoPorCedula(Al, cedula))) {
			printf("No existe ningun alumno con la cedula %d\n", cedula);
			salir = !impSiNo("Desea volver a ingresar los datos?");
			continue;
		}
		printf("Introduzca el codigo del curso donde esta el alumno, y seguido de un espacio, el codigo del curso destino: ");
		scanf("%i %i%*c", &codigoFuente, &codigoDestino);
		// verificamos que el codigo del curso fuente sea valido
		if (!(fuente = obtenerCursoPorCodigo(Cur, codigoFuente)))
			printf("No existe curso con el codigo %d\n", codigoFuente);
		// verificamos que el codigo del curso destino sea valido
		if (!(destino = obtenerCursoPorCodigo(Cur, codigoDestino)))
			printf("No existe curso con el codigo %d\n", codigoDestino);
		// si alguno no fue valido, damos la opcion de reintentar
		if (!(fuente && destino)) {
			salir = !impSiNo("Desea volver a ingresar los datos?");
			continue;
		}
		// si llegamos hasta aqui, los valores son validos
		/* Valores de retorno validos 
			0: Exito, no hubo ningun problema
			1: El alumno no estaba inscrito el en curso fuente
			2: El alumno ya se encuentra en el curso destino
			default: No deberia caer, pero quien sabe...
				Quiere decir que no existia alguno de los elementos, pero se supone fueron validados antes...
		*/
		switch (moverAlumnoDeCurso(alumno, fuente, destino)) {
		case 0: printf("El alumno %s fue movido con exito de \"%s (%d)\" a \"%s (%d)\"", alumno->nombre, obtenerMateriaPorCodigo(Mat, fuente->codMat)->nombre, fuente->ano, obtenerMateriaPorCodigo(Mat, destino->codMat)->nombre, destino->ano);
			salir = 1;
			break;
		case 1: printf("Error al inscribir: El alumno no se encuentra inscrito en el curso fuente");
			salir = !impSiNo("Desea volver a intentar?");
			break;
		case 2: printf("Error al inscribir: El alumno ya se encuentra inscrito en el curso destino");
			salir = !impSiNo("Desea volver a intentar?");
			break;
		default: printf("Error inesperado: Al parecer la validacion no esta funcionando");
		}
		system("pause");
	} while (! salir);
}