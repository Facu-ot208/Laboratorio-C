// se implementan los calculos fisicos y explicacion del escenario

#include <stdio.h>
#include <math.h>
#include "simulador.h" //permite utilizar las constantes, estructuras y prototipos que definimos

// con la siguiente funcion nos muestra la explicacion fisica del apartado A, ley de inercia
void mostrarInercia(void) {

    printf("\n Apartado A: LEY DE INERCIA \n");

    printf("Los motores principales de Orion se encuentran apagados.\n");
    printf("La nave conserva su movimiento debido a la inercia.\n");
    printf("Sin embargo, la gravedad terrestre sigue actuando sobre Orion.\n");
    printf("Esta fuerza gravitatoria modifica progresivamente su velocidad y direccion.\n");
    printf("Mientras Orion se aleja, la gravedad terrestre lo frena (desacelera),\n");
    printf("porque la fuerza apunta hacia la Tierra, opuesta al movimiento.\n");
    printf("Segun la 1.a Ley de Newton, sin esa fuerza la nave seguiria con\n");
    printf("velocidad constante en linea recta.\n");
}

// apartado B: calculo de energia cinetica
double calcularEnergiaCinetica(const Orion *nave) {

    double energia; // energia: almacena el resultado

    energia = 0.5 * nave->masa * nave->velocidad * nave->velocidad;

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
    printf("\n--- APARTADO D: IDA (Tierra-Luna) vs REGRESO (Luna-Tierra) ---\n");
    printf("La Tierra tiene mucha mas masa que la Luna (unas 81 veces),\n");
    printf("por eso su pozo de potencial gravitatorio es mucho mas profundo.\n\n");
    printf("Velocidad de escape desde la superficie de la Tierra: aprox. 11,2 km/s\n");
    printf("Velocidad de escape desde la superficie de la Luna:   aprox. 2,4 km/s\n");
    printf("Energia por unidad de masa (v^2 / 2): Tierra aprox. 6,3e7 J/kg,\n");
    printf("Luna aprox. 2,9e6 J/kg. Salir de la Tierra cuesta unas 22 veces mas.\n\n");
    printf("Ir a la Luna implica salir del pozo terrestre: hace falta mucha\n");
    printf("energia (delta-v alto), y por lo tanto mucho combustible.\n");
    printf("Volver implica salir del pozo lunar, que es poco profundo, y luego\n");
    printf("la Tierra ayuda atrayendo a la nave: hace falta poca energia.\n\n");
    printf("Ademas, el combustible que todavia no se uso tambien hay que\n");
    printf("acelerarlo junto con la nave, y por eso hace falta mucho mas (ecuacion\n");
    printf("del cohete). Por eso la ida requiere una masa de combustible\n");
    printf("significativamente mayor que el regreso.\n");
}

// reporte final: resume los datos y el resultado de la mision
void mostrarReporteFinal(const Orion *nave, double energiaCinetica,
                         double trabajoExterno) {
    double vEscape = sqrt(2.0 * G * MASA_TIERRA / (RADIO_TIERRA + nave->altura));

    printf("\n======== REPORTE FINAL ========\n");
    printf("Masa de la nave:        %.1f kg \n", nave->masa);
    printf("Velocidad de inyeccion: %.1f m/s \n", nave->velocidad);
    printf("Altura de la orbita:    %.1f m \n", nave->altura);
    printf("Energia cinetica:       %.3e J \n", energiaCinetica);
    printf("Trabajo extra minimo:   %.3e J/kg \n", trabajoExterno);
    printf("Velocidad de escape:    %.1f m/s \n", vEscape);

    if (nave->velocidad >= vEscape)
        printf("Resultado: la nave ESCAPA de la gravedad terrestre.\n");
    else if (trabajoExterno <= 0)
        printf("Resultado: la nave LLEGA al punto de equilibrio Tierra-Luna.\n");
    else
        printf("Resultado: NO llega. Faltan %.3e J/kg.\n", trabajoExterno);
    printf("===================\n");
}

// carga los datos iniciales de la nave en la estructura (se recibe por puntero)
// distancia = distancia al CENTRO de la Tierra = radio terrestre + altura
void inicializarNave(Orion *nave, double masa, double velocidad, double altura) {
    double distanciaAlCentro = RADIO_TIERRA + altura;

    nave->masa = masa;
    nave->velocidad = velocidad;
    nave->altura = altura;
    nave->distancia = distanciaAlCentro;
}

// aceleracion sobre la nave (positiva = hacia la Luna) a distancia r del centro terrestre
static double aceleracion(double r) {
    return -G * MASA_TIERRA / (r * r)
           + G * MASA_LUNA / ((DISTANCIA_TIERRA_LUNA - r) * (DISTANCIA_TIERRA_LUNA - r));
}

// avanza la nave 'segundos' con los motores apagados (Verlet de velocidad).
// Modifica la nave por puntero y devuelve como termino el turno.
EstadoVuelo avanzarTurno(Orion *nave, double segundos) {
    double rEq = calcularDistanciaEquilibrio();
    double restante = segundos;

    while (restante > 0.0) {
        double dt = (restante < PASO_INTEGRACION) ? restante : PASO_INTEGRACION;
        double a0 = aceleracion(nave->distancia);

        nave->distancia += nave->velocidad * dt + 0.5 * a0 * dt * dt;
        nave->velocidad += 0.5 * (a0 + aceleracion(nave->distancia)) * dt;
        restante -= dt;

        if (nave->distancia >= rEq)            return LLEGA_EQUILIBRIO;
        if (nave->distancia <= RADIO_TIERRA)   return CHOCA_TIERRA;
        if (nave->velocidad <= 0.0)            return REGRESA_A_TIERRA;
    }
    nave->altura = nave->distancia - RADIO_TIERRA;
    return EN_VUELO;
}

void mostrarResultadoSimulacion(EstadoVuelo estado, int turnos) {
    printf("\n--- RESULTADO DE LA SIMULACION (%d turnos) ---\n", turnos);
    switch (estado) {
        case LLEGA_EQUILIBRIO:
            printf("Orion llego al punto de equilibrio gravitatorio Tierra-Luna.\n");
            printf("Desde ahi la Luna domina y la nave cae hacia ella.\n");
            break;
        case REGRESA_A_TIERRA:
            printf("La velocidad llego a cero antes del punto de equilibrio.\n");
            printf("Orion se detiene y la gravedad terrestre la hace volver.\n");
            break;
        case CHOCA_TIERRA:
            printf("Orion cayo a la Tierra (distancia menor al radio terrestre).\n");
            break;
        default:
            printf("La simulacion termino con la nave todavia en vuelo.\n");
    }
}

// tabla con la velocidad y la distancia al final de cada turno (usa arreglos)
void mostrarHistorial(const double velocidades[], const double distancias[],
                      int cantidad) {
    int i;
    printf("\n--- HISTORIAL POR TURNO ---\n");
    printf(" Turno | Velocidad [km/s] | Distancia a la Tierra [km]\n");
    for (i = 0; i < cantidad; i++)
        printf(" %5d | %16.3f | %14.0f\n", i + 1, velocidades[i] / 1000.0,
               distancias[i] / 1000.0);
}
