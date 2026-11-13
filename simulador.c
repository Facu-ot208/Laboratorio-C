// se implementan los calculos fisicos y explicacion del escenario

#include <stdio.h>
#include <math.h>
#include "simulador.h" //permite utilizar las constantes, estructuras y prototipos que definimos

// con la siguiente funcion nos muestra la explicacion fisica del apartado A, ley de inercia
void mostrarInercia() {

    printf("\n Apartado A: LEY DE INERCIA \n");

    printf("Los motores principales de Orion se encuentran apagados.\n");
    printf("La nave conserva su movimiento debido a la inercia.\n");
    printf("Sin embargo, la gravedad terrestre sigue actuando sobre Orion.\n");
    printf("Esta fuerza gravitatoria modifica progresivamente su velocidad y direccion.\n");
}

// apartado B: calculo de energia cinetica
double calcularEnergiaCinetica(Orion nave) {

    double energia; // energia: alamcena el resultado

    energia = 0.5 * nave.masa * nave.velocidad * nave.velocidad;

    return energia; //devuelve el resultado al programa principal
}

// apartado C: calculamos la distancia hasta el punto de equilibrio gravitatorio por las masas 
// y el calculo del trabajo externo por unidad de masa
double calcularDistanciaEquilibrio() {

    double distancia;
    distancia = DISTANCIA_TIERRA_LUNA / 
                (1 + sqrt(MASA_LUNA / MASA_TIERRA)); 
    return distancia;
}

double calcularTrabajoExterno(Orion nave) {

    double distanciaEquilibrio;
    double distanciaInicial;
    double potencialInicial;
    double potencialFinal;
    double energiaCineticaInicial;
    double trabajoExterno;

    distanciaEquilibrio = calcularDistanciaEquilibrio();

    distanciaInicial = RADIO_TIERRA + nave.altura;

    potencialInicial = // energia potencial gravitatoria por unidad de masa al comenzar
        -(G * MASA_TIERRA / distanciaInicial) // atraccion gravitatoria de la tierra
        -(G * MASA_LUNA / (DISTANCIA_TIERRA_LUNA - distanciaInicial)); // atraccion gravitatoria de la luna

    potencialFinal = // energia potencial gravitatoria por unidad de masa en el punto de equilibrio
        -(G * MASA_TIERRA / distanciaEquilibrio)
        -(G * MASA_LUNA / (DISTANCIA_TIERRA_LUNA - distanciaEquilibrio));

    energiaCineticaInicial = 0.5 * nave.velocidad * nave.velocidad;

    trabajoExterno = potencialFinal - potencialInicial - energiaCineticaInicial;
    // en este ultimo, se supone que orion llega al punto de equilibrio con velodiad final cero
    return trabajoExterno;
}

// apartado D: comparacion energetica ida (Tierra-Luna) vs regreso (Luna-Tierra)
void mostrarAnalisisCombustible(void) {
    printf("\n--- APARTADO D: IDA (Tierra-Luna) vs regreso (Luna-Tierra) ---\n");
    printf("La tierra tiene mucha más masa que la luna (unas 81 veces), \n");
    printf("por eso su pozo de potencial gravitatorio es mucho mas profundo.\n\n");
    printf("Velocidad de escape desde la Tierra: aprox. 11,2 km/s\n");
    printf("Velocidad de escape desde la Luna:   aprox. 2,4 km/s\n\n");
    printf("Ir a la Luna implica salir del pozo terrestre: hace falta mucha\n");
    printf("energia (delta-v alto), y por lo tanto mucho combustible.\n");
    printf("Volver implica salir del pozo lunar, que es poco profundo, y luego\n");
    printf("la Tierra ayuda atrayendo a la nave: hace falta poca energia.\n\n");
    printf("Ademas, el combustible gastado en la ida tambien debe ser\n");
    printf("impulsado, lo que obliga a llevar aun mas combustible (ecuacion\n");
    printf("del cohete). Por eso la ida requiere una masa de combustible\n");
    printf("significativamente mayor que el regreso.\n");
}

    
