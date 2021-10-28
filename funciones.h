#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "carton.h"
#include "puntaje.h"
#include "computadora.h"
#include "jugador.h"

#define LINEA 3
#define COLUM 5
#define BOLSA 90

void cargarCartonAleatorio(Carton cart);
void cargarCartonPersonalizado(Carton cart);
int busquedaEnCarton(int m[LINEA*COLUM], int buscar);

//-----------------------------------------

void iniciaJugadoresConBasura(Jugador j[], int t);
int buscarPosLibre(Jugador j[], int t);
void agregarJugador(Jugador j[], Computadora pc, int t);
void leerArchivo(Jugador j[], int t);
void eliminarPuntajesGuardados(Jugador j[], int t);
int contadorPuntajesGuardados(Jugador j[], int t);
void ordenarJugadoresPorPuntos(Jugador jug[], int t);
void ordenarPuntajesGuardados(Jugador j[], int t);
void mostrarPuntajesGuardados(Jugador j[], int t);

//-----------------------------------------
void menuPrincipalDelJuego(Jugador j[], Computadora c, int t);

void comienzaElJuego(Jugador j, Computadora pc);

int cantCartones();

int opcionTipoCarton();

int busquedaBolillas(int v[BOLSA], int buscar);

void sacarBolillas(int v[BOLSA]);

//PRE: matriz definida en el main de entero, linea>0 y entero, vector definido en main de enteros, pos>0 y entero
//POST: si num en pos de vector esta en matriz, el numero en la matriz se cambia por -1, sino queda igual
void coincidencia(Carton cart, int v[BOLSA], int pos);

//PRE: estructura Carton definida y generada en main, linea>0 y entero
//POST: columna de matriz,fila de matriz o matriz entera cargada con -1 se pondra 1 en variable correspondiente
void canto(Carton cart, Puntaje punt);
//int puntos(int m[LINEA*COLUM], int t);

//PRE: dos estructuras Carton definidas y generadas en main, y dos estructuras Jugador definidas y generadas en main
//POST: se muestra por pantalla si fila,columna o la matriz entera esta cargada con -1
void puntajes(Jugador j, Computadora pc);

void finJuego(Jugador j, Computadora pc, int contador);


#endif // FUNCIONES_H_INCLUDED
