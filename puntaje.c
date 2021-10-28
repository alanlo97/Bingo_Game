#include <stdio.h>
#include <stdlib.h>

#include "carton.h"
#include "funciones.h"
#include "puntaje.h"

#define LINEA 3
#define COLUM 5
#define BOLSA 90

enum busqueda{no_encontrado = -1, salir, col_lleno = 2, lin_lleno, bin_lleno};

struct PuntajeE{

    int linea;
    int columna;
    int bingo;
    float puntajeTotal;

};

//---------------CONSTRUCTOR------------------

Puntaje cargarPuntajeEnCero(){

    Puntaje p = malloc(sizeof(struct PuntajeE));

    p->bingo = 0;
    p->columna = 0;
    p->linea = 0;
    p->puntajeTotal = no_encontrado;

    return p;

};

//---------------DESTRUCTOR-------------------

void destruirPuntaje(Puntaje p){

    free(p);

}

//---------------MOSTRAR----------------------

void mostrarPuntaje(Puntaje p){

    printf("BINGO: %d\n", p->bingo);
    printf("COLUMNA: %d\n", p->columna);
    printf("LINEA: %d\n", p->linea);
    printf("PUNTOS TOTALES: %.2f\n", p->puntajeTotal);

}

//---------------GETS-------------------------

int getBingo(Puntaje p){
    return p->bingo;
};
int getColumna(Puntaje p){
    return p->columna;
};
int getLinea(Puntaje p){
    return p->linea;
};
float getPuntajeTotal(Puntaje p){
    return p->puntajeTotal;
};

//---------------SETS-------------------------

void setBingo(Puntaje p, int nuevoBingo){
    p->bingo = nuevoBingo;
}
void setColumna(Puntaje p, int nuevaColumna){
    p->columna = nuevaColumna;
}
void setLinea(Puntaje p, int nuevaLinea){
    p->linea = nuevaLinea;
}
void setPuntajeTotal(Puntaje p, float nuevoPuntajeTotal){
    p->puntajeTotal = nuevoPuntajeTotal;
}
