#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>
#include "cursos.h"
#include "materias.h"
#include "functions.h"

Curso *Cur = NULL;
static const char *HorariosArr[3] = { "Matutino", "Vespertino", "Nocturno" };

const char *horStr(Horario h) {
	return HorariosArr[(int)h];
}

void printCurso(Curso *C, int detalle) {
	TILDES;
	if (!C) return; // solamente actuamos si la Curso no es NULL
	Materia *M = obtenerMateriaPorCodigo(Mat, C->codMat);
	printf("Información del Curso: %s (%d)\n\n", M->nombre, C->ano);
	printf("\tNombre de la materia: %s\n", M->nombre);
	printf("\tCódigo Curso: %i\n", C->codigo);
	if (detalle) {
		printf("\tAño: %d\n", C->ano);
		printf("\tLapso: %d\n", C->lapso);
		printf("\tCódigo de la materia: %d\n", C->codMat);
		printf("\tHorario: %s\n\n", horStr( C->horario ));
	}
}

void printListaCurso(Curso *C, int detalle) {
	// solamente actuamos si la lista no esta vacia
	if (!C) {
		printf("\tLista vacía\n");
		return;
	}
	printf("----------------------------\n\n");
	// mostramos la informacion de esta Curso como nos la planteen
	printCurso(C, detalle);
	// si tenemos mas mursos, llamamos recursivamente con la siguiente, caso contrario, cerramos la tablita y salimos de la pila
	if (C->prox) printListaCurso(C->prox, detalle);
	else printf("----------------------------\n");
}

Curso *crearCurso() {
	// declaramos el nuevo Curso a insertar, y un auxiliar para saber si el Curso existe
	Curso *C = new Curso, *existe = NULL;
	int codigoCurso = -1, codigoMateria = -1, horario = -1, reintentar = 1;
	unsigned short ano = 0;

	miflush(); // limpiamos el buffer de entrada
	do {
		do {
			//  solicitamos el codigo de la materia del curso
			printf("Introduzca el código de la materia: ");
			scanf("%i", &codigoMateria);
			miflush();
			if ( ! obtenerMateriaPorCodigo(Mat, codigoMateria)) {
				printf("No existe ninguna materia con el código \"%i\"\n", codigoMateria);
				if ( ! impSiNo("Desea reintentar?")) return NULL;
				codigoMateria = 0;
			}
		} while ( !codigoMateria );

		do {
			// solicitamos el ano de la Curso
			printf("Año que representa este curso: ");
			scanf("%hu", &ano);
			if ( ano < 1970) printf("El año introducido es inválido, introduzca otro\n");
		} while ( ano < 1970 );

		// para este punto, el año y el codigo de la materia son validos, asi que podemos generar el codigo del curso
		codigoCurso = genCodigoCurso(ano, codigoMateria);
		existe = obtenerCursoPorCodigo(Cur, codigoCurso);
		if (existe) {
			printf("Un curso con esas características ya existe (Código %d)\n", existe->codigo);
			if ( ! impSiNo("Desea reintentar?")) return NULL;
		}
	} while (existe);
	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer
	// podemos guardar los datos
	C->ano = ano;
	C->codMat = codigoMateria;
	C->codigo = codigoCurso;

	// solicitamos el numero de lapso que ocupa la Curso
	printf("Número de lapso: ");
	scanf("%hhd", &(C->lapso));

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer
	do {
		// solicitamos el horario en el que se debe estar para cursar la Curso
		impMenu("Horario de este curso", 3, "Matutino", "Vespertino", "Nocturno");
		scanf("%d", &horario);
		if ( ( horario < 1  ) || ( horario > 3 ) ) printf("Opción no reconocida, por favor seleccione una opción válida\n");
	} while ( ( horario < 1 ) || ( horario > 3 ) );

	// para este punto el horario es valido, hacemos una conversion explicita
	C->horario = (Horario)(--horario);

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// inicializamos el proximo elemento de este Curso como nulo
	C->prox = NULL;

	// devolvemos
	return C;
}

void insertarCurso(Curso **P, Curso *C) {
	// como es insercion por cola, tenemos que volver nulo el proximo del elemento a insertar
	if ( C->prox ) C->prox = NULL;
	// si la cabeza es nulo, entonces asignamos el nuevo como cabeza
	if (!(*P)) *P = C;
	// si el siguiente es nulo, estamos en el ultimo elemento, insertemos
	else if (!(*P)->prox) (*P)->prox = C;
	// llamamos recursivamente si estamos en cualquier otro punto de la lista
	else insertarCurso(&(*P)->prox, C);
}

void modificarCurso(Curso **P) {
	// nada mas actuamos si no tenemos un puntero a nulo
	if (*P) {
		int opt = -1, codMat = -1, cursoInvalido = -1, ano = -1, horario = -1, codigo = -1;
		Curso *existe = NULL;
		// salimos cuando la opcion sea 0
		do {
			// mostramos el encabezado
			impCabezado();
			printCurso(*P);
			printf("**NOTA: EL AÑO Y EL CÓDIGO DE LA MATERIA NO SE GUARDARÁN HASTA QUE DECIDA SALIR**\n\n");
			impMenu(
				"Estas son las opciones disponibles para los Cursos.\nMarque la opción de acuerdo a la operación que desea realizar",
				4,
				"Editar el Código de Materia",
				"Editar el año del Curso",
				"Editar el número de lapso",
				"Editar horario"
			);
			scanf("%i", &opt);
			switch (opt) {
			case 0: break;
			case 1:
				printf("Introduzca el nuevo código de materia para este curso. Actual: %d: ", (*P)->codMat);
				do {
					scanf("%d", &codMat);
					if ( ! obtenerMateriaPorCodigo( Mat, codMat ) ) {
						printf("No existe ninguna materia con ese código\nIntroduzca otro\n");
						codMat = 0;
					}
				} while ( !codMat );
				break;
			case 2:
				printf("Introduzca un nuevo año para este curso. Actual: %d: ", (*P)->ano);
				scanf("%hu", &ano);
				miflush();
				break;
			case 3:
				printf("Introduzca el nuevo lapso para este curso. Actual: %d: ",  (*P)->lapso);
				scanf("%d", &((*P)->lapso));
				miflush();
				break;
			case 4:
				printf("Seleccione el nuevo turno de horario para este curso. Actual: %s\n", horStr((*P)->horario));
				impMenu("\0", 3, "Matutino", "Vespertino", "Nocturno");
				do {
					scanf("%hu", &horario);
					if ( (horario < 1) || (horario > 3) ) printf("Opción no reconocida, seleccione un horario válido\n");
				} while ( (horario < 1) || (horario > 3) );
				(*P)->horario = (Horario)(--horario);
				break;
			default:
				printf("Opción no reconocida. Vuelva a intentar\n");
			}
			if ( ano != -1 || codMat != -1 ) {
				if ( ano == -1 ) ano = (*P)->ano;
				if ( codMat == -1 ) codMat = (*P)->codMat;
				codigo = genCodigoCurso( ano, codMat );
				existe = obtenerCursoPorCodigo(Cur, codigo);
				if (existe) {
					printf("Ya existe un curso de la materia %s en el año %d. Por favor verifique los datos e intente nuevamente\n", obtenerMateriaPorCodigo(Mat, existe->codMat)->nombre, existe->ano);
					cursoInvalido = 1;
				} else {
					(*P)->ano = ano;
					(*P)->codMat = codMat;
					(*P)->codigo = codigo;
					cursoInvalido = 0;
				}
			} else cursoInvalido = 0;
		} while (opt || cursoInvalido);
	}
}

void elimCurso(Curso **P, int codigo) {
	if (!*P) return; // regresamos si el listado esta vacio
	Curso *del = NULL; // declaramos un auxiliar de eliminacion
	if ((*P)->codigo == codigo) {
		// si el codigo coincide con el primer elemento, tenemos que eliminar la cabeza
		del = *P;
		*P = (*P)->prox;
		if ( impSiNo("Seguro que desea eliminar el curso?") )
			delete del;
		return;
	}

	// ayudante para iterar
	Curso  *C = *P;
	// iteramos hasta el ultimo elemento
	while (C && C->prox) {

		if (C->prox->codigo == codigo) {
			// si el codigo del proximo en la lista coincide, entonces tenemos que eliminarlo
			del = C->prox;
			C->prox = del->prox;
			if ( impSiNo("Seguro que desea eliminar el curso?") )
				delete del;
			return;
		}

		C = C->prox;
	}

	// si llegamos hasta aqui, no existe
	printf("No existe el curso especificado\n");
}

Curso *obtenerCursoPorCodigo(Curso *C, int codigo) {
	// si tenemos una Curso, comparamos el codigo. Si no existe retornamos NULL
	if (C) return C->codigo == codigo ? C : obtenerCursoPorCodigo(C->prox, codigo);
	return NULL;
}

int genCodigoCurso(int ano, int cod) {
	int codigo = -1;
	char aux[10];
	sprintf(aux, "%d%d", ano, cod);
	sscanf(aux, "%d", &codigo);

	return codigo;
}

void BuscarCursos(char *NombreM){
	int Codigo;
	Curso *C=NULL;
	Codigo = ObtenerCodigoMateria(Mat,NombreM);
	if (Codigo){
		Buscar(Codigo,&C);
		printListaCurso(C, detalle());
	}
	else{ printf("La materia solicitada no existe\n");} 
}

void Buscar(int Codigo, Curso **C){
	Curso *T= Cur;
	while (T){
		if ((T->codMat)== Codigo)
			insertarCurso(C, extraerCurso(T, T->codigo));
		T = T->prox;
	}
}

void vaciarListaCursos(Curso **P) {
	if (*P) {
		vaciarListaCursos(&((*P)->prox));
		delete (*P);
	}
}

void extraerCursosDesdeArchivo(Curso **P, FILE *f) {
	// reservamos memoria
	Curso *C = new Curso;
	// leemos registro
	fread(C, sizeof Curso, 1, f);
	// comprobamos que no sea fin de archivo
	if (!feof(f)) {
		// volvemos el siguiente nulo
		C->prox = NULL;
		// insertamos
		insertarCurso(P, C);
		// llamamos recursivamente
		extraerCursosDesdeArchivo(P, f);
	}
	else delete C; // si llegamos a fin de archivo, liberemos la memoria (no lo hacemos siempre porque la memoria declarada aqui fue insertada
}

Curso *extraerCurso(Curso *C, int codigo) {
	// Alumno a extraer de la lista
	Curso *objetivo = obtenerCursoPorCodigo(C, codigo),
		// Alumno a devolver
		*extraido = new Curso;

	// si no obtuvimos nada, limpiamos la memoria reservada y regresamos nulo
	if (!objetivo) {
		delete extraido;
		return NULL;
	}

	// copiamos todos los campos, y nulificamos el puntero a proximo
	extraido->ano = objetivo->ano;
	extraido->horario = objetivo->horario;
	extraido->codigo = objetivo->codigo;
	extraido->lapso = objetivo->lapso;
	extraido->codMat = objetivo->codMat;
	extraido->prox = NULL;

	// regresamos
	return extraido;
}