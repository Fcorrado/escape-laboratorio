#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "escape_laboratorio.h"
#include "detector_personajes.h"
#include "utiles.h"

int main() {
    srand ((unsigned)time(NULL));
    juego_t juego;
    char movimiento;
    char tipo_personaje;
    //detector_de_personajes(&tipo_personaje);
    tipo_personaje = 'H';

    printf(" %c \n", tipo_personaje);

    inicializar_juego(&juego, tipo_personaje);
    
    mostrar_juego(juego);

    printf("Te quedan %i movimientos \n", juego.personaje.movimientos);

    int estado = estado_juego(juego);

    while (estado == 0) {
        printf("Ingrese el movimiento del personaje: \n");
        scanf(" %c", &movimiento);
        mover_personaje(&juego, movimiento);
        estado = estado_juego(juego);
        printf("evalue el estado del juego y es %i", estado);
        printf("Te quedan %i movimientos \n", juego.personaje.movimientos);
    }

    if (estado == 1) {
        printf("GANASTE EL JUEGO!!");
    }

    return 0;
}