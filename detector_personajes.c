#include <stdio.h>
#include <stdlib.h>

#define DULCE 'D'
#define SALADO 'S'
#define AMARGO 'A'
#define AZUL 'A'
#define AMARILLO 'Y'
#define VERDE 'V'
#define NEGRO 'N'
#define BLANCO 'B'
#define ROSA 'R'
#define ALTURA_JHONNY_BRAVO 180
#define ALTURA_BELLOTA 120
#define ALTURA_POLLITO 50
#define ALTURA_BLUE 140
#define ALTURA_PURO_HUESO 200
#define ALTURA_CORAJE 30
#define PUNTAJE_COLOR_ROSA 5
#define PUNTAJE_COLOR_AMARILLO 5
#define PUNTAJE_COLOR_NEGRO 15
#define PUNTAJE_COLOR_BLANCO 15
#define PUNTAJE_COLOR_AZUL 20
#define PUNTAJE_COLOR_VERDE 20
#define PUNTAJE_SABOR_SALADO 5
#define PUNTAJE_SABOR_DULCE 15
#define PUNTAJE_SABOR_AMARGO 20
#define FECHA_NACIMIENTO_MINIMA 1988
#define FECHA_NACIMIENTO_MAXIMA 2008
#define TAMANIO_ZAPATO_MAXIMO 47
#define TAMANIO_ZAPATO_MINIMO 33
#define TAMANIO_NO_USA_ZAPATO 0
#define ALTURA_MINIMA 10
#define ALTURA_MAXIMA 250
#define MULTIPLICADOR_NO_USA_ZAPATOS 1
#define CORAJE 'C'
#define BLUE 'B'
#define BELLOTA 'S'
#define PURO_HUESO 'H'
#define POLLITO 'P'
#define JOHNNY_BRAVO 'J'

/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Guardaen en una variable el int ingresado por el usuario. */
void preguntarFechaDeNacimiento(int* fechaDeNacimiento) {
    printf("¿Cual es tu año de nacimiento? \n");
    scanf("%i", fechaDeNacimiento);
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo char.
post: Guarda en una variable el char ingresado por el usuario. */
void preguntarPreferenciaDeSabor( char* preferenciaDeSabor) {
    printf("¿Que sabor preferis? Opciones: Dulce, Salado, Amargo. Ingresa la inicial de tu eleccion en mayuscula: \n");
    scanf(" %c", preferenciaDeSabor);
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Guarda en una variable el int ingresado por el usuario. */
void preguntarTallaDeZapato(int* tallaDeZapatos) {
    printf("¿Cual es tu talla de zapatos? Ingresar un numero entre 33 y 47 o 0 si no usas zapatos: \n");
    scanf("%i", tallaDeZapatos);
}
/* pre: Funcion tipo procedimiento que recibe un puntero a la variable de tipo char colorFavorito.
post: Guarda en la variable colorFavorito el char ingresado por el usuario. */
void preguntarColorFavorito(char* colorFavorito) {
    printf("¿Cual es tu color favorito? Ingresa la inicial en mayuscula (Como excepcion, para amarillo ingresa (Y)): \n");
    scanf(" %c", colorFavorito);
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Guarda en una variable el int ingresado por el usuario. */
void preguntarAlura(int *alturaPersonaje) {
  printf("¿Cual es tu altura? En centimetros: \n");
  scanf("%i", alturaPersonaje);
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Verifica que el valor de la variable concuerde con las limitaciones impuestas, si no, le vuelve a preguntar
al usuario hasta que se ingrese un numero valido. */
void enCasoDeErrorFechaDeNacimiento(int *fechaDeNacimiento){
    while ((*fechaDeNacimiento <= FECHA_NACIMIENTO_MINIMA) || (*fechaDeNacimiento >= FECHA_NACIMIENTO_MAXIMA)) {
        printf("No se reconoce su fecha de nacimiento, ingrese una fecha entre 1988 y 2008: \n");
        scanf("%i", fechaDeNacimiento);
    }
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo char.
post: Verifica que el valor de la variable concuerde con las limitaciones impuestas, si no, le vuelve a preguntar
al usuario hasta que se ingrese un caracter valido. */
void enCasoDeErrorPreferenciaDeSabor(char *preferenciaDeSabor){
    while ((*preferenciaDeSabor != DULCE) && (*preferenciaDeSabor != SALADO) && (*preferenciaDeSabor != AMARGO)) {
        printf("No se reconoce su preferencia de sabor, ingrese la inicial de Dulce (D), Salado (S) o Amargo (A), en mayuscula: \n");
        scanf(" %c", preferenciaDeSabor);
    }
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Verifica que el valor de la variable concuerde con las limitaciones impuestas, si no, le vuelve a preguntar
al usuario hasta que se ingrese un numero valido .*/
void enCasoDeErrorTallaDeZapato(int *tallaDeZapatos){
    while ((*tallaDeZapatos <= TAMANIO_ZAPATO_MINIMO || *tallaDeZapatos >= TAMANIO_ZAPATO_MAXIMO) && *tallaDeZapatos != TAMANIO_NO_USA_ZAPATO) {
        printf("No se reconoce su talla de zapato, ingrese un numero entre 33 y 47 o 0 si no usa zapatos: \n");
        scanf("%i", tallaDeZapatos);
    }
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo char.
post: Verifica que el valor de la variable concuerde con las limitaciones impuestas, si no, le vuelve a preguntar
al usuario hasta que se ingrese un caracter valido. */
void enCasoDeErrorColorFavorito(char *colorFavorito){
    while ((*colorFavorito != AZUL) && (*colorFavorito != AMARILLO) && (*colorFavorito != VERDE)
        && (*colorFavorito != NEGRO) && (*colorFavorito != BLANCO) && (*colorFavorito != ROSA)) { 
        printf("No se reconoce su color favorito, ingrese la inicial de Azul (A), Amarillo (Y), Verde (V), Negro (N), Blanco (B) o Rosa (R), en mayuscula: \n");
        scanf(" %c", colorFavorito); 
    }
}
/* pre: Funcion tipo procedimiento que recibe un puntero a una variable de tipo int.
post: Verifica que el valor de la variable concuerde con las limitaciones impuestas, si no, le vuelve a preguntar
al usuario hasta que se ingrese un numero valido. */
void enCasoDeErrorAltura(int *alturaPersonaje){
    while (*alturaPersonaje <= ALTURA_MINIMA || *alturaPersonaje >= ALTURA_MAXIMA) {
        printf("No se reconoce la altura ingresada, ingrese un valor entre 10 y 250: \n");
        scanf("%i", alturaPersonaje);
    }
}

/* pre : Funcion que recibe un char.
 post : Devuelve un puntaje de tipo int positivo de acuerdo al char ingresado */
int puntosPorColores(char color) {
    switch (color) {
    case ROSA:
        return PUNTAJE_COLOR_ROSA;
    case AMARILLO:
        return PUNTAJE_COLOR_AMARILLO;
    case NEGRO:
        return PUNTAJE_COLOR_NEGRO;
    case BLANCO:
        return PUNTAJE_COLOR_BLANCO;
    case AZUL:
        return PUNTAJE_COLOR_AZUL;
    case VERDE:
        return PUNTAJE_COLOR_VERDE;
    }
    return 0;
}

/* pre : Funcion que recibe un char.
 post : Devuelve un puntaje de tipo int positivo de acuerdo al char ingresado. */
int puntosPorSabor(char saborFavorito) {
    switch (saborFavorito){
    case SALADO:
        return PUNTAJE_SABOR_SALADO;
    case DULCE:
        return PUNTAJE_SABOR_DULCE;
    case AMARGO:
        return PUNTAJE_SABOR_AMARGO;
    }
    return 0;
}

/* pre : Funcion que recibe un int positivo.
 post : Devuelve un puntaje en int. */
int puntosPorNacimiento(int fechaDeNacimiento) {
     return ((fechaDeNacimiento % 20) + 1);
}

/* pre : Funcion que recibe un int positivo.
 post : Devuelve un multiplicador de acuerdo al int ingresado. */
int multiplicadorPorTallaDeZapato(int tallaDeZapatos) {
    if (tallaDeZapatos == TAMANIO_NO_USA_ZAPATO) {
        return MULTIPLICADOR_NO_USA_ZAPATOS;
    } else if ((tallaDeZapatos >= TAMANIO_ZAPATO_MINIMO) && (tallaDeZapatos <= 37)){
        return 2;
    } else if ((tallaDeZapatos >= 38) && (tallaDeZapatos <= 42)){
        return 3;
    } else if ((tallaDeZapatos >= 43) && (tallaDeZapatos <= TAMANIO_ZAPATO_MAXIMO)){
        return 4;
    }
    return 0;
}

/* pre: Funcion tipo procedimiento que recibe 2 parametros de tipo char y 3 de tipo int
post: Realiza la llamada a otras funciones para obtener valores con los que realiza calculos que luego 
almacena en una variable de tipo int. */
void calculoPuntajeTotal(char preferenciaDeSabor, char colorFavorito, int fechaDeNacimiento, int tallaDeZapatos, int *puntajeTotal) {
     *puntajeTotal = (puntosPorSabor(preferenciaDeSabor) + puntosPorColores(colorFavorito)
         + puntosPorNacimiento(fechaDeNacimiento)) * multiplicadorPorTallaDeZapato(tallaDeZapatos);
}
/* pre: Funcion tipo procedimiento que recibe dos ints positivos.
post: Devuelve impreso por pantalla el nombre del personaje obtenido. */
char calculoPersonajeFinal(int puntajeTotal, int alturaPersonaje) {
     if ((puntajeTotal >= 1) && (puntajeTotal <= 80)) {
        int diferenciaPersonaje1 = abs(ALTURA_JHONNY_BRAVO - alturaPersonaje);
        int diferenciaPersonaje2 = abs(ALTURA_CORAJE - alturaPersonaje);
        if (diferenciaPersonaje1 > diferenciaPersonaje2){
            printf("El sistema detecto al personaje: Coraje.\n");
            return CORAJE;
        } else {
            printf("El sistema detecto al personaje: Jhonny Bravo.\n");
            return JOHNNY_BRAVO;
        }
    } else if ((puntajeTotal >= 81) && (puntajeTotal <= 160)) {
        int diferenciaPersonaje1 = abs(ALTURA_PURO_HUESO - alturaPersonaje);
        int diferenciaPersonaje2 = abs(ALTURA_POLLITO - alturaPersonaje);
        if (diferenciaPersonaje1 > diferenciaPersonaje2){
            printf("El sistema detecto al personaje: Pollito.\n");
            return POLLITO;
        } else {
            printf("El sistema detecto al personaje: Puro Hueso.\n");
            return PURO_HUESO;
        }
    } else if ((puntajeTotal >= 161) && (puntajeTotal <= 240)) {
        int diferenciaPersonaje1 = abs(ALTURA_BLUE - alturaPersonaje);
        int diferenciaPersonaje2 = abs(ALTURA_BELLOTA - alturaPersonaje);
        if (diferenciaPersonaje1 > diferenciaPersonaje2){
            printf("El sistema detecto al personaje: Bellota.\n");
            return BELLOTA;
        } else {
            printf("El sistema detecto al personaje: Blue.\n");
            return BLUE;
        }
    }
    return CORAJE;
}

void detector_de_personajes(char* personaje_detectado) {

    char preferenciaDeSabor;
    char colorFavorito;
    int tallaDeZapatos = 0 ;
    int fechaDeNacimiento = 0;
    int alturaPersonaje = 0;
    int puntajeTotal = 0;

    preguntarFechaDeNacimiento(&fechaDeNacimiento);
    enCasoDeErrorFechaDeNacimiento(&fechaDeNacimiento);

    preguntarPreferenciaDeSabor(&preferenciaDeSabor);
    enCasoDeErrorPreferenciaDeSabor(&preferenciaDeSabor);

    preguntarTallaDeZapato(&tallaDeZapatos);
    enCasoDeErrorTallaDeZapato(&tallaDeZapatos);

    preguntarColorFavorito(&colorFavorito);
    enCasoDeErrorColorFavorito(&colorFavorito);

    preguntarAlura(&alturaPersonaje);
    enCasoDeErrorAltura(&alturaPersonaje);

    calculoPuntajeTotal(preferenciaDeSabor, colorFavorito, fechaDeNacimiento, tallaDeZapatos, &puntajeTotal);

    *personaje_detectado = calculoPersonajeFinal(puntajeTotal, alturaPersonaje);

}