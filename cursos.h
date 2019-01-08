#ifndef CURSOS_H
#define CURSOS_H

#include "estructuras.cpp"
/* Declaraciones relacionados con Cursos */

/*
	Variable global, a ser utilizada a lo largo del programa como la lista de Cursos
*/
extern Curso *Cur;

extern CursosY *IndCurso;

/*
	Variable global, a ser utilizada a lo largo del programa como el indice de cursos
*/
extern CursosY *IndCurso;

/*
	Devuelve la representacion en string de un horario (naturalmente un enum)
	Parametros:
		Horario h : El horario neto para buscar su equivalente string
	Retorno : const char * : La representacion imprimible de h 
*/
const char *horStr(Horario);

/*
	Crea un nuevo puntero a Curso, se encarga de una vez de mostrar las opciones y recibir las entradas
	Retorno: Curso * : El nuevo Curso creado
*/
Curso *crearCurso(void);

/*
	Utilidad para mostrar los datos de un Curso en pantalla, mediante un formato definido
	Parametros:
		Curso *C   : Un Curso cuyos datos quieren ser mostrados en pantalla
		int detalle : Flag para determinar si se imprimen todos los datos o solamente el nombre + codigo (prendido por defecto)
	Si detalle esta prendido, se muestra:
	- Nombre de la materia
	- Codigo
	- Año del curso
	- Lapso
	- Codigo de Materia
	- Horario de la materia
*/
void printCurso(Curso *, int = 1);

/*
	Utilidad para imprimir de manera recursiva todos los Cursos de un listado (Usa printCurso)
	Parametros:
		Curso *A   : La cabeza de una lista de Cursos
		int detalle : Flag para especificar si hay que imprimir a detalle (vease printCurso para mas info)
*/
void printListaCurso(Curso *, int = 0);

/*
	Inserta un Curso en una lista de Cursos. La insercion se hace siempre ordenadamente, siendo el dsicriminante el
	numero de cedula del Curso
	Parametros:
		Curso **P : La lista de Cursos destino
		Curso *C  : El Curso a insertar en P

*/
void insertarCurso(Curso **, Curso *);

/*
	Extrae un curso como un elemento <b>individual</b>, es decir, su prox siempre es NULL
	Util para crear listas paralelas sin tocar la global
	Parametros:
		Curso *C   : Lista de donde buscar un curso
		int cedula : Codigo de curso a buscar
*/
Curso *extraerCurso(Curso *, int);

/*
	Extrae recursivamente los cursos de un archivo y los inserta en un listado dado
	Parametros:
		Curso **P : Listado donde insertar los cursos extraidos
		FILE * f  : Archivo binario donde se encuentran los registros de cursos
*/
void extraerCursosDesdeArchivo(Curso **, FILE *);

/*
	Devuelve la cantidad de Cursos que hay en un listado de manera recursiva
	Parametros:
		Curso *C : El Curso actual de la lista
	Retorno: int : Cantidad de Cursos que pasaron por la funcion

*/
int cantidadCursos(Curso *);

/*
	Obtener un puntero a un Curso de un listado dado, que posea una cedula dada, de manera recursiva
	Parametros:
		Curso *C   : Un listado de Cursos donde buscar
		int codigo : El codigo de curso a buscar en la lista
	Retorno: Curso * : Puntero al Curso encontrado (NULL si no existe)
*/
Curso *obtenerCursoPorCodigo(Curso *, int);

/*
	Somete a un Curso a la posible modificacion de sus datos. Esta funcion se encarga del menu de modificacion y de
	hacer las modificaciones pertinentes. La unica opcion que no se puede modificar es la cedula del Curso (ya que romperia el orden)
	Parametros:
		Curso **P : Direccion de memoria de un Curso que posiblemente sea modificado
*/
void modificarCurso(Curso **);

/*
	Elimina un Curso de una lista, usando como criterio su numero de cedula
	Parametros:
		Curso **P : Listado de Cursos, pasado por referencia debido a que la cabeza se podria mover
		int cedula : Numero de cedula del Curso, criterio a usar en la busqueda
*/
void elimCurso(Curso **, int);

/*
	Genera el codigo de curso unico
	Parametros:
		int ano : El año del curso
		int cod : Codigo de la materia de este curso
		unsigned short lapso : Lapso del Curso en el año
	Retorno: int : el nuevo codigo
*/
int genCodigoCurso(int, int, unsigned short);
/*
	Obtiene e imprime una lista de los cursos de una materia en especifico 
	Parametros:
		char *NombreM : Nombre de la materia a buscar
*/
void BuscarCursos(char*);

/*
	Busca los cursos de una materia en especifico y los inserta en una lista auxiliar
	Parametros:
		int Codigo: Es el codigo de la materia que se utilizara como base para la busqueda
		Curso **C: Es la lista auxiliar en la que se insertaran los cursos que cumplan el requerimiento 
*/
void Buscar(int,Curso**);

/*
	Vacia una lista de cursos
	Parametros:
		Curso **P : La lista de cursos a vaciar
*/
void vaciarListaCursos(Curso**);

/*
	Inserta en la lista de indice de curso
	Parametros:
		Curso *Agregado: Es el curso que se agregara al indice
*/
void InsertarIndCurso(Curso *);
/*
	Verifica y devuelve el puntero que coincida con el año deseado de la lista de indice de cursos
	Parametros:
		Unsigned shot ano: Es el año que se desea buscar en el indice de cursos
*/
CursosY *ubicarIndiceAnual( unsigned short);

/*
	Agrega un curso a la lista de cursos de un año determinado
	Parametros:
		CursosS **Cab: Es la lista de cursos de un año especifico en donde se agregara el curso
		Curso *Agregar: Es el curso que se va a agregar
*/
void InsertarCursosS(CursosS **,Curso*);

/*
	Crea un nuevo año en la lista de indice de cursos para agregar los cursos que se dicten en dicho año
	Parametros:
		Unsigned short ano: Es el año que se va a agregar en el indice de cursos
*/
CursosY *CrearCursosY(unsigned short);

/*
	Muestra la nota  o estado de un alumno en un curso
	Parametros:
		CursosS *Curso: Es el puntero del indice de Cursos donde se encuentra dicho alumno inscrito para la impresion de la informacion del curso
		CursosA *AlumnoBuscado: Es el punto al registro del alumno donde se almacena la nota y el estado
*/
void MostrarNotaAlumno(CursosS*,CursosA*);

/*
	Recorre una lista de CursosS buscando si el alumno esta inscrito en ese curso para imprimir su record academico
	Parametros:
		CursosS *Cab: Es la cabeza de la lista en donde se buscara todas las coincidencias del alumno
		Int Cedula: Es la cedula que se utilizara para buscar al alumno;
*/
void ImprimirRegistroAlumnoCursosS(CursosS *,int);

/*
	Busca el primer curso en el que esta inscrito el alumno deseado, para verificar si estuvo inscrito en ese año academico
	Parametros:
		CursosS *Cab: Es la lista de Cursos que hubo en ese año
		Int Cedula: Es el alumno que se desea buscar
*/
CursosS *BuscarPrimeraCoincidencia(CursosS*,int);

/*
	Recorre todo el indice de cursos buscando si el alumno esta inscrito en almenos un curso de ese año, para imprimir su record academico
	Parametros:
	
*/
void ImprimirRecordAcademicoAlumno();

/*
	Busca usando el nombre de una materia, todos los cursos que sean de esa materia
*/
void BuscarCursosPorNombre(void);

/*
	Busca e imprime las veces que un alumno ha cursado una materia
*/
void BuscarRepeticionesDeCursos(void);

/*
	Inserta un CursosS en una lista de CursosS por cola
	Parametros:
		CursosS **Cab: La cabeza de la lista de cursosS
		CursosS *Nuevo: El cursosS que se desea ingresar
*/
void InsertarListaCursosScola(CursosS **,CursosS *);

/*
	Busca un curso por el codigo de la materia y el año
	Parametros:
		Int Codigo: Es el codigo de la materia a buscar
		Int Año: Es el año del curso a buscar
*/
Curso *BuscarCursoPorCodigoYano(int,int);

/*
	Inserta un CursosS en una lista de  por cabeza
	Parametros:
		CursosS **Cab: La cabeza de la lista de cursosS
		CursosS *Nuevo: El cursosS que se desea ingresar
*/
void InsertarListaCursosScabeza(CursosS **,CursosS *);

/*
	
*/
CursosS *obtenerCursos(CursosS *Cab,int codigo);

/*
	Crea una nueva entrada en el indice de cursos CursosA
	Parametros:
		Alumno * A : El Alumno a quien pertenece este indice
*/
CursosA *crearCursosA(Alumno *);

/*
	Devuelve el ultimo elemento de un indice de cursos CursosA
	Parametros:
		CursosA *listado : Listado de los alumnos del indice
*/
CursosA *ultimoCursosA(CursosA *);

/*
	Inserta un registro en un listado de CursosA dado
	Parametros:
		CursosA ** listado : El listado donde insertar
		CursosA * indice   : El indice a insertar
	Retorno : int : Regresa 1 si hibo exito al insertar, 0 en caso contrario
*/
int insertarCursosA(CursosA **, CursosA *);

/*
	Regresa el listado de alumnos de un curso dado
	Parametros:
		Curso *C : El cuya lista se va a retornar
	Retorno : CursosA * : La lista de alumnos
*/
CursosA *ubicarListaAlumnos(Curso *);

/*
	Ubica y devuelve el registro de un alumno en la lista de un curso
	Parametros:
		Curso *C  : El curso donde se buscara el alumno
		Alumno *A : El alumno a buscar en la lista del curso
	Retorno : CursosA* : El registro del alumno
*/
CursosA *ubicarAlumnoEnCurso(Curso *, Alumno *);

/*
	Ubica y devuelve la lista de cursos dictados en un año dado
	Parametros:
		unsigned short y : Año del curso
	Retorno : CursosS* Lista de cursos de dicho año
*/
CursosS *ubicarCursosEnAno(unsigned short);

/*
	Remueve un Curso dado del indice
	Parametros:
		Curso *C : El curso a remover
*/
void removerIndCurso(Curso *);

/*
	Imprime los datos de un curso especifico, la cantidad de alumos que lo cursan y la cantidad de aprobados, reprobados y retirados
*/
void DatosDelCurso(void);
/*
	Busca y devuelve un curso en el indice de cursos
	Parametro:
		Curso *Buscado: Es el curso que se desea encontrar
*/
CursosS *ObtenerCursosS(Curso *);

CursosS *extraerCursosS(CursosS *);

Curso *obtenerCursosDeMateria(Materia *);

#endif