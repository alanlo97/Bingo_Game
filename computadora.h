#ifndef COMPUTADORA_H_INCLUDED
#define COMPUTADORA_H_INCLUDED

#include "carton.h"
#include "puntaje.h"

struct ComputadoraE;

typedef struct ComputadoraE * Computadora;

//-----------------------Constructor
Computadora cargarCPU();

//-----------------------Destructor
void destruirCPU(Computadora c);

//-----------------------Mostrar
void mostrarComputadora(Computadora c);

//-----------------------Gets
Puntaje getPuntajeCPU(Computadora c);
Carton getCartonCPU(Computadora c, int pos);

//-----------------------Sets
void setPuntajeCPU(Computadora c, Puntaje nuevoPuntaje);
void setCartonCPU(Computadora c, Carton nuevoCarton, int pos);




#endif // COMPUTADORA_H_INCLUDED
