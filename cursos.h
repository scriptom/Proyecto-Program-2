#ifndef CURSOS_H
#define CURSOS_H

#include "estructuras.cpp";
/* Declaraciones relacionados con Cursos */

/*
	Variable global, a ser utilizada a lo largo del programa como la lista de Cursos
*/
extern Curso *Cur;

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
	Retorno: int : el nuevo codigo
*/
int genCodigoCurso(int, int);
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
*/
CursosY *obtenerPunteroInd( unsigned short);

/*
	
*/
void InsertarCursosS(CursosS **,Curso*);

CursosY *CrearCursosY(unsigned short);

/*
	Muestra la nota  o estado de un alumno en un curso
	Parametros:
		CursosS *Curso: Es el puntero del indice de Cursos donde se encuentra dicho alumno inscrito para la impresion de la informacion del curso
*/
void MostrarNotaAlumno(CursosS*)

#endif