#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "carton.h"
#include "puntaje.h"
#include "computadora.h"


struct JugadorE;

typedef struct JugadorE * Jugador;

//-----------------------Constructor
Jugador inicializarJugador();
Jugador cargarJugador();
Jugador pasarDeArchivosAStruct(char c[], int n);

//-----------------------Destructor
void destruirJugador(Jugador j);

//-----------------------Mostrar
void mostrarJugador(Jugador j);

//-----------------------Gets
char * getNombre(Jugador j);
char * getApellido(Jugador j);
Puntaje getPuntajeJug(Jugador j);
int getDni(Jugador j);
Carton getCartonJug(Jugador j, int pos);

//-----------------------Sets
void setNombre(Jugador j, char nuevoNombre[20]);
void setApellido(Jugador j, char nuevoApellido[20]);
void setPuntajeJug(Jugador j, Puntaje nuevoPuntaje);
void setDni(Jugador j, int nuevoDni);
void setCartonJug(Jugador j, Carton nuevoCarton, int pos);


#endif // JUGADOR_H_INCLUDED


