#ifndef ALUMNOS_H
#define ALUMNOS_H

#include <stdio.h>
#include "estructuras.cpp"
/* Declaraciones relacionados con alumnos */

/*
	Variable global, a ser utilizada a lo largo del programa como la lista de alumnos
*/
extern Alumno *Al;

 /*
	Indice global de alumnos
 */
extern AlumC *IndAlumno;

/*
	Crea un nuevo puntero a Alumno, se encarga de una vez de mostrar las opciones y recibir las entradas
	Retorno: Alumno * : El nuevo alumno creado
*/
Alumno *crearAlumno(void);

/*
	Extrae un alumno como un elemento <b>individual</b>, es decir, su prox siempre es NULL
	Util para crear listas paralelas sin tocar la global
	Parametros: 
		Alumno *A  : Lista de donde buscar un alumno
		int cedula : Cedula a buscar
*/
Alumno *extraerAlumno(Alumno *, int);

/*
	Utilidad para mostrar los datos de un Alumno en pantalla, mediante un formato definido
	Parametros: 
		Alumno *A   : Un alumno cuyos datos quieren ser mostrados en pantalla
		int detalle : Flag para determinar si se imprimen todos los datos o solamente el nombre + cedula (prendido por defecto)
	Si detalle esta prendido, se muestra:
	- Nombre completo
	- Cedula
	- Fecha Nacimiento
	- Correo
	- Direccion
*/
void printAlumno(Alumno *, int = 1);

/*
	Utilidad para imprimir de manera recursiva todos los alumnos de un listado (Usa printAlumno)
	Parametros:
		Alumno *A   : La cabeza de una lista de alumnos
		int detalle : Flag para especificar si hay que imprimir a detalle (vease printAlumno para mas info)
*/
void printListaAlumno(Alumno *, int = 0);

/*
	Crear una nueva instancia de Fecha. Esta funcion se encarga de una vez de mostrar las opciones en pantalla, 
	y de recibir las entradas
	Retorno: Fecha : El struct de Fecha creado
*/
Fecha crearFecha(void);

/*
	Inserta un Alumno en una lista de Alumnos. La insercion se hace siempre ordenadamente, siendo el dsicriminante el
	numero de cedula del Alumno
	Parametros:
		Alumno **P : La lista de Alumnos destino
		Alumno *A  : El Alumno a insertar en P
	
*/
void insertarAlumno(Alumno **, Alumno *);

/*
	Extrae recursivamente los alumnos de un archivo y los inserta en un listado dado
	Parametros:
		Alumno **P : Listado donde insertar los alumnos extraidos
		FILE * f   : Archivo binario donde se encuentran los registros de alumnos
*/
void extraerAlumnosDesdeArchivo(Alumno **, FILE *);

/*
	Devuelve la cantidad de Alumnos que hay en un listado de manera recursiva
	Parametros:
		Alumno *A : El alumno actual de la lista
	Retorno: int : Cantidad de alumnos que pasaron por la funcion
		
*/
int cantidadAlumnos(Alumno *);

/*
	Obtener un puntero a un alumno de un listado dado, que posea una cedula dada, de manera recursiva
	Parametros:
		Alumno *A  : Un listado de Alumnos donde buscar
		int cedula : El numero de cedula a buscar en la lista 
	Retorno: Alumno * : Puntero al alumno encontrado (NULL si no existe)
*/
Alumno *obtenerAlumnoPorCedula(Alumno *, int);

/*
	Obtener alumnos por nombre. Se devuelve un listado de los alumnos cuyo campo de nombre sea igual o semejante al
	pasado por el nombre
	Parametros:
		Alumno *P    : Lista de alumnos donde buscar
		char *nombre : String con el nombre a buscar (solo busca por nombre, no por apellido)
	Retorno: Alumno * : Listado de coincidencias de alumnos (NULL si no existen coincidencias)
 */
Alumno *obtenerAlumnosPorNombre(Alumno *, char *);

/*
	Somete a un alumno a la posible modificacion de sus datos. Esta funcion se encarga del menu de modificacion y de
	hacer las modificaciones pertinentes. La unica opcion que no se puede modificar es la cedula del alumno (ya que romperia el orden)
	Parametros:
		Alumno **P : Direccion de memoria de un alumno que posiblemente sea modificado
*/
void modificarAlumno(Alumno **);

/*
	Elimina un alumno de una lista, usando como criterio su numero de cedula
	Parametros:
		Alumno **P : Listado de alumnos, pasado por referencia debido a que la cabeza se podria mover
		int cedula : Numero de cedula del alumno, criterio a usar en la busqueda
*/
void elimAlumno(Alumno **, int);

/*
	Peque�a funcion para consultar rapidamente los datos de un alumno [Posiblemente se elimine por ser tan similar con obtenerAlumnoPorCedula]	
	Parametros:
		Alumno **P : Listado de alumno donde buscar. Sera pasado a obtenerAlumnoPorCedula
		int cedula : La cedula del alumno a buscar. Sera pasado a obtenerAlumnoPorCedula
*/
void consultarAlumno(Alumno **, int);

/*
	Vacia una lista de alumnos
	Parametros:
		Alumno **P : La lista de alumnos a vaciar
*/
void vaciarListaAlumnos(Alumno**);
/*
	Verifica si un alumno especifico se encuentra inscrito en un curso utilizando la cedula
	Parametros:
		CursosA *Puntero: Es la lista de alumnos en la cual se buscara
		Int Cedula: Es la cedula que se utilizara para la busqueda
*/
CursosA *EstaInscrito(CursosA*,int);
 

/*
	Inscribe un alumno en un curso
	Parametros:
		Alumno *A : Alumno a inscribir
		Curso *C  : Curso donde inscribir
	Retorno: int : Si hubo exito en la inscripcion devuelve 1, 0 en caso contrario
*/
int inscribirEnCurso(Alumno *, Curso *);

/*
	Busca todos los alumnos cuyo nombre coincida parcial o totalmente con el buscado e imprime su nombre y su cedula
*/
void BuscarAlumnos(void);

/*
	Crear el indice de alumnos
	Parametros:
		Alumno *A : Alumno a ser insertado al indice

	Retorno : AlumC *: Indice de alumno creado
*/
AlumC *crearIndiceAl(Alumno *);

/*
	Inserta un alumno al indice global
*/
void insertarAlumC(AlumC*);

/*
	Busca a un alumno en una lista de CursosA
*/
int BuscarAlumnoCursosA(CursosA *,Alumno*);

/*
	Agrega una materia (en realidad es un curso) al listado de materias vistas por un alumno
	Parametros:
		Alumno *A : El Alumno a quien se le va a agregar la materia
		Curso *C  : El Curso que se va a agregar a la lista del Alumno

*/
void agregarMateriaAAlumno(Alumno *, Curso *);

/*
	Crea un registro en el indice de materias de alumno
	Parametro:
		Curso *C: Materia correspondiente
*/
AlumN *crearAlumN(Curso *);

/*
	Inserta un nodo de materias cursadas (AlumN) en un listado dado
	Parametros:
		AlumN **listado : El listado de materias original
		AlumN *materia : La materia a ser ingresada en la lista
*/
void insertarAlumN(AlumN**, AlumN*);

/*
	Pone a un alumno en un estado de modificacion de nota
	Parametros:
		Alumno *A : Alumno cuya nota sera modificada
		Curso *C : Curso donde la nota sera modificada
*/
void modificarNotaAlumno(Alumno *, Curso *);

/*
	Ubica y devuelve la instancia de una materia dentro del indice de alumnos
	Parametros:
		Curso *C  : Curso donde esta el alumno inscrito
		Alumno *A : Alumno cuyos datos se quieren
	Retorno : AlumN * : El indice de materias de alumno relevante
*/
AlumN *ubicarMateriaAlumno(Curso *, Alumno *);

/*
	Ubica y devuelve la instancia de un alumno en el indice
	Parametros:
		Alumno *A : Alumno a ubicar en el indice
	Retorno: AlumC * : Indice del alumno ubicado
*/
AlumC *ubicarAlumno(Alumno *);

#endif