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


/* pre: Funcion que recibe un puntero a variables de tipo nivel_t y coordenada_t
post: Retorna un booleano, false si no se encuentra el caracter que representa una pared en la coordenada especificada, true si se
encuentra  */
bool hay_pared(nivel_t* nivel, coordenada_t* coordenada) {
    for (int i = 0; i < nivel->tope_paredes; i++) {
        if(nivel->paredes[i].fil == coordenada->fil && nivel->paredes[i].col == coordenada->col) {
            return true;
        }
    }
    return false;
}
/* pre: Funcion que recibe un puntero a variables de tipo nivel_t y coordenada_t
post: Retorna un booleano, false si la coordenada esta ocupada por una herramienta, obstaculo, pared, entrada o salida, false si
coordenada esta ocupada y no se puede agregar un objeto a la coordenada */
bool es_coordenada_disponible(nivel_t* nivel, coordenada_t* coordenada) {
    bool hay_pared_en_posicion = hay_pared(nivel, coordenada);
    bool pude_ubicar = false;
    
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

    return pude_ubicar;
}

/* pre: Metodo que recibe punteros a variables de tipo nivel_t y coordenada_t y una variable de tipo int entre 1 y 4
post: Determina si la coordenada brindada esta disponible para ubicar objetos  */
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

       pude_ubicar = es_coordenada_disponible(nivel, coordenada);
    }
}

/* pre: Metodo que recibe un int con la cantidad de baldosas pinches segun el nivel en el que se encuente (4, 6 o 10), un int 
que representa en nivel que se esta evaluando (entre 1 y 4) y un puntero a la variable de tipo nivel_t
post: Ubica los obstaculos tipo baldosa pinche en la matriz de juego adyacentemente */
void crear_baldosas_pinches(int cantidad_baldosas_pinches, nivel_t* nivel, int numero_nivel){
    coordenada_t posicion_baldosa_pinche;
    crear_coordenada_disponible(nivel, &posicion_baldosa_pinche, numero_nivel);
    nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSA_PINCHE;
    nivel->obstaculos[nivel->tope_obstaculos].posicion = posicion_baldosa_pinche;
    printf("fila random: %i \n", posicion_baldosa_pinche.fil);
    printf("columna random: %i \n", posicion_baldosa_pinche.col);
    nivel->tope_obstaculos++;

    for (int i = 0; i < cantidad_baldosas_pinches - 1; i++) {
        coordenada_t nuevo_piche_derecha;
        nuevo_piche_derecha.col = posicion_baldosa_pinche.col+1;
        nuevo_piche_derecha.fil = posicion_baldosa_pinche.fil;
        coordenada_t nuevo_piche_izq;
        nuevo_piche_izq.col = posicion_baldosa_pinche.col-1;
        nuevo_piche_izq.fil = posicion_baldosa_pinche.fil;
        coordenada_t nuevo_piche_arriba;
        nuevo_piche_arriba.col = posicion_baldosa_pinche.col;
        nuevo_piche_arriba.fil = posicion_baldosa_pinche.fil-1;
        coordenada_t nuevo_piche_abajo;
        nuevo_piche_abajo.col = posicion_baldosa_pinche.col;
        nuevo_piche_abajo.fil = posicion_baldosa_pinche.fil+1;

        printf("ENTRE AL FOR\n");
        printf("posicion fila baldosa pinche %i \n", posicion_baldosa_pinche.fil);
        printf("posicion columna baldosa pinche %i \n", posicion_baldosa_pinche.col);
        if (es_coordenada_disponible(nivel, &nuevo_piche_derecha)) {
            printf("ENTRE ACAAA\n");
            nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSA_PINCHE;
            nivel->obstaculos[nivel->tope_obstaculos].posicion = nuevo_piche_derecha;
            nivel->tope_obstaculos++;
        } else if (es_coordenada_disponible(nivel, &nuevo_piche_izq)) {
            printf("ENTRE AQUIIII\n");
            nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSA_PINCHE;
            nivel->obstaculos[nivel->tope_obstaculos].posicion = nuevo_piche_izq;
            nivel->tope_obstaculos++;
        } else if (es_coordenada_disponible(nivel, &nuevo_piche_arriba)) {
            printf("ADSADSADAS\n");
            nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSA_PINCHE;
            nivel->obstaculos[nivel->tope_obstaculos].posicion = nuevo_piche_arriba;
            nivel->tope_obstaculos++;
        } else if (es_coordenada_disponible(nivel, &nuevo_piche_abajo)) {
            printf("ENTRE QWEWQEWQEWQE\n");
            nivel->obstaculos[nivel->tope_obstaculos].tipo = BALDOSA_PINCHE;
            nivel->obstaculos[nivel->tope_obstaculos].posicion = nuevo_piche_abajo;
            nivel->tope_obstaculos++;   
        } else {
            printf("salio todo malardo\n");
        }
    }
}

/* pre: Metodo que recibe la cantidad de monedas a ubicar en la matriz de juego (valores posibles:) 2, 3 o 5), un puntero
a la variable de tipo nivel_t y un int que representa el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4)
post: Ubica las herramientas tipo moneda AlgoCOins en la matriz de juego */
void crear_monedas(int cantidad_monedas, nivel_t* nivel, int numero_nivel) {
    for (int i = 0; i < cantidad_monedas; i++) {
        coordenada_t posicion_monedas;
        crear_coordenada_disponible(nivel, &posicion_monedas, numero_nivel);
        nivel->herramientas[nivel->tope_herramientas].tipo = MONEDA;
        nivel->herramientas[nivel->tope_herramientas].posicion = posicion_monedas;
        nivel->tope_herramientas++;
    }
}

/* pre: Metodo que recibe un puntero a la variable de tipo nivel_t y un int que representa
el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4) 
post: Ubica los obstaculos tipo bomba en la matriz de juego  */
void crear_bomba(nivel_t* nivel, int numero_nivel) {
    coordenada_t posicion_bomba;
    crear_coordenada_disponible(nivel, &posicion_bomba, numero_nivel);
    nivel->obstaculos[nivel->tope_obstaculos].tipo = BOMBA;
    nivel->obstaculos[nivel->tope_obstaculos].posicion = posicion_bomba;
    nivel->tope_obstaculos++;
}

/* pre: Metodo que recibe un puntero a la variable de tipo nivel_t y un int que representa
el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4)
post: Ubica la herramienta tipo interruptor en la matriz de juego  */
 void crear_interruptor(nivel_t* nivel, int numero_nivel){
    coordenada_t posicion_interruptor;
    crear_coordenada_disponible(nivel, &posicion_interruptor, numero_nivel);
    nivel->herramientas[nivel->tope_herramientas].tipo = INTERRUPTOR;
    nivel->herramientas[nivel->tope_herramientas].posicion = posicion_interruptor;
    nivel->tope_herramientas++;
}

/* pre: Metodo que recibe un puntero a la variable de tipo nivel_t y un int que representa
el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4)
post: Ubica la herramienta tipo llave en la matriz de juego  */
 void crear_llave(nivel_t* nivel, int numero_nivel) {
    coordenada_t posicion_llave;
    crear_coordenada_disponible(nivel, &posicion_llave, numero_nivel);
    nivel->herramientas[nivel->tope_herramientas].tipo = LLAVE;
    nivel->herramientas[nivel->tope_herramientas].posicion = posicion_llave;
    nivel->tope_herramientas++;
}

/* pre: Metodo que recibe un puntero a la variable de tipo nivel_t y un int que representa
el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4)
post: Ubica las herramientas tipo baldosa teletransportadora en la matriz de juego  */
void crear_baldosa_teletransportadora(nivel_t* nivel, int numero_nivel) {
    coordenada_t posicion_baldoza_transportadora;
    crear_coordenada_disponible(nivel, &posicion_baldoza_transportadora, numero_nivel);
    nivel->herramientas[nivel->tope_herramientas].tipo = BALDOSA_TELETRANSPORTADORA;
    nivel->herramientas[nivel->tope_herramientas].posicion = posicion_baldoza_transportadora;
    nivel->tope_herramientas++;
}

/* pre: Metodo que recibe un puntero a la variable de tipo nivel_t, un int que representa
el numero de nivel que se debe evaluar (valores posibles: 1, 2, 3, 4) y un int que representa la cantidad de
obstaculos tipo guardias robot a ubicar en la matriz de juego.
post: Ubica los obstaculos tipo guardia robot en la matriz de juego  */
void crear_guardia_robot(nivel_t* nivel, int numero_nivel, int cantidad_guardias) {
     for (int i = 0; i < cantidad_guardias; i++) {
        coordenada_t posicion_guardia_robot;
        crear_coordenada_disponible(nivel, &posicion_guardia_robot, numero_nivel);
        nivel->obstaculos[nivel->tope_obstaculos].tipo = GUARDIA;
        nivel->obstaculos[nivel->tope_obstaculos].posicion = posicion_guardia_robot;
        nivel->tope_obstaculos++;
        crear_baldosa_teletransportadora(nivel, numero_nivel);
    }
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardias, bool hay_bomba) {
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

    crear_baldosas_pinches(cantidad_baldosas_pinches, nivel, numero_nivel);
    crear_monedas(cantidad_monedas, nivel, numero_nivel);

    if (hay_bomba) {
        crear_bomba(nivel, numero_nivel);
        crear_interruptor(nivel, numero_nivel);
       
    } else {
       crear_llave(nivel, numero_nivel);
    } 

    crear_guardia_robot(nivel, numero_nivel, cantidad_guardias);
             
}

int estado_juego(juego_t juego) {
    if ((juego.nivel_actual == CUARTO_NIVEL) && (juego.personaje.posicion.fil == juego.niveles[juego.nivel_actual-1].salida.fil)
         && (juego.personaje.posicion.col == juego.niveles[juego.nivel_actual-1].salida.col) && (juego.personaje.tiene_llave)
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

/* pre: Metodo que recibe un nivel con todas sus estructuras validas, un int que representa el nivel en el que se esta jugando y
una matriz de caracteres que representa la matriz jugable
post: Define los espacios de la matriz ocupados por paredes, entrada, salida, herramientas y obstaculos */
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
    //system("clear");
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

/* pre: Metodo que recibe una variable de tipo personaje con todas sus estructuras validas y un caracter que representa
el personaje con el que se va a jugar (valores posibles: C, B, S, H, P, J)
post:  Inicializa los valores de la estructura del personaje*/
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

    juego->nivel_actual = 4;

    juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual-1].entrada.fil;
    juego->personaje.posicion.col = juego->niveles[juego->nivel_actual-1].entrada.col;
}

/* pre: Metodo que recibe un puntero a la variable de tipo coordenada_t y un caracter que representa el movimiento
que el usuario desea realizar (valores posibles: D, A, W, S)
post:  Actualiza la posicion del personaje de acuerdo al caracter ingresado*/
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

/* pre: Metodo que recibe un array de tipo elemento_t, un puntero al tope de herramientas y una variable de tipo coordenada_t
post: Elimina la herramienta del array de acuerdo a la posicion recibida y actualiza el tope de herramientas */
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

/* pre: Metodo que recibe un array de tipo elemento_t, un int que representa el tope del vector de herramientas y un puntero a la 
variable de tipo coordenada_t
post: Actualiza la coordenada de la posicion del personaje a otra herramienta de tipo baldosa teletransportadora 
que se encuentre en el array de herramientas */
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

/* pre: 
post:  */
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

    while (!detener_personaje && !hay_pared(&(juego->niveles[juego->nivel_actual-1]), &siguiente_posicion)) {        
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

        detener_el_tiempo(0.5);
        mostrar_juego(*juego);

        if ((estado_del_nivel == 1) && (juego->nivel_actual < 4)) {
            juego->nivel_actual += 1;
            detener_personaje = true;
        }

        if ((estado_del_nivel == 1) && (juego->nivel_actual = 4)) {
            detener_personaje = true;
        }
        obtener_siguiente_posicion(&siguiente_posicion, movimiento);
    }
}



