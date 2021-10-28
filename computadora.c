#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "carton.h"
#include "puntaje.h"
#include "computadora.h"
#include "funciones.h"

enum busqueda{no_encontrado = -1, salir, col_lleno = 2, lin_lleno, bin_lleno};

struct ComputadoraE{

    Puntaje puntosCPU;
    Carton cartonesCPU[3];
};

//---------------CONSTRUCTOR------------------

Computadora cargarCPU(){

    Computadora c = malloc(sizeof(struct ComputadoraE));

    c->puntosCPU = cargarPuntajeEnCero();

    setPuntajeTotal(c->puntosCPU, 0);

    for(int i=0; i<3; i++){
        c->cartonesCPU[i] = cargarCartonEnCero();
    }

    return c;
};

//---------------DESTRUCTOR-------------------

void destruirCPU(Computadora c){

    free(c);

}

//---------------MOSTRAR----------------------

void mostrarComputadora(Computadora c){

    printf("PUNTAJE:\n");
    mostrarPuntaje(c->puntosCPU);

    for(int i=0; i<3; i++){
        mostrarCarton(c->cartonesCPU[i]);
    }
}

//---------------GETS-------------------------

Puntaje getPuntajeCPU(Computadora c){
    return c->puntosCPU;
};
Carton getCartonCPU(Computadora c, int pos){
    return c->cartonesCPU[pos];
};

//---------------SETS-------------------------

void setPuntajeCPU(Computadora c, Puntaje nuevoPuntaje){
    c->puntosCPU = nuevoPuntaje;
}
void setCartonCPU(Computadora c, Carton nuevoCarton, int pos){
    c->cartonesCPU[pos] = nuevoCarton;
}
