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
	char nombre[30];
	char area[20];
	unsigned short creditos;
	unsigned short semestre;
	Materia *prox;
}Materia;

typedef struct PromedioCurso {
	int CantidadAlumnos;
	int Aprobados;
	int Reprobados;
	int Retirados;
	float promedio;
}PromedioCurso;

typedef struct Curso {
	int codigo;
	unsigned short ano;
	unsigned short lapso;
	int codMat;
	Horario horario;
	Curso *prox;
}Curso;


// FIN DECLARACION DE ESTRUCTURAS BASE
//--------------------------------------
// INICIO DECLARACION DE INDICES


typedef struct AlumN {
	char estatus;
	float nota;
	Curso *curso;
	AlumN *prox;
}AlumN;

typedef struct AlumC {
	Alumno *alumno;
	AlumC *prox;
	AlumN *materias;
}AlumC;

typedef struct CursosA {
	float nota;
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

typedef struct ArchivoNotas {
	int cedula;
	int codigoCurso;
	float nota;
	char estatus;
}ArchivoNotas;

#endif
