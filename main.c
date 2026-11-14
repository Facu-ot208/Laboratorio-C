#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

// espera que el usuario presione Enter
static void pausar(void) {
    printf("\nPresione Enter para continuar...");
    while (getchar() != '\n');
}

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

int main(void) {
     Orion naveInicial;
    double velocidades[MAX_TURNOS];
    double distancias[MAX_TURNOS];
    int turnos = 0;
    int opcion;
    int simulado = 0;
    EstadoVuelo estado = EN_VUELO;
    double energia, trabajo;

    // por defecto se cargan los datos del enunciado
    inicializarNave(&naveInicial, MASA_ORION_ENUNCIADO, VELOCIDAD_TLI_ENUNCIADO,
                    ALTURA_LEO_ENUNCIADO);
    do {
        mostrarMenu();
        opcion = ingresarEntero("Opcion: ", 0, 7);

        switch (opcion) {
            case 1:
                configurarNave(&naveInicial);
                simulado = 0;
                break;
            case 2:
                mostrarInercia();
                break;
            case 3:
                energia = calcularEnergiaCinetica(naveInicial);
                printf("\n--- APARTADO B: ENERGIA CINETICA INICIAL ---\n");
                printf("Ki = 1/2 * m * v^2 = %.3e J\n", energia);
                break;
            case 4:
                trabajo = calcularTrabajoExterno(naveInicial);
                printf("\n--- APARTADO C: TRABAJO EXTERNO MINIMO ---\n");
                printf("Punto de equilibrio Tierra-Luna: %.0f km del centro de la Tierra\n",
                       calcularDistanciaEquilibrio() / 1000.0);
                printf("Wext = %.3e J/kg\n", trabajo);
                if (trabajo <= 0)
                    printf("Negativo: la energia inicial alcanza, no hace falta trabajo extra.\n");
                break;
            case 5:
                mostrarAnalisisCombustible();
                break;
            case 6:
                estado = ejecutarViaje(&naveInicial, velocidades, distancias, &turnos);
                mostrarResultadoSimulacion(estado, turnos);
                if (turnos > 0) mostrarHistorial(velocidades, distancias, turnos);
                simulado = 1;
                break;
            case 7:
                energia = calcularEnergiaCinetica(naveInicial);
                trabajo = calcularTrabajoExterno(naveInicial);
                mostrarReporteFinal(&naveInicial, energia, trabajo);
                if (simulado) mostrarResultadoSimulacion(estado, turnos);
                break;
            default:
                break;
        }
        if (opcion != 0) pausar();
    } while (opcion != 0);

    printf("\nFin del programa. Hasta la proxima mision!\n");
    return 0;
}
