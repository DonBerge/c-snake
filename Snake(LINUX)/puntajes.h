#ifndef PUNTAJE_H // Si PUNTAJE_H no esta definido

#define PUNTAJE_H // La define (

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strcat().
#include <ctype.h> // Para usar toupper().

FILE* puntuacion; // Puntero FILE para manejar archivos.

int verificarArchivo()
{
    if(!(puntuacion=fopen("puntuaciones.txt","r"))) // Si al querer abrir puntuaciones.txt
    {                                                // para en modo lectura, obtenemos un error.
        if(!(puntuacion=fopen("puntuaciones.txt","w")))// Intentamos crear el archivo
        {                                              // si fracasamos.
            perror("Error al abrir el archivo \"puntuaciones.txt\""); // Mostramos un error y finalizamos
            exit(EXIT_FAILURE);                                       // El programa anormalmente
        }
    }
    fclose(puntuacion); // Si conseguimos abrir/crear el archivo, lo cerramos.
}

void mostrarPuntaje()
{
    char nombre[100]; // Almacena el nombre de la persona con mayor puntaje
    int puntaje_mayor; // Almacena el mayor puntaje
    printf("\nPERDISTE\n\n");
    puntuacion=fopen("puntuaciones.txt","r"); // Abre el archivo en modo lectura
    if(!puntuacion)
    {
        perror("No se pudo abrir el archivo \"puntuaciones.txt\""); // Si no lo consigue el programa termina
        exit(EXIT_FAILURE);
    }
    fscanf(puntuacion,"%[^ ] %d",nombre,&puntaje_mayor); // Leemos desde "puntuaciones.txt" el nombre y el puntaje con mayor puntaucion
    fclose(puntuacion); // Cierra el archivo
    if(puntaje>puntaje_mayor) // Si el puntaje del jugador es mayor al puntaje maximo registrado
    {
        puntaje_mayor=puntaje; // Lo cambiamos.

        printf("LA PUNTUACION DE ");
        for(int i=0; nombre[i]; i++)
            putchar(toupper(nombre[i]));
        printf(" A SIDO SUPERADA!!!\n\n");
        printf("Ingresa tu nombre: ");

        scanf("%s",nombre); // Le pedimos al jugador un nombre para identificarlo.

        #ifdef _WIN32
            strcat(nombre,"(Windows)");
        #else
            strcat(nombre,"(Linux)");
        #endif // Especificamos en que SO consiguio dicha puntuacion.

        puntuacion=fopen("puntuaciones.txt","w"); // Abrimos el archivo en modo escritura
        if(!puntuacion)
        {
            perror("No se pudo abrir el archivo \"puntuaciones.txt\""); // Si no podemos abrirlo, el programa termina.
            exit(EXIT_FAILURE);
        }
        fprintf(puntuacion,"%s %d",nombre,puntaje_mayor); // Cambia el nombre y el puntaje mayor
    }
    printf("Nombre del jugador con la maxima puntuacion: %s\n\n",nombre); // Muestra el nombre y el puntaje mayor.
    printf("Maxima puntuacion registrada: %d\n\n",puntaje_mayor);
}
#endif

