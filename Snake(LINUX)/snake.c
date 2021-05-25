/// snake.c Programa principal ///


/***** Librerias   ***/

                    // Use stdio.h para leer caracteres desde el
                    // teclado o desde un fichero y mostrarlos por pantalla. Tambien usada para mostrar mensajes
                    // de error.
#include <stdio.h>  //
                    // Funciones utilizadas:
                    //                       printf(),scanf(),getchar(), putchar(), fopen(), fprintf(),
                    //                       fscanf(), fclose(), perror().
                    //
                    // Ademas utilize punteros a FILE, que es una estructura definida en stdio.h
                    //

#include <stdlib.h> // stdlib.h fue usada para generar numeros aleatorios, borrar la pantalla,
                    // gestionar memoria dinamica y para terminar el programa anormalmente en casos particulares.
                    //
                    // Funciones utilizadas:
                    //                       rand(), srand(), system(), exit(), malloc(), free().
                    //
                    // Constantes usadas:
                    //
                    // NULL(0): Indica o una direccion de memoria nula.
                    // EXIT_SUCCESS(0): indica que el programa termino de manera adecuada.
                    // EXIT_FAILURE(!0): indica todo lo contrario.

#include <time.h>   //Unicamente usada para llamar a la funcion time(NULL).

#include <conio.h> // Console Input-Output header (conio.h): Biblioteca no estandar usada para leer y escribir
                   // directamente desde la consola si el uso de los buffer. En caso de que se pueda incluir
                   // se utilizan las funciones getch() y kbhit() para leer un caracter sin mostrarlo ni presionar
                   // enter y para detectar si el usuario presiono una tecla. Si no esta disponible, entonces hay que
                   // comentar la linea de #include <conio.h> para que la biblioteca no se incluya y el programa se
                   // pueda compilar. Aunque esto le quitara funcionalidades al programa.

#include "pantalla.h" // Aqui se agrupan las funciones relacionadas con la pantalla( matriz bidimensional de caracteres.

#include "serpiente.h" //Aqui se agrupan las funciones relacionadas con la "serpiente".

#include "puntajes.h" //Aqui se agrupan las funciones para leer el fichero puntajes.txt y obtener el maximo puntaje.

#ifdef _WIN32         // Si _WIN32( Constante definida por defecto en windows) esta definida
#include <windows.h>  // inclui windows.h
#elif __linux__       // sino entonces si __linux__ (constante definida por defecto en linux) esta definida
#include <unistd.h>   // inclui unistd.h
#else                 // si ninguna de las dos constantes esta definida
#error Este programa solo funciona en windows o en linux // Muestra este error
#endif // Dependiendo del sistema operativo, se incluye windows.h o unistd.h.
       // Para ambas bibliotecas usamos una funcion Sleep(int n) (Espera n milisegundos y reanuda la ejecucion).
       // o usleep(int n) (Espera n microsegundos y reanuda la ejecucion) para windows.h y unistd.h respectivamente.

/**** Constantes *****/

#define SEGUNDO 1000 // Define 1 SEGUNDO como 1000 MILISEGUNDOS

#ifndef SI // Si SI no esta definida
    #define SI 1 // define SI como 1
#endif // Ya definida en serpiente.h

#ifndef NO // Si NO no esta definida
    #define NO 0 // Define NO como 0
#endif // Ya definida en serpiente.h

#define FRUTAS_EN_PANTALLA 3 // La cantidad de frutas que va a haber en la pantalla al mismo tiempo.


int game_over=0; // Variable global booleana (vive en todo el programa y puede valer verdadero o falso)
                 //que nos indica si el jugador perdio.


void iniciar() /// Esta funcion llama las funciones necesarias para iniciar el juego
{
    verificarArchivo(); // Verifica si puntuaciones.txt existe, si no, lo crea.
    crearPantalla(); // Reserva memoria para almacenar la pantalla.
    crearNodo(L/2,A/2,'O'); //Crea la cabeza de la serpiente.
    pantalla[primero->y][primero->x]=primero->c; // Inserta la cabeza en la pantalla.
    for(int i=0;i<FRUTAS_EN_PANTALLA;i++) // Insertamos todas las frutas en la pantalla.
        genFruit();
    puntaje=0; // Coloca el puntaje inicial en 0
    mostrar(); // Muestra la pantalla
}

void wait(int n) /// Espera n segundos antes de retomar la ejecucion
{
#ifdef _WIN32       // Si _WIN32 esta definido
    Sleep(n);       // Llama a Sleep();
#else               // Si no
    usleep(n*1000); // Llama a usleep();
#endif // _WIN32
}

void clear() /// Borra la pantalla
{
#ifdef _WIN32         // Si _WIN32 esta definido
    system("cls");    // Llama a system("cls");
#else                 // Si no
    system("clear");  // Llama a system("clear);
#endif // _WIN32
}

int jugadorPulsoTecla() /// Detecta si el jugador presiono una tecla, si puede.
{
    #ifdef _CONIO_H_    // Si conio.h esta incluida
        return kbhit(); // llamar a kbhit() y retornar su valor
    #else               // Si no
        return SI;      // Devolver SI
    #endif // Si conio.h esta incluida, es posible detectar si el usuario presiono o no una tecla
           // con la funcion kbhit(). Si conio.h no esta incluida, es imposible determinar
           // si no se presiono una tecla, por lo que se devuelve SI.
}
int getTecla()
{
    #ifdef _CONIO_H_     // Si conio.h esta incluida
        return getch();  // Devuelve el valor de getch()
    #else                // Si no
	char c;              //
        scanf(" %c",&c); // Devuelve un caracter no blanco leido desde el teclado.
        return c;        //
    #endif // Si conio.h esta incluida, es posible usar la funcion getch() para detectar las teclas de movimiento
           // sin necesidad de que el caracter presionado se muestre por pantalla o de presionar enter.
}

int main()
{
    char c;  // Almacena el caracter asociado a la tecla que pulso el jugador
    srand(time(NULL)); // Para la generacion de numeros aleatorios.
    iniciar(); // Se realizan los preparativos antes de iniciar el juego.

    printf("Pulsa una tecla de movimiento para comenzar..."); //
    while(!esTeclaDeMovimiento(c))                            // Cuando el jugador presiona una tecla de movimiento
        c=getTecla();                                         // comienza el juego.

    while(!game_over) // Mientras no haya un game over.
    {
        clear(); // Borra la pantalla.
        mostrar(); // Muestra la pantalla de juego
        if(jugadorPulsoTecla()) // Si el jugador pulso una tecla
            c=getTecla(); // Registra la tecla que pulso el jugador
        transladar(c); // Mueve la serpiente o lanza un game over dependiendo de que tecla pulso un jugador
        wait(1.0*SEGUNDO/E); // Espera 1/E segundos donde E va aumentando en base al puntaje.
    }

    if(esTeclaDeMovimiento(c)) // Si la ultima tecla que pulso el jugador es una tecla de movimiento
    {
        for_p_u(primero)            //
        pantalla[i->y][i->x]=i->c;  // Actualiza la ultima posicion
        clear();                    // de la serpiente.
        mostrar();                  //
    }

    eliminarSnake();  // Se libera la memoria usada para la serpiente.

    mostrarPuntaje(); // Se muestra el puntaje maximo y de ser necesario, se actualiza.

    wait(1*SEGUNDO);  // Esperamos un segundo.

    printf("Pulsa una tecla para finalizar...\n"); //
    while(esTeclaDeMovimiento(getTecla()))         // Y finalizamos el programa.
        continue;                                  //
}
