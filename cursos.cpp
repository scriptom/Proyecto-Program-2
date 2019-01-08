#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alumnos.h"
#include "cursos.h"
#include "materias.h"
#include "functions.h"


Curso *Cur = NULL;
CursosY *IndCurso = NULL;
static const char *HorariosArr[3] = { "Matutino", "Vespertino", "Nocturno" };

const char *horStr(Horario h) {
	return HorariosArr[(int)h];
}

void printCurso(Curso *C, int detalle) {
	
	if (!C) return; // solamente actuamos si el Curso no es NULL
	Materia *M = obtenerMateriaPorCodigo(Mat, C->codMat);
	printf("Informacion del Curso: %s (%d)\n\n", M->nombre, C->ano);
	printf("\tNombre de la materia: %s\n", M->nombre);
	printf("\tCodigo Curso: %i\n", C->codigo);
	if (detalle) {
		printf("\tAño: %d\n", 164, C->ano);
		printf("\tLapso: %d\n", C->lapso);
		printf("\tCodigo de la materia: %d\n", C->codMat);
		printf("\tHorario: %s\n\n", horStr( C->horario ));
	}
}

void printListaCurso(Curso *C, int detalle) {
	
	// solamente actuamos si la lista no esta vacia
	if (!C) {
		printf("\tLista vacia\n");
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

	do {
		do {
			//  solicitamos el codigo de la materia del curso
			printf("Introduzca el codigo de la materia: ");
			scanf("%i%*c", &codigoMateria);
			if ( ! obtenerMateriaPorCodigo(Mat, codigoMateria)) {
				printf("No existe ninguna materia con el codigo \"%i\"\n", codigoMateria);
				if ( ! impSiNo("Desea reintentar?")) return NULL;
				codigoMateria = 0;
			}
		} while ( !codigoMateria );

		do {
			// solicitamos el ano de la Curso
			printf("A%co que representa este curso: ", 164);
			scanf("%hu%*c", &ano);
			if ( ano < 1970) printf("El a%co introducido es invalido, introduzca otro\n", 164);
		} while ( ano < 1970 );

		// para este punto, el año y el codigo de la materia son validos, asi que podemos generar el codigo del curso
		codigoCurso = genCodigoCurso(ano, codigoMateria);
		existe = obtenerCursoPorCodigo(Cur, codigoCurso);
		if (existe) {
			printf("Un curso con esas caracteristicas ya existe (Codigo %d)\n", existe->codigo);
			if ( ! impSiNo("Desea reintentar?")) return NULL;
		}
	} while (existe);
	// podemos guardar los datos
	C->ano = ano;
	C->codMat = codigoMateria;
	C->codigo = codigoCurso;

	// solicitamos el numero de lapso que ocupa la Curso
	printf("Numero de lapso: ");
	scanf("%hu%*c", &(C->lapso));

	do {
		// solicitamos el horario en el que se debe estar para cursar la Curso
		impMenu("Horario de este curso", 3, "Matutino", "Vespertino", "Nocturno");
		scanf("%d%*c", &horario);
		if ( ( horario < 1  ) || ( horario > 3 ) ) printf("Opcion no reconocida, por favor seleccione una opcion valida\n");
	} while ( ( horario < 1 ) || ( horario > 3 ) );

	// para este punto el horario es valido, hacemos una conversion explicita
	C->horario = (Horario)(--horario);

	// inicializamos el proximo elemento de este Curso como nulo
	C->prox = NULL;

	// devolvemos

	
	return C;
}

void insertarCurso(Curso **P, Curso *C) {
	// como es insercion por cola, tenemos que volver nulo el proximo del elemento a insertar
	if ( C->prox ) C->prox = NULL;
	// si la cabeza es nulo, entonces asignamos el nuevo como cabeza
	if (!(*P)) {
		*P = C;
		InsertarIndCurso(C);
	}
	// si el siguiente es nulo, estamos en el ultimo elemento, insertemos
	else if (!(*P)->prox) {
		(*P)->prox = C;
		InsertarIndCurso(C);
	}
	// llamamos recursivamente si estamos en cualquier otro punto de la lista
	else
		insertarCurso(&(*P)->prox, C);
}

void modificarCurso(Curso **P) {
	// nada mas actuamos si no tenemos un puntero a nulo
	if (*P) {
		int opt = -1, codMat = -1, cursoInvalido = -1, codigo = -1;
		unsigned short ano = -1, horario = -1;
		char str[] = "Editar el a%co del Curso";
		Curso *existe = NULL;
		// salimos cuando la opcion sea 0
		do {
			// mostramos el encabezado
			impCabezado();
			printCurso(*P);
			sprintf(str, str, 164);
			printf("**NOTA: EL A%cO Y EL CODIGO DE LA MATERIA NO SE GUARDARAN HASTA QUE DECIDA SALIR**\n\n", 165);
			impMenu(
				"Estas son las opciones disponibles para los Cursos.\nMarque la opcion de acuerdo a la operacion que desea realizar",
				4,
				"Editar el Codigo de Materia",
				str,
				"Editar el numero de lapso",
				"Editar horario"
			);
			scanf("%i%*c", &opt);
			switch (opt) {
			case 0: break;
			case 1:
				printf("Introduzca el nuevo codigo de materia para este curso. Actual: %d: ", (*P)->codMat);
				do {
					scanf("%d%*c", &codMat);
					if ( ! obtenerMateriaPorCodigo( Mat, codMat ) ) {
						printf("No existe ninguna materia con ese codigo\nIntroduzca otro\n");
						codMat = 0;
					}
				} while ( !codMat );
				break;
			case 2:
				printf("Introduzca un nuevo a%co para este curso. Actual: %d: ", 164, (*P)->ano);
				scanf("%4hu%*c", &ano);
				break;
			case 3:
				printf("Introduzca el nuevo lapso para este curso. Actual: %d: ",  (*P)->lapso);
				scanf("%hu%*c", &((*P)->lapso));
				break;
			case 4:
				printf("Seleccione el nuevo turno de horario para este curso. Actual: %s\n", horStr((*P)->horario));
				impMenu("\0", 3, "Matutino", "Vespertino", "Nocturno");
				do {
					scanf("%hu%*c", &horario);
					if ( (horario < 1) || (horario > 3) ) printf("Opcion no reconocida, seleccione un horario valido\n");
				} while ( (horario < 1) || (horario > 3) );
				(*P)->horario = (Horario)(--horario);
				break;
			default:
				printf("Opcion no reconocida. Vuelva a intentar\n");
			}
			if ( ano != -1 || codMat != -1 ) {
				if ( ano == -1 ) ano = (*P)->ano;
				if ( codMat == -1 ) codMat = (*P)->codMat;
				codigo = genCodigoCurso( ano, codMat );
				existe = obtenerCursoPorCodigo(Cur, codigo);
				if (existe) {
					printf("Ya existe un curso de la materia %s en el a%co %d. Por favor verifique los datos e intente nuevamente\n", obtenerMateriaPorCodigo(Mat, existe->codMat)->nombre, 164, existe->ano);
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
		if (impSiNo("Seguro que desea eliminar el curso?")) {
			removerIndCurso(del);
			delete del;
		}
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
			if (impSiNo("Seguro que desea eliminar el curso?")) {
				removerIndCurso(del);
				delete del;
			}
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
	impCabezado();
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
		if ((T->codMat) == Codigo)
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

CursosY *ubicarIndiceAnual( unsigned short Ano){
	CursosY *T = IndCurso;
	while (T){
		if ((T->ano) == Ano)
			return T;
		else {T = T->prox;}
	}
	return NULL;
}

void InsertarCursosS(CursosS** Cab, Curso *Agregar){
	CursosS *P = new CursosS;
		P->curso = Agregar;
		P->alumnos = NULL;
		P->prox = NULL;
	if (!*Cab) *Cab = P;
	else{ 
		CursosS *T = *Cab;	
		while (T->prox){
			// prevencion de repetidos en el indice (repetidos causados por la recursividad ups)
			if (T->curso->codigo == Agregar->codigo) return;
			T = T->prox;
		}
		T->prox = P;
	}
}

CursosY *CrearCursosY(unsigned short ano) {
	CursosY *T = new CursosY;
	CursosY *Puntero = IndCurso;
	T->ano = ano;
	T->cursosDictados = NULL;
	T->prox = NULL;

	if (!(IndCurso)) {
		IndCurso = T;
		return T;
	}
	else {
		if ((T->ano) > (Puntero->ano)){
			T->prox = Puntero;
			IndCurso = T;
			return T;
		}
		else {
			while (Puntero) {
				if (!(Puntero->prox)){
					Puntero->prox = T;
					return T;
				}
				else if (((Puntero->prox)->ano) < (T->ano)){
					T->prox = Puntero->prox;
					Puntero->prox = T;
					return T;
				    }
				else{Puntero = Puntero->prox;} 
	        }
        }
	  }
	// no deberia pasar
	return NULL;
}

void InsertarIndCurso(Curso *Agregado){ 
	CursosY *Existe = NULL;
	// Se verifica si el año se encuentra en el indice para introducirlo a la lista correspondiente, sino se creara una nueva lista del año correspondiente
	Existe = ubicarIndiceAnual(Agregado->ano);
	if  (!(Existe))
		Existe = CrearCursosY(Agregado->ano);
	InsertarCursosS(&(Existe->cursosDictados),Agregado);	
}

void MostrarNotaAlumno(CursosS *Curso,CursosA *AlumnoBuscado){
	Materia *MateriaDeseada = NULL;
	MateriaDeseada =  obtenerMateriaPorCodigo(Mat,(Curso->curso)->codMat);
	printf("\n Nombre de la materia: %s \n",MateriaDeseada->nombre);
	printf("\n La nota del alumno en la materia es: %05.2f \n",AlumnoBuscado->nota);
	printCurso(Curso->curso,1);
}

void ImprimirRegistroAlumnoCursosS(CursosS *Cab,int Cedula){
	CursosS *T= Cab;
	CursosA *AlumnoBuscado = NULL;
	while (T){
		AlumnoBuscado = EstaInscrito(T->alumnos,Cedula);
		if (AlumnoBuscado)
			MostrarNotaAlumno(T,AlumnoBuscado);
		T = T->prox;
	}
	system("Pause");
}

CursosS *BuscarPrimeraCoincidencia(CursosS *Cab,int Cedula){
	CursosS *T = Cab;
	CursosA *AlumnoBuscado = NULL;
	while (T){
		AlumnoBuscado = EstaInscrito(T->alumnos,Cedula);
		if (AlumnoBuscado) return T;
		T = T->prox;
	}
	return NULL;
}

void ImprimirRecordAcademicoAlumno(){
	CursosY *T = IndCurso;
	CursosS *Puntero = NULL;
	short existe = 0;
	int Cedula = 0;
	printf("\nIntroduzca el numero de cedula del alumno a buscar\n");
	scanf("%i%*c",&Cedula);
	while (T){
		Puntero = BuscarPrimeraCoincidencia(T->cursosDictados,Cedula);
		if (Puntero) existe = 1;
		if (Puntero){
			printf("\n Cursos del %i: \n",T->ano);
			ImprimirRegistroAlumnoCursosS(T->cursosDictados,Cedula);
		}
		T = T->prox;
	}
	if (!existe){
		printf("\nEl alumno no esta inscrito en ningun curso registrado\n");
		system("Pause");
	}
}

void InsertarListaCursosScola(CursosS **Cab,CursosS *Nuevo){
	Nuevo->prox = NULL;
	if (!(*Cab)) *Cab =Nuevo;
	else{
		Nuevo->prox = *Cab;
		*Cab = Nuevo;
	}
}

void InsertarListaCursosScabeza(CursosS **Cab,CursosS *Nuevo){
	Nuevo->prox = NULL;
	CursosS *T = *Cab;
	if (!(*Cab)) *Cab =Nuevo;
	else{
		while (T->prox) {
			// prevencion de repetidos
			if (T->curso->codigo == Nuevo->curso->codigo) return;
			T = T->prox;
		}
		T->prox = Nuevo;
	}
}


void BuscarCursosPorNombre(){
	char Nombre[30];
	impCabezado();
	printf("Introduzca el nombre de la materia que se desea buscar\n");
	scanf("%s%*c",Nombre);
	BuscarCursos(Nombre);
	system("Pause");
}

CursosS *obtenerCursos(CursosS *Cab,int codigo){
	CursosS *T = Cab;
	while (T){
		if (((T->curso)->codMat)==codigo) return T;
		T = T->prox;
	}
	return NULL;
}

void BuscarRepeticionesDeCursos(){
	int Cedula = 0;
	Alumno *AlumnoBuscado;
	Materia *MateriaBuscada;
	int Codigo = 0;
	int SN = 1,existe = 0;
	CursosS *Curso = NULL;
	CursosY *T = IndCurso;
	do
	{
		printf("\nIntroduzca la cedula del alumno al cual desea consultar\n");
		scanf("%i%*c",&Cedula);
		AlumnoBuscado = obtenerAlumnoPorCedula(Al,Cedula);
		if (!AlumnoBuscado){
			SN = impSiNo("El alumno no existe, ¿Desea introducir otra cedula?");
			if (!SN) return;
			}
	} while (!AlumnoBuscado);
	do
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
		Curso = obtenerCursos(T->cursosDictados,Codigo);

		if ((Curso) && (BuscarAlumnoCursosA(Curso->alumnos,AlumnoBuscado))){
			printf("\nCurso del a%co: %hu\n", 164, T->ano);
			printCurso(Curso->curso,detalle());
			existe = 1;
		}
		T = T->prox;
	}
	if (!existe){
		printf("\nEl alumno no ha cursado esta materia ninguna vez\n");
		system("Pause");
	}
	system("pause");
}

CursosA *ultimoCursosA(CursosA *listado) {
	if (listado)
		return listado->prox ? ultimoCursosA(listado->prox) : listado;
	return NULL;
}

CursosA *crearCursosA(Alumno *A) {
	if (A) {
		CursosA *indice = new CursosA;
		indice->alumno = A;
		indice->estatus = 'N';
		indice->nota = -1.0f;
		indice->prox = NULL;

		return indice;
	}

	return NULL;

}

int insertarCursosA(CursosA **listado, CursosA *indice) {
	if (*listado) {
		// si las cedulas coinciden, no podemos insertar
		if ((*listado)->alumno->cedula == indice->alumno->cedula)
			return 0;
		// llamamos recursivamente hasta el ultimo elemento
		if ((*listado)->prox)
			return insertarCursosA(&((*listado)->prox), indice);
		// si llegamos hasta aqui, estamos en el ultimo elemento, insertamos como si nada
		(*listado)->prox = indice;
		return 1;
	}

	// si no hay listado, nuestro indice es el primero
	(*listado) = indice;
	return 1;
}

CursosA *ubicarListaAlumnos(Curso *C) {
	if (C) {
		CursosS *cursos = ubicarIndiceAnual(C->ano)->cursosDictados;
		while (cursos->prox) {
			if (cursos->curso == C) break;
			cursos = cursos->prox;
		}

		return cursos->alumnos;
	}	

	return NULL;
}

void removerIndCurso(Curso *C) {
	// actuamos si tenemos un curso
	if (C) {
		// Cabeza del listado de cursos
		CursosS **cab = &( ubicarIndiceAnual( C->ano )->cursosDictados ),
			// Curso a eliminar del indice
				*del = NULL,
			// Copia de la cabeza
				*copia = *cab;

		// Listado de alumnos del curso
		CursosA *alumnos = NULL;

		// evaluamos si tenemos que eliminar la cabeza
		if ((*cab)->curso == C) {
			del = *cab;
			*cab = del->prox;
		}
		else {
			// sino, iteramos usando la copia
			copia = *cab;
			while (copia->prox)
				if (copia->prox->curso == C) {
					del = copia->prox;
					copia->prox = del->prox;
				}
		}

		// guardamos la lista de alumnos 
		alumnos = del->alumnos;
		while (alumnos) {
			// por cada alumno le eliminamos de su lista de materias el curso
			removerMateriaDeListado(alumnos->alumno, C);
			alumnos = alumnos->prox;
		}
		// finalmente, eliminamos del indice
		delete del;
	}	
}

CursosS *ObtenerCursosS(Curso *Buscado){
	CursosY *T = IndCurso;
	CursosS *Lista;
	while (T){
		Lista = T->cursosDictados;
		while(Lista){
			if (Lista->curso == Buscado) return Lista;
			Lista = Lista->prox;
		}
		T = T->prox;
	}
	return NULL;
}

void DatosDelCurso(void){
	int Codigo = 0;
	Curso *CursoBuscado; 
	CursosS *Encontrado;
	PromedioCurso *NuevoProm = new PromedioCurso;
	NuevoProm->Aprobados = 0;
	NuevoProm->Reprobados = 0;
	NuevoProm->Retirados = 0;
	NuevoProm->promedio = 0;
	NuevoProm->CantidadAlumnos = 0;
	impCabezado();
	int salir = 0;
	do{
		printf("\nIntroduzca el codigo del curso\n");
		scanf("%i%*c",&Codigo);
		CursoBuscado = obtenerCursoPorCodigo(Cur,Codigo);
		if (!CursoBuscado)
			salir = impSiNo("El curso que busca no existe, ¿Desea intentarlo de nuevo?");
	} while(salir);
	if (CursoBuscado){
	Encontrado = ObtenerCursosS(CursoBuscado);
	printCurso(CursoBuscado,1);
	CalcularAlumnos(Encontrado->alumnos,&NuevoProm);
	printf("\nLa cantidad de alumnos inscritos en el curso es de: %i \nLa cantidad de aprobados es: %i \nLa cantidad de repobados es: %i \nLa cantidad de retirados es: %i\n",(NuevoProm->CantidadAlumnos),(NuevoProm->Aprobados),(NuevoProm->Reprobados),(NuevoProm->Retirados));
	system("Pause");
	}
}

Curso *BuscarCursoPorCodigoYano(int Codigo,int Ano){
	Curso *T = Cur;
	while (T){
		if ((T->codMat == Codigo) && (T->ano ==Ano)) return T;
		T = T->prox;
	}
	return NULL;
}

CursosA *ubicarAlumnoEnCurso(Curso *C, Alumno *A) {
	if (C && A) {
		CursosA *lista = ubicarListaAlumnos(C);
		while (lista->prox) {
			if (lista->alumno->cedula == A->cedula) break;
			lista = lista->prox;
		}

		return lista;
	}
	return NULL;
}

CursosS *ubicarCursosEnAno(unsigned short y) {
	CursosY *anual = ubicarIndiceAnual(y);
	if (anual) 
		return anual->cursosDictados;
	return NULL;
}