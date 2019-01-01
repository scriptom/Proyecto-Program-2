#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "functions.h"
#include "materias.h"

Materia *Mat = NULL;

void printMateria(Materia *M, int detalle) {
	if (!M) return; // solamente actuamos si la Materia no es NULL
	printf("Informaci�n de la Materia: %s\n", M->nombre);
	printf("\tNombre: %s\n", M->nombre);
	printf("\tC�digo: %i\n", M->codigo);
	if (detalle) {
		printf("\t�rea: %s\n", M->area);
		printf("\tCr�ditos: %d\n", M->creditos);
		printf("\tSemestre: %d\n\n", M->semestre);
	}
}

void printListaMateria(Materia *M, int detalle) {
	// solamente actuamos si la lista no esta vacia
	if (!M) {
		printf("\tLista vac�a\n");
		return;
	}
	printf("----------------------------\n\n");
	// mostramos la informacion de esta Materia como nos la planteen
	printMateria(M, detalle);
	// si tenemos mas Materias, llamamos recursivamente con la siguiente, caso contrario, cerramos la tablita y salimos de la pila
	if (M->prox) printListaMateria(M->prox, detalle);
	else printf("----------------------------\n");
}

Materia *crearMateria() {
	// declaramos el nuevo Materia a insertar, y un auxiliar para saber si el Materia existe
	Materia *M = new Materia, *existe = NULL;

	miflush(); // limpiamos el buffer de entrada

	// solicitamos el nombre del Materia
	printf("Nombre del Materia: ");
	gets_s(M->nombre);

	// solicitamos la Codigo del Materia hasta que esta sea una Codigo unica (No este en el sistema)
	do {
		printf("C�digo de identidad de la Materia: ");
		scanf("%i", &(M->codigo));
		existe = obtenerMateriaPorCodigo(Mat, M->codigo);
		if (existe)
			printf("La Materia con el c�digo \"%i\" ya existe, pertence a %s\n Por favor ingrese otro c�digo\n", existe->codigo, existe->nombre);
	} while (existe);

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// solicitamos el area de la Materia
	printf("�rea: \n");
	gets_s(M->area);

	// solicitamos el numero de creditos que ocupa la Materia
	printf("N�mero de cr�ditos: \n");
	scanf("%hhd", &(M->creditos));
	
	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// solicitamos el semestre en el que se debe estar para cursar la Materia
	printf("Semestre m�nimo: \n");
	scanf("%hhd", &(M->semestre));

	miflush(); // despues de una llamada a scanf, hay que limpiar el buffer

	// inicializamos el proximo elemento de este Materia como nulo
	M->prox = NULL;

	// devolvemos
	return M;
}

void insertarMateria(Materia **P, Materia *M) {
	if (M->prox) M->prox = NULL;
	// si la cabeza es nulo, entonces asignamos el nuevo como cabeza
	if (!(*P)) *P = M;
	// si el siguiente es nulo, estamos en el ultimo elemento, insertemos
	else if (!(*P)->prox) (*P)->prox = M;
	// llamamos recursivamente si estamos en cualquier otro punto de la lista
	else insertarMateria(&(*P)->prox, M);
}

void modificarMateria(Materia **P) {
	// nada mas actuamos si no tenemos un puntero a nulo
	if (*P) {
		// inicializamos el manejador de opciones a 0
		int opt = -1;
		// salimos cuando la opcion sea 0
		do {
			// mostramos el encabezado
			impCabezado();
			printMateria(*P);
			impMenu(
				"Estas son las opciones disponibles para las Materias.\nMarque la opci�n de acuerdo a la operaci�n que desea realizar",
				5,
				"Editar n�mero de C�digo",
				"Editar el nombre de la Materia",
				"Editar el �rea de la Materia",
				"Editar el n�mero de cr�ditos",
				"Editar semestre m�nimo"
			);
			scanf("%i", &opt);
			switch (opt) {
			case 0: break;
			case 1:
				printf("Introduzca el nuevo n�mero de c�digo para %s. Actual: %d: ", (*P)->nombre, (*P)->codigo);
				scanf("%i", &((*P)->codigo));
				break;
			case 2:
				printf("Introduzca un nuevo nombre para %s: ", (*P)->nombre);
				miflush();
				gets_s((*P)->nombre);
				break;
			case 3:
				printf("Introduzca la nueva �rea para %s. Actual: %s: ", (*P)->nombre, (*P)->area);
				gets_s((*P)->area);
				break;
			case 4:
				printf("Introduzca la nueva cantidad de cr�ditos de %s. Actual: %d: ", (*P)->nombre, (*P)->creditos);
				scanf("%c", (*P)->creditos);
				miflush();
				break;
			case 5:
				printf("Introduzca el nuevo semestre m�nimo para %s. Actual: %d: ", (*P)->nombre, (*P)->semestre);
				scanf("%c", (*P)->semestre);
				break;
			default:
				printf("Opci�n no reconocida. Vuelva a intentar\n");
			}
		} while (opt);
	}
}

void elimMateria(Materia **P, int codigo) {
	if (!*P) return; // regresamos si el listado esta vacio
	Materia *del; // declaramos un auxiliar de eliminacion
	if ((*P)->codigo == codigo) {
		// si el codigo coincide con el primer elemento, tenemos que eliminar la cabeza
		del = *P;
		*P = (*P)->prox;
		if ( impSiNo("Seguro que desea eliminar la materia?") )
			delete del;
		return;
	}

	// ayudante para iterar
	Materia  *M = *P;
	// iteramos hasta el ultimo elemento
	while (M && M->prox) {

		if (M->prox->codigo == codigo) {
			// si el codigo del proximo en la lista coincide, entonces tenemos que eliminarlo
			del = M->prox;
			M->prox = del->prox;
			if ( impSiNo("Seguro que desea eliminar la matera?") )
				delete del;
			return;
		}

		M = M->prox;
	}

	// si llegamos hasta aqui, la materia no existe
	printf("La materia con el codigo %d no existe\n", codigo);
}

Materia *obtenerMateriaPorCodigo(Materia *M, int codigo) {
	// si tenemos una materia, comparamos el codigo. Si no existe retornamos NULL
	if (M) return M->codigo == codigo ? M : obtenerMateriaPorCodigo(M->prox, codigo);
	return NULL;
}

int cantidadMaterias(Materia *M) {
	return M ? cantidadMaterias(M->prox) + 1 : 0;
}

Materia *obtenerEnesimaMateria(Materia *M, int n) {
	if ( M )
		return n ? obtenerEnesimaMateria(M->prox, n-1) : M;
	return NULL;
}

int ObtenerCodigoMateria(Materia *P,char *Nombre){
	// Lista de materias coincidientes en la busqueda
	Materia *M = NULL,
		// Ayudante de iteracion de la lista pasada
		    *T = P,
		// Adyuante de iteracion para la lista de coincidencias (En caso de que haya mas de una)
			*aux;
	// Cantidad de coincidencias por nombre
	int cm,
		// Control de iteracion de coincidencias
		cont = 0,
		// Opcion de coincidencia, escogida por el usuario
		opcion = 0;
	Nombre = minusculas(Nombre);
	while (T){
		if (strstr(minusculas(T->nombre),Nombre))
			insertarMateria(&M,T);
		T=T->prox;
	}
	if (( cm = cantidadMaterias(M)) > 1) {
		impCabezado();
		printf("Elija la materia que desea usar para su b�squeda:\n\n");
		aux = M;
		for ( ; cont < cm; cont++, aux = aux->prox)
			printf("\t%i. %s\n", cont + 1, aux->nombre);
		do {
			scanf("%i",&opcion);
			if ((opcion < 1) || (opcion > cm))
				printf("El n�mero indicado no es v�lido\n");
		} while ((opcion < 1) || (opcion > cm));
			aux = obtenerEnesimaMateria(M, opcion);
			return aux->codigo;
		}
	else if (cm == 1) return M->codigo;
	else return 0;
}

void vaciarListaMaterias(Materia **P) {
	if (*P) {
		vaciarListaMaterias(&((*P)->prox));
		delete (*P);
	}
}

void extraerMateriasDesdeArchivo(Materia **P, FILE *f) {
	// reservamos memoria
	Materia *M = new Materia;
	// leemos registro
	fread(M, sizeof Materia, 1, f);
	// comprobamos que no sea fin de archivo
	if (!feof(f)) {
		// volvemos el siguiente nulo
		M->prox = NULL;
		// insertamos
		insertarMateria(P, M);
		// llamamos recursivamente
		extraerMateriasDesdeArchivo(P, f);
	}
	else delete M; // si llegamos a fin de archivo, liberemos la memoria (no lo hacemos siempre porque la memoria declarada aqui fue insertada
}

Materia *extraerMateria(Materia *M, int codigo) {
	// Materia a extraer de la lista
	Materia *objetivo = obtenerMateriaPorCodigo(M, codigo),
		// Alumno a devolver
		*extraido = new Materia;

	// si no obtuvimos nada, limpiamos la memoria reservada y regresamos nulo
	if (!objetivo) {
		delete extraido;
		return NULL;
	}

	// copiamos todos los campos, y nulificamos el puntero a proximo
	strcpy_s(extraido->nombre, sizeof(objetivo->nombre), objetivo->nombre);
	strcpy_s(extraido->area, sizeof(objetivo->area), objetivo->area);
	extraido->creditos = objetivo->creditos;
	extraido->semestre = objetivo->semestre;
	extraido->codigo = objetivo->codigo;
	extraido->prox = NULL;

	// regresamos
	return extraido;
}