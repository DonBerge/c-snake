#ifndef SERPIENTE_H //
                    // Para evitar la doble inclusion
#define SERPIENTE_H //

#include <stdio.h>
#include <stdlib.h>
#include "pantalla.h"

#ifndef SI  // Definimos Si y NO
    #define SI 1
#endif

#ifndef NO
    #define NO 0
#endif

/// MACROS ///
// Cuando en el codigo aparecen for_p_u y for_u_p se remplazan por las palabras a la derecha
#define for_p_u(inicial) for(Nodo* i=inicial;i!=NULL;i=i->siguiente) // Recorre desde inicial hasta ultimo
#define for_u_p(final) for(Nodo* i=final;i!=NULL;i=i->anterior) // Recorre desde final hasta primero

// Definimos constantes para las teclas especiales que getch() puede reconocer.
#define ESCAPE 27
#define ENTER 13
#define FLECHA_ARRIBA 72
#define FLECHA_ABAJO 80
#define FLECHA_IZQUIERDA 75
#define FLECHA_DERECHA 77

/// Funciones y variables externas ///
extern int game_over; // Indica si hubo un game_over
extern void clear();  // Para borrar la pantalla
extern int getTecla(); // Para detectar una tecla

/// Para hacer que la serpiente crezca use un tipo de estructura de datos llamada lista doblemente enlazada\
(doubly linked list). Son varias estructuras de datos(o nodos) donde cada una contiene un puntero\
(piensenlo como una flecha) al nodo siguiente y al nodo anterior. Es similar a un array, pero una ventaja que tiene respecto\
a estos es que su tamaño puede variar en tiempos de ejecucion, cosa que el array no puede hacer ya que hay que darle un valor\
fijo cuando se lo declara. El puntero anterior del primer elemento y el puntero siguiente del ultimo elemento apuntan a NULL.

/**

     Una lista enlazada tiene mas o menos esta pinta:

              Primero
    NULL <-- anterior
                x
                y
                c           (Nodo que le sigue a primero y le precede a ultimo)
            siguiente -->                <--anterior
                                               x
                                               y
                                               c                     Ultimo
                                           siguiente -->        <-- anterior
                                                                       x
                                                                       y
                                                                       c
                                                                   siguiente --> NULL


**/

typedef struct node // Estructura usada para construir la serpiente
{
    struct node* anterior; // Puntero a la parte anterior de la serpiente.
    int x; // Coordenada x.
    int y; // Coordenada y.
    char c; // Caracter representativo.
    struct node* siguiente; // Puntero a la parte siguiente de la serpiente.
} Nodo;

Nodo* primero=NULL,*ultimo=NULL; // Dos punteros, uno al primer nodo y otro al ultimo

int esTeclaDeMovimiento(char c) /// Verifica si un caracter corresponde a una tecla de movimiento
{
    if(c!='a'&&c!='A'&&c!=FLECHA_IZQUIERDA&&c!='w'&&c!='W'&&c!=FLECHA_ARRIBA&&c!='d'&&c!='D'&&c!=FLECHA_DERECHA&&c!='s'&&c!='S'&&c!=FLECHA_ABAJO)
        return NO;
    return SI;
}

Nodo* crearNodo(int x,int y,char c) /// Crea un nodo de la serpiente
{
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo)); // Reservamos memoria para el nodo, sizeof(Nodo) devuelve el tamaño en bytes de un Nodo
    if(!nuevo) // Si no se puede reservar memoria el programa termina
    {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    /// nuevo->algo funciona de manera analoga a (*nuevo).algo donde * es un operador que devuelve el valor de una direccion de memoria

    nuevo->anterior=ultimo; // El nuevo nodo que creamos va a ser el ultimo de la lista, por lo que anterior apunta a ultimo
                            // y ultimo apunta al que antes era el ultimo nodo de la lista.

    nuevo->siguiente=NULL; // Al ser el ultimo nodo, siguiente apunta a NULL.
    nuevo->x=x;  //
    nuevo->y=y;  // Le asignamos los valores pasados por parametro.
    nuevo->c=c;  //
    if(!primero) // Si primero es igual a NULL, lo cual quiere decir que no hay elementos en la serpiente.
    {
        primero=nuevo; // El nuevo nodo es el primer elemento y el ultimo elemento al mismo tiempo.
        ultimo=primero;
        primero->anterior=NULL; // Actualizamos el puntero anterior.
    }
    else // Si primero no es igual a NULL, hay mas nodos en la lista.
    {
        ultimo->siguiente=nuevo; // El que le sigue al que antes era el ultimo es el nuevo nodo.
        ultimo=nuevo; // Ahora el nuevo nodo es el ultimo nodo.
    }
    return nuevo; // Devolvemos un puntero al nuevo nodo (de todas formas, esto no lo usamos en el programa).
}
int estaAhi(Nodo* valor,Nodo* desde) /// Se fija si las coordenadas de un Nodo de la serpiente es igual a otro.
{
    for_p_u(desde) // Desde una posicion pasada como parametro hasta el ultimo nodo
    {
        if(i->x==valor->x&&i->y==valor->y) // Si las coordenadas son iguales.
        {
            game_over=1; // El juego termina.
            return SI;
        }
    }
    return NO; // Devolvemos No si no hay nodos con coordenadas iguales.
}

void transladar(char c) /// Mueve la serpiente
{
    int generate=0;
    for_u_p(ultimo) // Desde el ultimo hasta el primer elemento
    {
        pantalla[i->y][i->x]=' '; // Se borran todos los nodos de la pantalla
        if(i==primero) // Cuando llega al primer elemento se termina el bucle
            break;
        i->x=i->anterior->x; // El nodo que estamos viendo con i se mueve
        i->y=i->anterior->y; // al lugar del nodo que le precede
    }

    /// switch funciona igual que una escalera de ifs
    /**
    Pantalla:
         x aumenta a medida que se acerca a la derechz
         y aumenta a medida que se acerca a la parte de abajo
        ___________________
       |                   |
       |                   |
       |                   |
       |___________________|
    */
    switch(c)
    {
    case 'A': // Si c es una tecla de movimiento a la izquierda
    case 'a':
    case FLECHA_IZQUIERDA:
        primero->x--; // Le restamos uno al x de la cabeza
        break;
    case 'D': // Si c es una tecla de movimiento a la derecha
    case 'd':
    case FLECHA_DERECHA:
        primero->x++; // Le sumamos uno al x de la cabez
        break;
    case 'W': // Si c es una tecla de movimiento hacia arriba
    case 'w':
    case FLECHA_ARRIBA:
        primero->y--; // Le restamos uno al y de la cabeza
        break;
    case 'S': // Si c es una tecla de movimiento hacia abajo
    case 's':
    case FLECHA_ABAJO:
        primero->y++; //Le sumamos uno al y de la cabeza
        break;
    case '\n': // Si c es un ENTER o un ESCAPE
    case ENTER:
    case ESCAPE:
        #ifdef _CONIO_H_ // Y si conio.h esta incluia
        printf("El jugador se ha retirado de la partida...\n"); // El programa termina, porque el jugador se retira
        exit(EXIT_SUCCESS);
        #endif
        break;
    default: // Si c no es ninguna de las cosas enumeradas arriba
        clear(); // El juego termina porque el jugador pulso una tecla no valida
        printf("Has presionado la tecla incorrecta...\n");
        game_over=1;
        return;
    }
    if(pantalla[primero->y][primero->x]=='F') // Si las coordenadas de la cabeza coinciden con el lugar de una fruta.
    {
        crearNodo(ultimo->x,ultimo->y,'x'); //Creamos un nuevo nodo en el lugar del ultimo nodo
        generate=1; // Indicamos que queremos generar una fruta
    }
    else if(pantalla[primero->y][primero->x]!=' '||estaAhi(primero,primero->siguiente)) // Si lo de arriba no ocurre entonces si
    { // Si las coordenadas de la pantalla no coinciden con el lugar de un espacio o hay un nodo con las mismas coordenadas de la cabeza
        game_over=1; // El juego termina
        return;
    }
    for_p_u(primero) //Insertamos la serpiente en la pantalla
    pantalla[i->y][i->x]=i->c;
    if(generate) // Si hay que generar una fruta la generamos
        genFruit();
}
void eliminarSnake() /// Esta funcion libera la memoria ocupada por la serpiente
{
    for_u_p(ultimo) // Desde el ulitmo el elemento hasta el primero
    {
        if(i->siguiente!=NULL) // Si el ndo que le sigue a i no es igual a NULL
            free(i->siguiente); // Se libera la memoria utilizada para el nodo siguiente
    }
    free(primero); // Finalmente se libera la memoria usada para el primer Nodo
}
#endif

