#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main() {

    
// Carga los datos de la nave: ingresados por el usuario o los del enunciado
static void configurarNave(Orion *nave) {
    double masa, velocidad, altura;
    char opcion;

    printf("\n--- CONFIGURACION DE ORION ---\n");
    printf("Valores del enunciado: m = %.1f kg, v_TLI = %.1f m/s, h = %.1f m\n",
           MASA_ORION_ENUNCIADO, VELOCIDAD_TLI_ENUNCIADO, ALTURA_LEO_ENUNCIADO);
    opcion = ingresarOpcion("Usar los valores del enunciado? (S/N): ", "SN");

    if (opcion == 'S') {
        masa = MASA_ORION_ENUNCIADO;
        velocidad = VELOCIDAD_TLI_ENUNCIADO;
        altura = ALTURA_LEO_ENUNCIADO;
    } else {
        masa = ingresarPositivo("Masa de Orion [kg]: ");
        velocidad = ingresarDoubleRango("Velocidad de inyeccion [m/s] (1000 a 15000): ",
                                        1000.0, 15000.0);
        altura = ingresarDoubleRango("Altura de la orbita baja [m] (100000 a 2000000): ",
                                     100000.0, 2000000.0);
    }
    inicializarNave(nave, masa, velocidad, altura);
    printf("\nNave configurada correctamente.\n");
}

// Ciclo por turnos del viaje translunar. Cada turno el usuario elige cuantas horas
// avanzar y se actualiza la nave por puntero. Guarda el historial en los arreglos.
static EstadoVuelo ejecutarViaje(const Orion *inicial, double velocidades[],
                                 double distancias[], int *turnos) {
    Orion nave = *inicial;
    EstadoVuelo estado = EN_VUELO;
    double horas;
    char opcion;

    *turnos = 0;
    while (estado == EN_VUELO && *turnos < MAX_TURNOS) {
        limpiarPantalla();
        mostrarPanelTurno(*turnos + 1, nave.velocidad, nave.distancia,
                          DISTANCIA_TIERRA_LUNA, (int)(nave.distancia / DISTANCIA_TIERRA_LUNA * 20));

        opcion = ingresarOpcion("[A] Avanzar turno  [S] Abandonar simulacion: ", "AS");
        if (opcion == 'S') break;
        horas = ingresarDoubleRango("Horas a avanzar en este turno (0.5 a 48): ", 0.5, 48.0);

        estado = avanzarTurno(&nave, horas * 3600.0);
        velocidades[*turnos] = nave.velocidad;
        distancias[*turnos] = nave.distancia;
        (*turnos)++;
    }

    limpiarPantalla();
    mostrarPanelTurno(*turnos, nave.velocidad, nave.distancia,
                      DISTANCIA_TIERRA_LUNA, (int)(nave.distancia / DISTANCIA_TIERRA_LUNA * 20));
    return estado;
}

static void mostrarMenu(void) {
    printf("\n==============================================\n");
    printf("   ARTEMIS: INYECCION TRANSLUNAR\n");
    printf("==============================================\n");
    printf(" 1. Configurar nave Orion\n");
    printf(" 2. Apartado A: ley de inercia\n");
    printf(" 3. Apartado B: energia cinetica inicial\n");
    printf(" 4. Apartado C: trabajo externo minimo\n");
    printf(" 5. Apartado D: combustible ida vs regreso\n");
    printf(" 6. Simular viaje translunar (por turnos)\n");
    printf(" 7. Reporte final\n");
    printf(" 0. Salir\n");
}
    return 0;
}
