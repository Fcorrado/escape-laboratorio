#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "escape_laboratorio.h"
#include "detector_personajes.h"
#include "utiles.h"
#include <string.h>
#include "interaccion_usuario.h"

#define SI 'S'

int main() {
    srand ((unsigned)time(NULL));
    juego_t juego;
    char movimiento;
    char tipo_personaje;
    char respuesta_ayuda;
    char continuar;

    bienvenida();

    detector_de_personajes(&tipo_personaje);
    mostrar_nombre_personaje(tipo_personaje);

    obtener_mas_informacion();
    scanf(" %c", &respuesta_ayuda);

    if (respuesta_ayuda == SI) {
        mostrar_informacion_del_juego();
        printf("Para continuar presiona cualquier tecla\n");
        scanf(" %c", &continuar);
    }

    inicializar_juego(&juego, tipo_personaje);
    
    mostrar_juego(juego);

    printf("Te quedan %i movimientos \n", juego.personaje.movimientos);

    int estado = estado_juego(juego);

    while (estado == 0) {
        printf("Ingrese el movimiento del personaje: \n");
        scanf(" %c", &movimiento);
        mover_personaje(&juego, movimiento);
        estado = estado_juego(juego);
        printf("Te quedan %i movimientos \n", juego.personaje.movimientos);
    }

    if (estado == 1) {
        printf("Felicidades, ganaste! Lograste salir del Laboratorio de Dexter!\n");
    }

    return 0;
}