#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "materias.h"
#include "cursos.h"
#include "alumnos.h"

Materia *Mat = NULL;

void printMateria(Materia *M, int detalle) {
	if (!M) return; // solamente actuamos si la Materia no es NULL
	printf("Informacion de la Materia: %s\n", M->nombre);
	printf("\tNombre: %s\n", M->nombre);
	printf("\tCodigo: %i\n", M->codigo);
	if (detalle) {
		printf("\tArea: %s\n", M->area);
		printf("\tCreditos: %d\n", M->creditos);
		printf("\tSemestre: %d\n\n", M->semestre);
	}
}

void printListaMateria(Materia *M, int detalle) {
	// solamente actuamos si la lista no esta vacia
	if (!M) {
		printf("\tLista vacia\n");
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

	// solicitamos el nombre del Materia
	printf("Nombre del Materia: ");
	gets_s(M->nombre);

	// solicitamos la Codigo del Materia hasta que esta sea una Codigo unica (No este en el sistema)
	do {
		printf("Codigo de identidad de la Materia: ");
		scanf("%i%*c", &(M->codigo));
		existe = obtenerMateriaPorCodigo(Mat, M->codigo);
		if (existe)
			printf("La Materia con el codigo \"%i\" ya existe, pertence a %s\n Por favor ingrese otro codigo\n", existe->codigo, existe->nombre);
	} while (existe);

	// solicitamos el area de la Materia
	printf("area: ");
	gets_s(M->area);

	// solicitamos el numero de creditos que ocupa la Materia
	printf("Numero de creditos: ");
	scanf("%hu%*c", &(M->creditos));
	
	// solicitamos el semestre en el que se debe estar para cursar la Materia
	printf("Semestre minimo: ");
	scanf("%hu%*c", &(M->semestre));

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
				"Estas son las opciones disponibles para las Materias.\nMarque la opcion de acuerdo a la operacion que desea realizar",
				5,
				"Editar numero de Codigo",
				"Editar el nombre de la Materia",
				"Editar el area de la Materia",
				"Editar el numero de creditos",
				"Editar semestre minimo"
			);
			scanf("%i%*c", &opt);
			switch (opt) {
			case 0: break;
			case 1:
				printf("Introduzca el nuevo numero de codigo para %s. Actual: %d: ", (*P)->nombre, (*P)->codigo);
				scanf("%i%*c", &((*P)->codigo));
				break;
			case 2:
				printf("Introduzca un nuevo nombre para %s: ", (*P)->nombre);
				gets_s((*P)->nombre);
				break;
			case 3:
				printf("Introduzca la nueva area para %s. Actual: %s: ", (*P)->nombre, (*P)->area);
				gets_s((*P)->area);
				break;
			case 4:
				printf("Introduzca la nueva cantidad de creditos de %s. Actual: %d: ", (*P)->nombre, (*P)->creditos);
				scanf("%hu%*c", &((*P)->creditos));
				break;
			case 5:
				printf("Introduzca el nuevo semestre minimo para %s. Actual: %d: ", (*P)->nombre, (*P)->semestre);
				scanf("%hu%*c", &((*P)->semestre));
				break;
			default:
				printf("Opcion no reconocida. Vuelva a intentar\n");
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
			if ( impSiNo("Seguro que desea eliminar la materia?") )
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
		return n != 1 ? obtenerEnesimaMateria(M->prox, n-1) : M;
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
			insertarMateria(&M, extraerMateria(T, T->codigo));
		T=T->prox;
	}
	if (( cm = cantidadMaterias(M)) > 1) {
		impCabezado();
		printf("Elija la materia que desea usar para su busqueda:\n\n");
		aux = M;
		for ( ; cont < cm; cont++, aux = aux->prox)
			printf("\t%i. %s\n", cont + 1, aux->nombre);
		do {
			scanf("%i%*c",&opcion);
			if ((opcion < 1) || (opcion > cm))
				printf("El numero indicado no es valido\n");
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

void InformacionHistoricaMateria(void){
	CursosY *T = IndCurso;
	int Codigo, CantidadCur = 0;
	float Nota = 0.0f;
	Materia *MateriaBuscada;
	CursosS *CursoEncontrado;
	CursosS *Lista = NULL;
	PromedioCurso *Prom = new PromedioCurso;
	Prom->Aprobados = 0;
	Prom->Reprobados = 0;
	Prom->Retirados = 0;
	Prom->CantidadAlumnos = 0;
	Prom->promedio = 0.0f;
	int SN = 1;
	do{
		printf("\nIntroduzca el codigo de la materia\n");
		scanf("%i%*c",&Codigo);
		MateriaBuscada = obtenerMateriaPorCodigo(Mat,Codigo);
		if (!MateriaBuscada){
			SN = impSiNo("La materia no existe, ¿Desea introducir otro codigo?");
			if (!SN) return;
			}
	} while (!MateriaBuscada);
		while (T){
			CursoEncontrado = obtenerCursos(T->cursosDictados,Codigo);
			if (CursoEncontrado) InsertarListaCursosScola(&Lista,CursoEncontrado);
			T = T->prox;
		}
		while(Lista){
			CantidadCur++;
			CalcularAlumnos(Lista->alumnos,&Prom);
			Nota +=Prom->promedio;
			printf("\nEl promedio de los alumnos del curso del año: %hu, es: %05.2f\n",(Lista->curso)->ano,Prom->promedio);
			Lista = Lista->prox;
		}
		printf("\nLa cantidad total de alumos que han cursado esta materia es: %i\n El promedio de todos los cursos es %05.2f\nEl numero de reprobados es: %i\nEl numero de retirados es:%i%*c", Prom->CantidadAlumnos, Nota / CantidadCur, Prom->Reprobados, Prom->Retirados);
		system("Pause");
}

void InformacionDeUnaMateria(void){
	PromedioCurso *Prom = new PromedioCurso;
	Prom->Aprobados =0 ;
	Prom->Reprobados = 0;
	Prom->Retirados = 0;
	Prom->promedio = 0;
	Prom->CantidadAlumnos = 0;
	int Codigo,ano,SN =1;
	int CodigoCurso;
	Materia *MateriaBuscada;
	CursosS *P;
	Curso *Buscado;
	do{
		printf("\nIntroduzca el codigo de la materia\n");
		scanf("%i%*c",&Codigo);
		MateriaBuscada = obtenerMateriaPorCodigo(Mat,Codigo);
		printf("Introduzca el año del curso: ");
		scanf("%i%*c",&ano);
		if (!MateriaBuscada){
			SN = impSiNo("La materia no existe, ¿Desea introducir otro codigo?");
			if (!SN) return;
			}
	} while (!MateriaBuscada);
	Buscado = BuscarCursoPorCodigoYano(Codigo,ano);
	if (!Buscado){
		printf("El curso que busca no existe");
		system("Pause");
		return;
	}
	else{
		P = ObtenerCursosS(Buscado);
		CalcularAlumnos(P->alumnos,&Prom);
		printf("\nLa cantidad total de alumos que han cursado esta materia es: %i\n El promedio de todos los cursos es: %05.2f\nEl numero de reprobados es: %i\nEl numero de retirados es:%i%*c",Prom->CantidadAlumnos,Prom->promedio,Prom->Reprobados,Prom->Retirados);
		printf("\n");
		system("Pause");
		}
}

void AlumnosNotaMaxima(void){
	CursosY *T = IndCurso;
	int Codigo,CantidadCur = 0,Nota = 0;
	Materia *MateriaBuscada;
	CursosS *CursoEncontrado;
	CursosS *Lista = NULL;
	PromedioCurso *Prom = new PromedioCurso;
	Prom->Aprobados = 0;
	Prom->Reprobados = 0;
	Prom->Retirados = 0;
	Prom->CantidadAlumnos = 0;
	Prom->promedio = 0;
	int SN = 1;
		{
		printf("\nIntroduzca el codigo de la materia\n");
		scanf("%i%*c",&Codigo);
		MateriaBuscada = obtenerMateriaPorCodigo(Mat,Codigo);
		if (!MateriaBuscada){
			SN = impSiNo("La materia no existe, ¿Desea introducir otro codigo?");
			if (!SN) return;
			}
	} while (!MateriaBuscada);
	while (T){
		CursoEncontrado = obtenerCursos(T->cursosDictados,Codigo);
		if (CursoEncontrado) InsertarListaCursosScabeza(&Lista,CursoEncontrado);
		T = T->prox;
	}
	printf("\n");
	BuscarNotaMax(Lista);
	system("Pause");
}