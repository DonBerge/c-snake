#ifndef PANTALLA_H

#include <stdio.h>
#include <stdlib.h>

#define PANTALLA_H

#define L 48
#define A 10

#ifndef SI
    #define SI 1
#endif // SI

#ifndef NO
    #define NO 0
#endif // NO

char **pantalla;
int puntaje;
int E=8;

void crearPantalla()
{
    pantalla=(char**)malloc(sizeof(char*)*A);
    if(!pantalla)
    {
        perror("Error al reservar memoria para la pantalla");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<A; i++)
    {
        pantalla[i]=(char*)malloc(sizeof(char)*L);
        if(!pantalla[i])
        {
            perror("Error al crear la pantalla");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<L; j++)
            if(i==0||i==A-1)
                pantalla[i][j]='.';
            else if(j==0||j==L-1)
                pantalla[i][j]=':';
            else
                pantalla[i][j]=' ';
    }
}
void genFruit()
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
        E++;
}

void mostrar()
{
    printf("Puntuacion: %d\n\n",puntaje);
    for(int i=0; i<A; i++)
    {
        for(int j=0; j<L; j++)
            putchar(pantalla[i][j]);
        putchar('\n');
    }
}
void eliminar()
{
    for(int i=0; i<A; i++)
        free(pantalla[i]);
    free(pantalla);
}
#endif
