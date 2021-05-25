/// pantalla.h: Aqui se encuentran las funciones relacionadas con la pantalla donde se almacenan los caracteres de juego

#ifndef PANTALLA_H //
                   // Para evitar la doble inclusion
#define PANTALLA_H //

#include <stdio.h>
#include <stdlib.h>

#define L 48 // Caracteres de largo de la pantalla.
#define A 10 // Caracteres de ancho de la pantalla.

// El tamaño de la pantalla puede variar segun los pixeles de alto y de ancho de un caracter.

char pantalla[A][L]; // Matriz bidimensional de AxL caracteres. Incluye todos los caracteres que se van a imprimir.
int puntaje; //El puntaje del jugador.
int E=15; // La cantidad de segundos que va a esperar la maquina hasta la siguiente jugada es 1/E.

void crearPantalla() /// Coloca todos los caracteres de los bordes, y tambien los espacios.
{
    for(int i=0; i<A; i++)
    {
        for(int j=0; j<L; j++)
            if(j==0||j==L-1)
                pantalla[i][j]='|';
            else if(i==0||i==A-1)
                pantalla[i][j]='_';
            else
                pantalla[i][j]=' ';
    }
    pantalla[0][0]=' ';
    pantalla[0][L-1]=' ';
}
void genFruit() /// Coloca una fruta en una posicion aleatoria de la pantalla.
{
    int y,x;
    do
    {
        y=rand () % (A-2) + 1;
        x=rand () % (L-2) + 1;
    }
    while(pantalla[y][x]!=' ');
    pantalla[y][x]='F';
    puntaje++;
    if(puntaje%5==0)
        E+=5;
}

void mostrar() /// Muestra la pantalla junto con el puntaje.
{
    printf("Puntuacion: %d\n\n",puntaje);
    for(int i=0; i<A; i++)
    {
        for(int j=0; j<L; j++)
            putchar(pantalla[i][j]);
        putchar('\n');
    }
}
#endif
