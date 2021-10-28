#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "carton.h"
#include "puntaje.h"
#include "computadora.h"
#include "jugador.h"
#include "funciones.h"


#define LINEA 3
#define COLUM 5
#define BOLSA 90

int main()
{
    srand(time(NULL));

    printf("START GAME!\n\n\n");

    Jugador jugadores[BOLSA];

    Computadora cpu = cargarCPU();

    iniciaJugadoresConBasura(jugadores, BOLSA);

    menuPrincipalDelJuego(jugadores, cpu, BOLSA);


    return 0;
}
