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
