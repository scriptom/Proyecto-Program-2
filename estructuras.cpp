#ifndef ESTRUCTURAS
#define ESTRUCTURAS

/* Estructuras base */

// INICIO DECLARACION DE ENUMERADOS
typedef enum Horario {
	Matutino, Vespertino, Nocturno
}Horario;

// FIN DECLARACION DE ENUMERADOS
//--------------------------------------
// INICIO DECLARACION DE ESTRUCTURAS BASE

typedef struct Fecha {
	unsigned short dia;
	unsigned short mes;
	unsigned short ano;
}Fecha;

typedef struct Alumno {
	char nombre[15];
	char apellido[15];
	int cedula;
	char direccion[255];
	char telefono[15];
	Fecha fechaNac;
	char correo[30];
	Alumno *prox;
}Alumno;

typedef struct Materia {
	int codigo;
	char nombre[15];
	char area[20];
	char creditos;
	char semestre;
	Materia *prox;
}Materia;

typedef struct Curso {
	int codigo;
	unsigned short ano;
	char lapso;
	int codMat;
	Horario horario;
	Curso *prox;
}Curso;
	
// FIN DECLARACION DE ESTRUCTURAS BASE
//--------------------------------------
// INICIO DECLARACION DE INDICES


typedef struct AlumN {
	char estatus;
	char nota;
	Curso *curso;
	AlumN *prox;
}AlumN;

typedef struct AlumC {
	Alumno *alumno;
	AlumC *prox;
	AlumN *materias;
}AlumC;

typedef struct CursosA {
	char nota;
	char estatus;
	Alumno* alumno;
	CursosA* prox;
}CursosA;

typedef struct CursosS {
	Curso* curso;
	CursosS* prox;
	CursosA* alumnos;
}CursosS;

typedef struct CursosY {
	unsigned short ano;
	CursosS *cursosDictados;
	CursosY *prox;
}CursosY;

#endif
