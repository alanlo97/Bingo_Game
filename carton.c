#include <stdio.h>
#include <stdlib.h>

#include "carton.h"
#include "funciones.h"

#define LINEA 3
#define COLUM 5
#define BOLSA 90

#include "carton.h"

enum busqueda{no_encontrado = -1, salir, col_lleno = 2, lin_lleno, bin_lleno};

struct CartonE{

    int carton[LINEA*COLUM];

};

//---------------CONSTRUCTOR------------------

Carton cargarCartonEnCero(){

    Carton c = malloc(sizeof(struct CartonE));

    for(int i=0; i<LINEA*COLUM; i++){
        c->carton[i] = 0;
    }

    return c;
};

//---------------DESTRUCTOR-------------------

void destruirCarton(Carton c){

    free(c);
}

//---------------MOSTRAR----------------------

void mostrarCarton(Carton cart){

    int contar = 0;

    for(int l=0; l<LINEA; l++){
        for(int c=0; c<COLUM; c++){

            printf("| %d |", cart->carton[contar]);
            contar++;
        }
        printf("\n\n");
      }
}

//---------------GETS-------------------------

int * getCarton(Carton c){
    return c->carton;
};
int getNumEnPos(Carton c, int pos){
    return c->carton[pos];
}

//---------------SETS-------------------------

void setCarton(Carton c, int nuevoCarton[LINEA*COLUM]){

    for(int i=0; i<LINEA*COLUM; i++){
        c->carton[i] = nuevoCarton[i];
    }
}
void setNumEnPos(Carton c, int pos, int nuevoNum){
    c->carton[pos] = nuevoNum;
}
