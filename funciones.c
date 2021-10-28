#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "carton.h"
#include "puntaje.h"
#include "computadora.h"
#include "jugador.h"
#include "funciones.h"

#define LINEA 3
#define COLUM 5
#define BOLSA 90

#define ESPACIO "\n-------------------------------\n\n"
#define cambioDuenio "\n----------carton CPU---------\n\n"

enum busqueda{no_encontrado = -1, salir, col_lleno = 2, lin_lleno, bin_lleno};

void cargarCartonAleatorio(Carton cart){

    int repetido = 0;
    int num = 0;

    for(int i=0; i<LINEA*COLUM; i++){

        num = rand()%BOLSA+1;
        repetido = busquedaEnCarton(getCarton(cart), num);

        while(repetido != no_encontrado){

            num = rand()%90+1;
            repetido = busquedaEnCarton(getCarton(cart), num);
        }

        setNumEnPos(cart, i, num);
    }
    mostrarCarton(cart);
};

void cargarCartonPersonalizado(Carton cart){

    int repetido = 0;
    int num = 0;

    for(int i=0; i<LINEA*COLUM; i++){

        system("cls");

        printf(ESPACIO);

        mostrarCarton(cart);

        printf(ESPACIO);

        printf("\nIngrese nro\n");
        scanf("%d",&num);

        while((num>90) || (num<1)){
            printf("\nError, ingrese numero entre 1 y 90 inclusive\n\n");
            scanf("%d",&num);
        }

        repetido = busquedaEnCarton(getCarton(cart), num);

        while(repetido != no_encontrado){

            printf("\nIngrese un numero distinto\n");
            scanf("%d", &num);
            repetido = busquedaEnCarton(getCarton(cart), num);

            while((num>90) || (num<1)){
                printf("\nError, ingrese numero entre 1 y 90 inclusive\n\n");
                scanf("%d",&num);
            }
        }

        setNumEnPos(cart, i, num);
    }
    mostrarCarton(cart);
}

int busquedaEnCarton(int m[LINEA*COLUM], int buscar){

        int pos = no_encontrado;

        for(int i=0; i<LINEA*COLUM; i++){
                if(m[i] == buscar){

                        pos = i;
                }
            }

    return pos;
}

void iniciaJugadoresConBasura(Jugador j[], int t){

    for(int i=0; i<t; i++){
        j[i] = inicializarJugador();
    }
}

int buscarPosLibre(Jugador j[], int t){

    int pos = no_encontrado;

    for(int i=0; i<t; i++){
        if(getPuntajeTotal(getPuntajeJug(j[i])) == no_encontrado){
            pos = i;
            i = t;
        }
    }
    return pos;
}

void agregarJugador(Jugador j[], Computadora pc, int t){

    int i = buscarPosLibre(j, t);

    if(i != no_encontrado){
        j[i] = cargarJugador();
        comienzaElJuego(j[i], pc);
    }
    if(i == no_encontrado){
        printf("ERROR! YA JUGARON TODOS LOS JUGADORES POSIBLES\n");
    }
}

void leerArchivo(Jugador j[], int t){

    int i = 0;
    FILE * fileAStruct;

    fileAStruct = fopen("archivoJugadores.txt", "r");

    while(!feof(fileAStruct)){

        char aux[30]=" ";

        fgets(aux, 30, fileAStruct);

        Jugador auxJug;

        auxJug = pasarDeArchivosAStruct(aux, 35);

        j[i] = auxJug;

        i++;
    }

    fclose(fileAStruct);

    destruirJugador(j[i-1]);

    j[i-1] = inicializarJugador();

}

void eliminarPuntajesGuardados(Jugador j[], int t){

    int cant = contadorPuntajesGuardados(j, t);
    int elim = 0;

    printf("USTED TIENE %d PUNTAJES GUARDADOS DE %d POSIBLES\n\n", cant, BOLSA);
    printf("¿CUANTOS PUNTAJES QUIERE ELIMINAR?\n");
    scanf("%d", &elim);

    while(elim > cant){
        printf("ERROR!!! SE EXCEDIO CANTIDAD PERMITIDA\n");
        printf("PUEDE ELIMINAR %d PUNTAJES\n", cant);
        printf("¿CUANTOS PUNTAJES QUIERE ELIMINAR?\n");
        scanf("%d", &elim);
    }

    if(elim < cant){
        FILE * structAFile;

        structAFile = fopen("archivoJugadores.txt", "w");

        for(int i=0; i< (cant-elim); i++){
            fprintf(structAFile, "%s;%s;%d;%.2f\n", getNombre(j[i]), getApellido(j[i]), getDni(j[i]), getPuntajeTotal(getPuntajeJug(j[i])));
        }

        fclose(structAFile);
    }

    if(elim == cant){
        FILE * structAFile;

        iniciaJugadoresConBasura(j, t);

        structAFile = fopen("archivoJugadores.txt", "w");

        fprintf(structAFile, " ");

        fclose(structAFile);
    }
}

int contadorPuntajesGuardados(Jugador j[], int t){

    leerArchivo(j, t);

    int cont = 0;

    for(int i=0; i<t; i++){
        if(getPuntajeTotal(getPuntajeJug(j[i])) != no_encontrado){
            cont++;
        }
    }
    return cont;
}

void ordenarJugadoresPorPuntos(Jugador jug[], int t){

    leerArchivo(jug, t);

    Jugador aux;

    for(int i=0; i<BOLSA; i++){

        for(int j=0; j<BOLSA-1; j++){

            if(getPuntajeTotal(getPuntajeJug(jug[j])) < getPuntajeTotal(getPuntajeJug(jug[j+1]))){
                aux = jug[j];
                jug[j] = jug[j+1];
                jug[j+1] = aux;
            }
        }
    }
}

void ordenarPuntajesGuardados(Jugador j[], int t){

    ordenarJugadoresPorPuntos(j, t);

    int i = 0;

    FILE * structAFile;

    structAFile = fopen("archivoJugadores.txt", "w");

    while(getPuntajeTotal(getPuntajeJug(j[i])) != no_encontrado){
        fprintf(structAFile, "%s;%s;%d;%.2f\n", getNombre(j[i]), getApellido(j[i]), getDni(j[i]), getPuntajeTotal(getPuntajeJug(j[i])));
        i++;
    }

    fclose(structAFile);
}

void mostrarPuntajesGuardados(Jugador j[], int t){

    leerArchivo(j, t);

    for(int i=0; i<t; i++){
        if(getPuntajeTotal(getPuntajeJug(j[i])) != no_encontrado){
                mostrarJugador(j[i]);
        }
    }
}

//---------------------------------------------

int cantCartones(){

    int nro=0;

    printf("\nElija cantidad de cartones para jugar\n");
    scanf("%d",&nro);

    while(nro<1 || nro>3){

        printf("\nERROR!!! Por favor elija entre 1 y 3 cartones inclusive\n");
        scanf("%d",&nro);
    }

    return nro;
}

int opcionTipoCarton(){

    int op = 0;

    printf("\nElija que carton quiere comprar\n");
    printf("1- Carton personalizado\n");
    printf("2- Carton aleatorio\n");
    scanf("%d",&op);

    while(op<1 || op>2){
        printf("\nERROR!!! Por favor elija opcion 1 o 2\n");
        scanf("%d",&op);
    }

    return op;
}

int busquedaBolillas(int v[BOLSA], int buscar){

    int pos = -1;

    for(int i=0; i<BOLSA; i++){
        if(v[i] == buscar){
            pos = i;
        }
    }
    return pos;
}

void sacarBolillas(int v[BOLSA]){

    int num = 0;
    int repetir = 0;

    for(int i=0; i<BOLSA; i++){

        num = rand()%BOLSA+1;
        repetir =  busquedaBolillas(v, num);

        while(repetir != no_encontrado){

            num = rand()%BOLSA + 1;
            repetir = busquedaBolillas(v, num);
        }

        v[i] = num;
    }
}

void coincidencia(Carton cart, int v[BOLSA], int pos){

    for(int i=0; i<LINEA*COLUM; i++){
        if(v[pos] == getNumEnPos(cart, i)){
            setNumEnPos(cart, i, no_encontrado);
        }
    }
    mostrarCarton(cart);
}

void canto(Carton cart, Puntaje punt){

    int auxColum = 0;
    int contar = 0;

    int m[LINEA][COLUM];

    for(int l=0; l<LINEA; l++){
        for(int c=0; c<COLUM; c++){
            m[l][c] = getCarton(cart)[contar];
            contar++;
        }
    }

    for(int c=0; c<COLUM; c++){
        for(int l=0; l<LINEA; l++){
            if(-1 == m[l][c]){
                auxColum++;
            }
        }
        if((auxColum == 3) && (getColumna(punt) != col_lleno)){
                setColumna(punt, col_lleno);
            }
        auxColum = 0;
    }

    int auxLin=0;

    for(int l=0; l<LINEA; l++){
        for(int c=0; c<COLUM; c++){
            if(-1 == m[l][c]){
                auxLin++;
            }
        }
        if((auxLin == 5) && (getLinea(punt) != lin_lleno)){
                setLinea(punt, lin_lleno);
            }
        auxLin = 0;
    }

    int auxBingo=0;

    for(int l=0; l<LINEA; l++){
        for(int c=0; c<COLUM; c++){
            if(-1 == m[l][c]){
                auxBingo++;
            }
        }

    if(auxBingo==15){
                setBingo(punt, bin_lleno);
            }
        }
}

void puntajes(Jugador j, Computadora pc){

    if((getLinea(getPuntajeJug(j)) == lin_lleno ) && (getLinea(getPuntajeCPU(pc)) != lin_lleno )){
        setLinea(getPuntajeCPU(pc), lin_lleno);
        printf("\nJUGADOR LLENO LINEA\n\n");
        setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) + 20);
    }

    if((getLinea(getPuntajeCPU(pc)) == lin_lleno) && (getLinea(getPuntajeJug(j)) != lin_lleno)){
        setLinea(getPuntajeJug(j), lin_lleno);
        printf("\nCPU LLENO LINEA\n\n");
        setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) + 20);
    }

    if((getColumna(getPuntajeJug(j)) == col_lleno ) && (getColumna(getPuntajeCPU(pc)) != col_lleno)){
        setColumna(getPuntajeCPU(pc), col_lleno);
        printf("\nJUGADOR LLENO COLUMNA\n\n");
        setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) + 10);
    }

    if((getColumna(getPuntajeCPU(pc)) == col_lleno) && (getColumna(getPuntajeJug(j)) != col_lleno)){
        setColumna(getPuntajeJug(j), col_lleno);
        printf("\nCPU LLENO COLUMNA\n\n");
        setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) + 10);
    }

    if((getBingo(getPuntajeJug(j)) == bin_lleno) && (getBingo(getPuntajeCPU(pc)) != bin_lleno)){
        setBingo(getPuntajeCPU(pc), bin_lleno);
        printf("\nJUGADOR HIZO BINGO\n\n");
        setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) + 70);
    }

    if((getBingo(getPuntajeCPU(pc)) == bin_lleno) && (getBingo(getPuntajeJug(j)) != bin_lleno)){
        printf("\nCPU HIZO BINGO\n\n");
        setBingo(getPuntajeJug(j), bin_lleno);
        setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) + 70);
    }
}

void finJuego(Jugador j, Computadora pc, int contador){

    if(contador<29){
       setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) * 2);
       setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) * 2);
    }

    if((contador>28) && (contador<50)){
       setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) * 1.7);
       setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) * 1.7);
    }

    if((contador>49) && (contador<70)){
       setPuntajeTotal(getPuntajeJug(j), getPuntajeTotal(getPuntajeJug(j)) * 1.5);
       setPuntajeTotal(getPuntajeCPU(pc), getPuntajeTotal(getPuntajeCPU(pc)) * 1.5);
    }

    mostrarJugador(j);
    printf("\nEL PUNTAJE DE LA CPU ES: %.3f\n\n", getPuntajeTotal(getPuntajeCPU(pc)));

    if(getPuntajeTotal(getPuntajeJug(j)) < getPuntajeTotal(getPuntajeCPU(pc)))
       printf("CPU GANO LA PARTIDA!!");

    if(getPuntajeTotal(getPuntajeJug(j)) > getPuntajeTotal(getPuntajeCPU(pc)))
       printf("%s GANO LA PARTIDA!!", getNombre(j));

    if(getPuntajeTotal(getPuntajeJug(j)) == getPuntajeTotal(getPuntajeCPU(pc)))
       printf("ES UN EMPATE!!");

}

void comienzaElJuego(Jugador j, Computadora pc){

    pc = cargarCPU();

    int nroCartones = 0;

    int i=0;

    nroCartones = cantCartones();
    int menu = 0;

    int bolillas[BOLSA];

    int contar = 0;

    system("cls");

    for(i=0; i<nroCartones; i++){  //cantidad de cartones segun cuantos se haya elegido
            menu = opcionTipoCarton(); //guarda variable de funcion opcion

            switch(menu){ //dependiendo la forma la que generar los cartones (personalizado/aleatorio) se haran de una forma u otra
                case (1):
                    cargarCartonPersonalizado(getCartonJug(j, i));
                            printf(cambioDuenio);
                    cargarCartonAleatorio(getCartonCPU(pc, i));
                            printf(ESPACIO);
                    break;

                case(2):
                    cargarCartonAleatorio(getCartonJug(j, i));
                            printf(cambioDuenio);
                    cargarCartonAleatorio(getCartonCPU(pc, i));
                            printf(ESPACIO);
                    break;
            } //cierre de switch
    } //cierre de for

    system("cls");

    sacarBolillas(bolillas);

    do{ // abre hacer mientras garantizando minimo 1 juego
        printf("\nEl numero que salio fue: %d\n", bolillas[contar]);
        for(i=0; i<nroCartones; i++){ //cantidad de cartones segun cuantos se haya elegido
                 printf(ESPACIO);
            coincidencia(getCartonJug(j, i), bolillas, contar);
                 printf(cambioDuenio);
            coincidencia(getCartonCPU(pc, i), bolillas, contar);

            canto(getCartonJug(j, i), getPuntajeJug(j));
            canto(getCartonCPU(pc, i), getPuntajeCPU(pc));

            puntajes(j, pc);
        }

        Sleep(1000);// se ralentiza el funciona la ejecucion por 0.5 seg
        contar++;
        system("cls");

    }while((getBingo(getPuntajeJug(j)) < 1) && (getBingo(getPuntajeCPU(pc)) < 1)); // se sigue el bucle mientras nadie haya cantado bingo

    finJuego(j, pc, contar);

    free(pc);

    FILE * structAFile;
    structAFile = fopen("archivoJugadores.txt", "a");
    fprintf(structAFile, "%s;%s;%d;%.2f\n", getNombre(j), getApellido(j), getDni(j), getPuntajeTotal(getPuntajeJug(j)));
    fclose(structAFile);

}

void menuPrincipalDelJuego(Jugador j[], Computadora pc, int t){

    int n = 0;
    int contador = 0;

    printf("Ingresar opcion:\n");
    printf("%d- Juego nuevo\n", 1);
    printf("%d- Leer puntajes\n", 2);
    printf("%d- Eliminar puntajes\n", 3);
    printf("%d- Salir\n", 0);

    scanf("%d", &n);

    while((n<0) || (n>3)){

        printf("ERROR! ELIJA NUMERO ENTRE %d y %d", 0, 3);
        scanf("%d", &n);

    }

    system("cls");

    while(n != 0){

        switch(n){

            case(2):        system("cls");
                            mostrarPuntajesGuardados(j, t);
                        break;
            case(3):        system("cls");
                            eliminarPuntajesGuardados(j, t);
                            mostrarPuntajesGuardados(j, t);
                        break;

            case(1):        system("cls");
                            agregarJugador(j, pc, t);
                            ordenarPuntajesGuardados(j, t);
                        break;

            case(0):        printf("\n\nGRACIAS POR JUGAR!!");
                        break;
        }

        printf(ESPACIO);

        printf("\nIngresar opcion:\n");
        printf("%d- Juego nuevo\n", 1);
        printf("%d- Leer puntajes\n", 2);
        printf("%d- Eliminar puntajes\n", 3);
        printf("%d- Salir\n", 0);

        scanf("%d", &n);

        while((n<0) || (n>3)){

            printf("ERROR! ELIJA NUMERO ENTRE %d y %d", 0, 3);
            scanf("%d", &n);

        }

        system("cls");
    }
}
