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
