#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "escape_laboratorio.h"
#include "utiles.h"

#define ENTRADA 'E'
#define SALIDA 'S'
#define BALDOSA_PINCHE 'P'
#define MONEDA 'M'
#define LLAVE 'L'
#define BOMBA 'B'
#define INTERRUPTOR 'I'
#define BALDOSA_TELETRANSPORTADORA 'T'
#define GUARDIA 'G'
#define MOVIMIENTOS_INICIALES 10
#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4
#define DIMENSION_MENOR 12
#define DIMENSION_MAYOR 17
#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define IZQUIERDA 'a'
#define CORAJE 'C'
#define BLUE 'B'
#define BELLOTA 'S'
#define PURO_HUESO 'H'
#define POLLITO 'P'
#define JOHNNY_BRAVO 'J'
#define PAREDES '*'
#define VACIO ' '

bool hay_pared(nivel_t* nivel, coordenada_t* coordenada) {
    for (int i = 0; i < nivel->tope_paredes; i++) {
        if(nivel->paredes[i].fil == coordenada->fil && nivel->paredes[i].col == coordenada->col) {
            return true;
        }
    }
    return false;
}

void crear_coordenada_disponible(nivel_t* nivel, coordenada_t* coordenada, int numero_nivel) {
    bool pude_ubicar = false;

    while (!pude_ubicar) {
        if (numero_nivel == PRIMER_NIVEL || numero_nivel == TERCER_NIVEL) {
            coordenada->fil = (rand() % 10) + 1;
            coordenada->col = (rand() % 10) + 1;
        } else {
            coordenada->fil = (rand() % 15) + 1;
            coordenada->col = (rand() % 15) + 1;
        }

        bool hay_pared_en_posicion = hay_pared(nivel, coordenada);
        
        
        bool entrada_y_coordenada_iguales = nivel->entrada.fil == coordenada->fil && nivel->entrada.col == coordenada->col;
        bool salida_y_coordenada_iguales = nivel->salida.fil == coordenada->fil && nivel->salida.col == coordenada->col;
        
        bool hay_obstaculos = false;
        for (int i = 0; i < nivel->tope_obstaculos; i++) {
            if(nivel->obstaculos[i].posicion.fil == coordenada->fil && nivel->obstaculos[i].posicion.col == coordenada->col) {
                hay_obstaculos = true;
            }
        }

        bool hay_herramientas = false;
        for (int i = 0; i < nivel->tope_herramientas; i++) {
            if(nivel->herramientas[i].posicion.fil == coordenada->fil && nivel->herramientas[i].posicion.col == coordenada->col) {
                hay_herramientas = true;
            }
        }

        if (!hay_pared_en_posicion && !entrada_y_coordenada_iguales && !salida_y_coordenada_iguales &&
            !hay_obstaculos && !hay_herramientas) {
            pude_ubicar = true;
        }
    }
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba) {

    nivel->tope_herramientas = 0;
    nivel->tope_obstaculos = 0;
    nivel->tope_paredes = 0;

    int cantidad_monedas = cantidad_baldosas_pinches/2;

    obtener_paredes(numero_nivel, nivel->paredes, &(nivel->tope_paredes));

    coordenada_t entrada;
    crear_coordenada_disponible(nivel, &entrada, numero_nivel);
    nivel->entrada = entrada;

    coordenada_t salida;
    crear_coordenada_disponible(nivel, &salida, numero_nivel);
    nivel->salida = salida;


    for (int i = 0; i < cantidad_baldosas_pinches; i++) {
        coordenada_t posicion_baldosa_pinche;
        crear_coordenada_disponible(nivel, &posicion_baldosa_pinche, numero_nivel);
        nivel->obstaculos[i].tipo = BALDOSA_PINCHE;
        nivel->obstaculos[i].posicion = posicion_baldosa_pinche;
        nivel->tope_obstaculos++;
    }
    
    for (int i = 0; i < cantidad_monedas; i++) {
        coordenada_t posicion_monedas;
        crear_coordenada_disponible(nivel, &posicion_monedas, numero_nivel);
        nivel->herramientas[nivel->tope_herramientas].tipo = MONEDA;
        nivel->herramientas[nivel->tope_herramientas].posicion = posicion_monedas;
        nivel->tope_herramientas++;
    }
    
    if (hay_bomba) {
        coordenada_t posicion_bomba;
        crear_coordenada_disponible(nivel, &posicion_bomba, numero_nivel);
        nivel->obstaculos[nivel->tope_obstaculos].tipo = BOMBA;
        nivel->obstaculos[nivel->tope_obstaculos].posicion = posicion_bomba;
        nivel->tope_obstaculos++;

        coordenada_t posicion_interruptor;
        crear_coordenada_disponible(nivel, &posicion_interruptor, numero_nivel);
        nivel->herramientas[nivel->tope_herramientas].tipo = INTERRUPTOR;
        nivel->herramientas[nivel->tope_herramientas].posicion = posicion_interruptor;
        nivel->tope_herramientas++;
    } else {
        coordenada_t posicion_llave;
        crear_coordenada_disponible(nivel, &posicion_llave, numero_nivel);
        nivel->herramientas[nivel->tope_herramientas].tipo = LLAVE;
        nivel->herramientas[nivel->tope_herramientas].posicion = posicion_llave;
        nivel->tope_herramientas++;
    } 

    for (int i = 0; i < cantidad_guardia; i++) {
        coordenada_t posicion_guardia_robot;
        crear_coordenada_disponible(nivel, &posicion_guardia_robot, numero_nivel);
        nivel->obstaculos[nivel->tope_obstaculos].tipo = GUARDIA;
        nivel->obstaculos[nivel->tope_obstaculos].posicion = posicion_guardia_robot;
        nivel->tope_obstaculos++;

        coordenada_t posicion_baldoza_transportadora;
        crear_coordenada_disponible(nivel, &posicion_baldoza_transportadora, numero_nivel);
        nivel->herramientas[nivel->tope_herramientas].tipo = BALDOSA_TELETRANSPORTADORA;
        nivel->herramientas[nivel->tope_herramientas].posicion = posicion_baldoza_transportadora;
        nivel->tope_herramientas++;
    }   

}

int estado_juego(juego_t juego) {
    if ((juego.nivel_actual == CUARTO_NIVEL) && (juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual].salida.fil)
         && (juego.personaje.posicion.col == juego.niveles[juego.nivel_actual].salida.col) && (juego.personaje.tiene_llave)
         && (juego.personaje.movimientos > 0)) {
        return 1;
    } else if (juego.personaje.movimientos <= 0){
        return -1;
    } else {
        return 0;
    }
}

int estado_nivel(personaje_t personaje, coordenada_t salida) {
    if ((personaje.posicion.fil == salida.fil) && (personaje.posicion.col == salida.col) && (personaje.tiene_llave)) {
        return 1;
    } else {
        return 0;
    }
}


void crear_matriz_de_nivel (nivel_t nivel, int numero_nivel, char matriz[MAX_PAREDES][MAX_PAREDES], 
    int dimension, personaje_t personaje) {

    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            matriz[i][j] = VACIO;
        }
    }

    for(int i = 0; i < nivel.tope_paredes; i++) {
        matriz[nivel.paredes[i].fil][nivel.paredes[i].col] = PAREDES;
    }
    matriz[nivel.entrada.fil][nivel.entrada.col] = ENTRADA;

    if (personaje.tiene_llave) {
        matriz[nivel.salida.fil][nivel.salida.col] = SALIDA;
    }
    
    for(int i = 0; i < nivel.tope_obstaculos; i++) {
        matriz[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = nivel.obstaculos[i].tipo;
    }
    for(int i = 0; i < nivel.tope_herramientas; i++) {
        matriz[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = nivel.herramientas[i].tipo;
    }
}

void mostrar_juego(juego_t juego) {
    system("clear");
    int dimension = DIMENSION_MENOR;

    if(juego.nivel_actual % 2 == 0) {
        dimension = DIMENSION_MAYOR;
    }

    char matriz[MAX_PAREDES][MAX_PAREDES];
    crear_matriz_de_nivel(juego.niveles[juego.nivel_actual-1], juego.nivel_actual, matriz, dimension, juego.personaje);

    matriz[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

   for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            printf(" %c ", matriz[i][j]);
        }
        printf("\n");
    }
}

void cargar_personaje(personaje_t* personaje, char tipo_personaje) {
    personaje->tipo = tipo_personaje;
    personaje->movimientos = MOVIMIENTOS_INICIALES;
    personaje->murio = false;
    personaje->presiono_interruptor = false;
    personaje->tiene_llave = false;
}

void inicializar_juego(juego_t* juego, char tipo_personaje) {
    personaje_t personaje;
    cargar_personaje(&personaje, tipo_personaje);
    juego->personaje = personaje;
    
    nivel_t nivel_uno;
    nivel_t nivel_dos;
    nivel_t nivel_tres;
    nivel_t nivel_cuatro;
    
    inicializar_nivel(&nivel_uno, PRIMER_NIVEL, 4, 2, false);
    inicializar_nivel(&nivel_dos, SEGUNDO_NIVEL, 6, 3, false);
    inicializar_nivel(&nivel_tres, TERCER_NIVEL, 6, 3, true);
    inicializar_nivel(&nivel_cuatro, CUARTO_NIVEL, 10, 4, true);

    juego->niveles[0] = nivel_uno;
    juego->niveles[1] = nivel_dos;
    juego->niveles[2] = nivel_tres;
    juego->niveles[3] = nivel_cuatro;

    juego->nivel_actual = 1;

    juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual-1].entrada.fil;
    juego->personaje.posicion.col = juego->niveles[juego->nivel_actual-1].entrada.col;
}

void obtener_siguiente_posicion(coordenada_t* posicion, char movimiento) {
     if (movimiento == DERECHA) {
           posicion->fil = posicion->fil;
           posicion->col = posicion->col + 1;
    }

    if (movimiento == IZQUIERDA) {
           posicion->fil = posicion->fil;
           posicion->col = posicion->col - 1;
    } 
    if (movimiento == ARRIBA) {
           posicion->fil = posicion->fil - 1;
           posicion->col = posicion->col;
    }
    if (movimiento == ABAJO) {
           posicion->fil = posicion->fil + 1;
           posicion->col = posicion->col;
    }
}

void sacar_elemento_en_posicion(elemento_t array_elementos[MAX_HERRAMIENTAS], int* tope_herramientas, coordenada_t coordenada_posicion) {
  bool encontre_elemento = false;
  int i = 0;
    while (!encontre_elemento) {
        if ((array_elementos[i].posicion.col == coordenada_posicion.col) && (array_elementos[i].posicion.fil == coordenada_posicion.fil)) {
            encontre_elemento = true;
        } else {
            i++;
        }
    }

    for (int j = i; j < *tope_herramientas - 1; j++) {
        array_elementos[j] = array_elementos[j + 1];
    }
    
    *tope_herramientas -= 1;
}

void ir_a_siguiente_baldosa_teletransportadora (elemento_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, coordenada_t* coordenada_posicion) {
    bool encontre_la_baldosa = false;
    int i = 0;

    while (!encontre_la_baldosa){
        if ((herramientas[i].tipo == BALDOSA_TELETRANSPORTADORA) && (herramientas[i].posicion.col == coordenada_posicion->col)
        && (herramientas[i].posicion.fil == coordenada_posicion->fil)) {
            encontre_la_baldosa = true;
        }
        i++;
    }
    bool encontre_la_siguiente_baldosa = false;
    while (!encontre_la_siguiente_baldosa){
        if (i == tope_herramientas){
            i = 0;
        }
        if ((herramientas[i].tipo == BALDOSA_TELETRANSPORTADORA)) {
            encontre_la_siguiente_baldosa = true;
        } else {
            i++;
        }
        
    }

    coordenada_posicion->col = herramientas[i].posicion.col;
    coordenada_posicion->fil = herramientas[i].posicion.fil;
}

void mover_personaje(juego_t* juego, char movimiento) {
    coordenada_t siguiente_posicion = juego->personaje.posicion;
    obtener_siguiente_posicion(&siguiente_posicion, movimiento);
    char matriz[MAX_PAREDES][MAX_PAREDES];
     int dimension = DIMENSION_MENOR;

    if(juego->nivel_actual % 2 == 0) {
        dimension = DIMENSION_MAYOR;
    }
 
    bool detener_personaje = false;
    juego->personaje.movimientos--;

    while (!hay_pared(&(juego->niveles[juego->nivel_actual-1]), &siguiente_posicion) && !detener_personaje) {        
        juego->personaje.posicion.fil = siguiente_posicion.fil;
        juego->personaje.posicion.col = siguiente_posicion.col;

        crear_matriz_de_nivel(juego->niveles[juego->nivel_actual-1], juego->nivel_actual, matriz, dimension, juego->personaje);
        char contenido_celda = matriz[juego->personaje.posicion.fil][juego->personaje.posicion.col];
        char tipo_personaje = juego->personaje.tipo;

        if (contenido_celda == BALDOSA_PINCHE) {
            if ((tipo_personaje != PURO_HUESO) && (tipo_personaje != POLLITO)) {
                juego->personaje.movimientos -= 2;
            }
        }

        if (contenido_celda == GUARDIA) {
            if ((tipo_personaje != JOHNNY_BRAVO) && (tipo_personaje != CORAJE)) {
                juego->personaje.movimientos = 0;
            }
        }

        if (contenido_celda == BOMBA) {                
            juego->personaje.movimientos = 0;
        }

        if (contenido_celda == INTERRUPTOR) {
            coordenada_t posicion_llave;
            crear_coordenada_disponible(juego->niveles, &posicion_llave, juego->nivel_actual);
            juego->niveles->herramientas[juego->niveles->tope_herramientas].tipo = LLAVE;
            juego->niveles->herramientas[juego->niveles->tope_herramientas].posicion = posicion_llave;
            juego->niveles->tope_herramientas++;
            juego->personaje.presiono_interruptor = true;
        }

        if (contenido_celda == LLAVE) {
            sacar_elemento_en_posicion( juego->niveles[juego->nivel_actual - 1].herramientas, 
            &juego->niveles[juego->nivel_actual - 1].tope_herramientas, juego->personaje.posicion);
            juego->personaje.tiene_llave = true;
        }

        if (contenido_celda == BALDOSA_TELETRANSPORTADORA) {
            ir_a_siguiente_baldosa_teletransportadora(juego->niveles[juego->nivel_actual - 1].herramientas, juego->niveles[juego->nivel_actual-1].tope_herramientas,
                &juego->personaje.posicion);
            detener_personaje = true;
        }

        if (contenido_celda == MONEDA) {
            sacar_elemento_en_posicion(juego->niveles[juego->nivel_actual - 1].herramientas, 
                &juego->niveles[juego->nivel_actual - 1].tope_herramientas, juego->personaje.posicion);
            juego->personaje.movimientos += 1;
        }

        if ((juego->personaje.movimientos <= 0) && ((juego->personaje.tipo == BELLOTA) || (juego->personaje.tipo == BLUE)) && !(juego->personaje.murio)){
            juego->personaje.movimientos = 10;
            juego->personaje.murio = true;
        }

        if (juego->personaje.movimientos <= 0) {
            juego->personaje.murio = true;
            detener_personaje = true;
        }

        int estado_del_nivel = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual - 1].salida);

        if (estado_del_nivel == 1) {
            juego->nivel_actual += 1;
        }

        detener_el_tiempo(0.5);
        mostrar_juego(*juego);
        obtener_siguiente_posicion(&siguiente_posicion, movimiento);
    }
}



