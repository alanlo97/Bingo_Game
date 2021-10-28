#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "carton.h"
#include "puntaje.h"
#include "jugador.h"
#include "funciones.h"

#define LINEA 3
#define COLUM 5
#define BOLSA 90

enum busqueda{no_encontrado = -1, salir, col_lleno = 2, lin_lleno, bin_lleno};

struct JugadorE{

    char nombre[20];
    char apellido[20];
    int dni;

    Puntaje puntosJug;
    Carton cartones[3];
};

//---------------CONSTRUCTOR------------------

Jugador inicializarJugador(){

    Jugador j = malloc(sizeof(struct JugadorE));

    for(int i=0; i<3; i++){
        j->cartones[i] = cargarCartonEnCero();
    }

    j->puntosJug = cargarPuntajeEnCero();

    return j;
}

Jugador cargarJugador(){

    Jugador j = malloc(sizeof(struct JugadorE));

    char auxNombre[20]=" ";
    char auxApellido[20]=" ";

    printf("\nINGRESE NOMBRE\n\n");
    fflush(stdin);
    gets(auxNombre);
    strcpy(j->nombre, auxNombre);

    printf("\nINGRESE APELLIDO\n\n");
    fflush(stdin);
    gets(auxApellido);
    strcpy(j->apellido, auxApellido);

    printf("\nINGRESE SU DNI\n\n");
    scanf("%d", &j->dni);

    for(int i=0; i<3; i++){
        j->cartones[i] = cargarCartonEnCero();
        }

    j->puntosJug = cargarPuntajeEnCero();

    setPuntajeTotal(j->puntosJug, 0);

    return j;

};

Jugador pasarDeArchivosAStruct(char c[], int n){

    int pos1 = no_encontrado;
    int pos2 = no_encontrado;
    int pos3 = no_encontrado;

    char auxNombre[30] = " ";
    char auxApellido[30] = " ";
    char auxDni[30] = " ";
    char auxPuntaje[30] = " ";

    for(int i=0; i<n; i++){
        if(c[i] == ';'){
            pos1 = i;
            i = n;
        }
    }

    for(int i = pos1+1; i<n; i++){
        if(c[i] == ';'){
            pos2 = i;
            i = n;
        }
    }

    for(int i = pos2+1; i<n; i++){
        if(c[i] == ';'){
            pos3 = i;
            i = n;
        }
    }

    for(int i=0; i<pos1; i++){
        auxNombre[i] = c[i];
    }

    for(int i = pos1+1; i<pos2; i++){
        auxApellido[i-pos1-1] = c[i];
    }

    for(int i = pos2+1; i<pos3; i++){
        auxDni[i-pos2-1] = c[i];
    }

    for(int i = pos3+1; i<n; i++){
        auxPuntaje[i-pos3-1] = c[i];
    }

    Jugador j = inicializarJugador();

    strcpy(j->nombre, auxNombre);
    strcpy(j->apellido, auxApellido);
    j->dni = atoi(auxDni);
    setPuntajeTotal(j->puntosJug, atof(auxPuntaje));

    return j;
}

//---------------DESTRUCTOR-------------------

void destruirJugador(Jugador j){

    free(j);

}

//---------------MOSTRAR----------------------

void mostrarJugador(Jugador j){

    printf("\nNOMBRE: %s\n", j->nombre);
    printf("APELLIDO: %s\n", j->apellido);
    printf("DNI: %d\n", j->dni);
    printf("PUNTAJE: %.2f\n", getPuntajeTotal(j->puntosJug));

}

//---------------GETS-------------------------

char * getNombre(Jugador j){
    return j->nombre;
};
char * getApellido(Jugador j){
    return j->apellido;
};
Puntaje getPuntajeJug(Jugador j){
    return j->puntosJug;
};
int getDni(Jugador j){
    return j->dni;
};
Carton getCartonJug(Jugador j, int pos){
    return j->cartones[pos];
};

//---------------SETS-------------------------

void setNombre(Jugador j, char nuevoNombre[20]){
    strcpy(j->nombre, nuevoNombre);
}
void setApellido(Jugador j, char nuevoApellido[20]){
    strcpy(j->apellido, nuevoApellido);
}
void setPuntajeJug(Jugador j, Puntaje nuevoPuntaje){
    j->puntosJug = nuevoPuntaje;
}
void setDni(Jugador j, int nuevoDni){
    j->dni = nuevoDni;
}
void setCartonJug(Jugador j, Carton nuevoCarton, int pos){
    j->cartones[pos] = nuevoCarton;
}
