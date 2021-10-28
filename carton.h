#ifndef CARTON_H_INCLUDED
#define CARTON_H_INCLUDED

#define LINEA 3
#define COLUM 5

struct CartonE;

typedef struct CartonE * Carton;

//-----------------------Constructor
Carton cargarCartonEnCero();

//-----------------------Destructor
void destruirCarton(Carton c);

//-----------------------Mostrar
void mostrarCarton(Carton c);

//-----------------------Gets
int * getCarton(Carton c);
int getNumEnPos(Carton c, int pos);

//-----------------------Sets
void setMatriz(Carton c, int nuevaMatriz[LINEA*COLUM]);
void setNumEnPos(Carton c, int pos, int nuevoNum);


#endif // CARTON_H_INCLUDED
