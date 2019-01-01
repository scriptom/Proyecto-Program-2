#ifndef MATERIAS_H
#define MATERIAS_H

#include "estructuras.cpp"

/*
	Lista global de Materias, para tener acceso a todas en cualquier punto de ejecucion
*/
extern Materia* Mat;

/*
	Muestra la informacion de una Materia dada en pantalla, en un formato legible. Opcionalmente, se puede pasar un flag para una vista detallada
	Parametros:
		Materia *M  : La materia a mostrar en pantalla
		int detalle : Flag que determina si se muestra todo el detalle de la materia o solo informacion basica
	La informacion basica consta de solo el codigo de la materia y el nombre
	La informacion detallada muestra:
	- Nombre
	- Codigo
	- Area
	- Creditos
	- Semestre
*/
void printMateria(Materia *, int = 1);

/*
	Muestra en pantalla todas las MAterias de un listado dado, mediante recursividad. Adicionalmente hay un parametro para
	definir el nivel de detalle de impresion (Esta funcion usa printMateria)
	Parametros:
		Materia *M  : La cabeza de la lista a imprimir
		int detalle : El nivel de detalle de impresion, el cual sera pasado a printMateria (ver printMateria para mas informacion)
*/
void printListaMateria(Materia *, int = 0);

/*
	Crea una nueva materia. Esta funcion se encarga de plantear una especie de menu y de recibir las entradas
	Retorno: Materia * : La nueva materia creada
*/
Materia *crearMateria();

/*
	Inserta una materia dada en un listado dado
	El proceso de insercion de una materia es simple insercion por cola.
	Parametros:
		Materia **P : Listado de materias destino
		Materia *M  : Materia a ser insertada en la lista
*/
void insertarMateria(Materia **, Materia *);

/*
	Extrae recursivamente las materias de un archivo y las inserta en un listado dado
	Parametros:
		Materia **P : Listado donde insertar las materias extraidas
		FILE * f  : Archivo binario donde se encuentran los registros de materias
*/
void extraerMateriasDesdeArchivo(Materia **, FILE *);

/*
	Extrae una materia como un elemento <b>individual</b>, es decir, su prox siempre es NULL
	Util para crear listas paralelas sin tocar la global
	Parametros:
		Materia *M  : Lista de donde buscar una materia
		int codigo : Codigo de materia a buscar
*/
Materia *extraerMateria(Materia *, int);

/*
	Somete una instancia de una Materia a ser posiblemente modificada. Esta funcion se encarga del menu de modificacion y y procesar la entrada
	Parametros:
		Materia **M : La Materia a ser (posiblemente) modificada
*/
void modificarMateria(Materia **);

/*
	Elimina una Materia de un listado de Materias dado
	Parametros:
		Materia **M : La lista de materias donde buscar
		int codigo  : El codigo de la materia a eliminar
*/
void elimMateria(Materia **, int);

/*
	Obtiene una Materia mediante un codigo dado
	Parametros:
		Materia *M : La lista de Materia de donde buscar
		int codigo : El codigo de Materia a bsucar
	Retorno: Materia * : Posiblemente, una Materia con el codigo dado
*/
Materia *obtenerMateriaPorCodigo(Materia *, int);
/*
	Obtiene una materia mediante la eleccion del usuario
	Parametros:
		Materia *M : La lista de materias donde buscar
		int n : La cantidad de veces que tiene que moverse en la lista para llegar a la posicion deseada
*/
Materia *obtenerEnesimaMateria(Materia, int);

/*
	Obtiene la cantidad de elementos que se tiene en una lista de materias
	Parametros:
		Materias *h: La lista de materias que se va a contar
*/
int cantidadMaterias(Materia *);
/*
	Obtiene el codigo de una materia usando el nombre de la materia
	Parametros:
		Materia * P: La lista de materias en donde se va a buscar 
		Char* Nombre: Es la cadena de chars que se utilizara como base para buscar el codigo de la materia deseada  
*/
int ObtenerCodigoMateria(Materia *,char*);

/*
	Vacia una lista de materias
	Parametros:
		Materia **P : La lista de materias a vaciar
*/
void vaciarListaMaterias(Materia**);

#endif