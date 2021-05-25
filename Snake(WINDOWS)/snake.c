#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //Cualquier relacion con dross es pura coincidencia
#include "pantalla.h"
#include "serpiente.h"
#include "puntajes.h"
#include <unistd.h>

#define SEGUNDO 1000

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#else
#error Este programa solo funciona en windows o en linux
#endif // _WIN32

int game_over=0;

void iniciar()
{
    verificarArchivo();
    crearPantalla();
    crearNodo(L/2,A/2,'O');
    pantalla[primero->y][primero->x]=primero->c;
    genFruit();
    puntaje=0;
    mostrar();
}

void wait(int n)
{
#ifdef _WIN32
    Sleep(n);
#else
    usleep(n*1000);
#endif // _WIN32
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // _WIN32
}

int main()
{
    char c='\0';
    char buffer[10];
    srand(time(NULL));
    REPETIR:
    iniciar();
    printf("Pulsa una tecla de movimiento para comenzar...");
    while(!esTeclaDeMovimiento(c))
        c=getch();
    while(!game_over)
    {
        clear();
        mostrar();
        if(kbhit())
            c=getch();
        transladar(c);
        wait(SEGUNDO/E);
    }
    if(esTeclaDeMovimiento(c))
    {
        for_p_u(primero)
        pantalla[i->y][i->x]=i->c;
        clear();
        mostrar();
    }
    eliminar();
    eliminarSnake();
    mostrarPuntaje();
    wait(1*SEGUNDO);
    printf("\Pulsa una tecla para finalizar...\n");
    while(esTeclaDeMovimiento(getch()))
        continue;
}
