#ifndef SERPIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include "Pantalla.h"


#define SERPIENTE_H

#ifndef SI
    #define SI 1
#endif // SI

#ifndef NO
    #define NO 0
#endif // NO


#define for_p_u(inicial) for(Nodo* i=inicial;i!=NULL;i=i->siguiente)
#define for_u_p(final) for(Nodo* i=final;i!=NULL;i=i->anterior)

#define ESCAPE 27
#define ENTER 13
#define FLECHA_ARRIBA 72
#define FLECHA_ABAJO 80
#define FLECHA_IZQUIERDA 75
#define FLECHA_DERECHA 77

extern int game_over;
extern void clear();

typedef struct node
{
    struct node* anterior;
    int x;
    int y;
    char c;
    struct node* siguiente;
} Nodo;

Nodo* primero=NULL,*ultimo=NULL;

int esTeclaDeMovimiento(char c)
{
    if(c!='a'&&c!='A'&&c!=FLECHA_IZQUIERDA&&c!='w'&&c!='W'&&c!=FLECHA_ARRIBA&&c!='d'&&c!='D'&&c!=FLECHA_DERECHA&&c!='s'&&c!='S'&&c!=FLECHA_ABAJO)
        return NO;
    return SI;
}

Nodo* crearNodo(int x,int y,char c)
{
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    if(!nuevo)
    {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }
    nuevo->anterior=ultimo;
    nuevo->siguiente=NULL;
    nuevo->x=x;
    nuevo->y=y;
    nuevo->c=c;
    if(!primero)
    {
        primero=nuevo;
        ultimo=primero;
        primero->anterior=NULL;
    }
    else
    {
        ultimo->siguiente=nuevo;
        ultimo=nuevo;
    }
}
int estaAhi(Nodo* valor,Nodo* desde)
{
    for_p_u(desde)
    {
        if(i->x==valor->x&&i->y==valor->y)
        {
            game_over=1;
            return SI;
        }
    }
    return NO;
}

void transladar(char c)
{
    int generate=0;
    for_u_p(ultimo)
    {
        pantalla[i->y][i->x]=' ';
        if(i==primero)
            break;
        i->x=i->anterior->x;
        i->y=i->anterior->y;
    }
    switch(c)
    {
    case 'A':
    case 'a':
    case FLECHA_IZQUIERDA:
        primero->x--;
        break;
    case 'D':
    case 'd':
    case FLECHA_DERECHA:
        primero->x++;
        break;
    case 'W':
    case 'w':
    case FLECHA_ARRIBA:
        primero->y--;
        break;
    case 'S':
    case 's':
    case FLECHA_ABAJO:
        primero->y++;
        break;
    case ENTER:
        printf("El jugador se ha retirado de la partida...\n");
        exit(EXIT_SUCCESS);
    default:
        clear();
        printf("Has presionado la tecla incorrecta...\n\n");
        printf("Presiona enter para continuar...\n");
        while(getch()!=ENTER)
            continue;
        clear();
        game_over=1;
        return;
    }
    if(pantalla[primero->y][primero->x]=='F')
    {
        crearNodo(ultimo->x,ultimo->y,'x');
        genFruit();
    }
    else if(pantalla[primero->y][primero->x]!=' '||estaAhi(primero,primero->siguiente))
    {
        game_over=1;
        return;
    }
    for_p_u(primero)
    pantalla[i->y][i->x]=i->c;
}
void eliminarSnake()
{
    for(Nodo* aux=ultimo; aux!=NULL; aux=aux->anterior)
    {
        if(aux->siguiente!=NULL)
            free(aux->siguiente);
    }
    free(primero);
}
#endif

