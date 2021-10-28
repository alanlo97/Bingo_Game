#ifndef PUNTAJE_H_INCLUDED
#define PUNTAJE_H_INCLUDED

struct PuntajeE;

typedef struct PuntajeE * Puntaje;

//-----------------------Constructor
Puntaje cargarPuntajeEnCero();

//-----------------------Destructor
void destruirPuntaje(Puntaje p);

//-----------------------Mostrar
void mostrarPuntaje(Puntaje p);

//-----------------------Gets
int getBingo(Puntaje p);
int getColumna(Puntaje p);
int getLinea(Puntaje p);
float getPuntajeTotal(Puntaje p);

//-----------------------Sets
void setBingo(Puntaje p, int nuevoBingo);
void setColumna(Puntaje p, int nuevaColumna);
void setLinea(Puntaje p, int nuevaLinea);
void setPuntajeTotal(Puntaje p, float nuevoPuntajeTotal);


#endif // PUNTAJE_H_INCLUDED
