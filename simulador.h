#ifndef SIMULADOR_H
#define SIMULADOR_H

// constantes fisicas que no cambian
#define G 6.67430e-11
#define MASA_TIERRA 5.972e24
#define MASA_LUNA 7.342e22
#define RADIO_TIERRA 6371000.0
#define DISTANCIA_TIERRA_LUNA 384000000.0

// estructura de datos de la nave orion
typedef struct {
    double masa;
    double velocidad;
    double distancia;
    double altura;
} Orion;

// valores del enunciado del Problema 3 (TLI)
#define MASA_ORION_ENUNCIADO 26000.0
#define VELOCIDAD_TLI_ENUNCIADO 10900.0
#define ALTURA_LEO_ENUNCIADO 192000.0

// limites de la simulacion por turnos
#define MAX_TURNOS 200
#define PASO_INTEGRACION 10.0   // segundos por subpaso numerico

// estado en el que queda la nave luego de cada turno
typedef enum {
    EN_VUELO,
    LLEGA_EQUILIBRIO,
    REGRESA_A_TIERRA,
    CHOCA_TIERRA
} EstadoVuelo;

// declaración de las funciones
void mostrarInercia();
double calcularEnergiaCinetica(Orion nave);
double calcularTrabajoExterno(Orion nave);
double calcularDistanciaEquilibrio(void);
void inicializarNave(Orion *nave, double masa, double velocidad, double altura);
EstadoVuelo avanzarTurno(Orion *nave, double segundos);
void mostrarResultadoSimulacion(EstadoVuelo estado, int turnos);
void mostrarHistorial(const double velocidades[], const double distancias[],
                      int cantidad);
void mostrarAnalisisCombustible(void);
void mostrarReporteFinal(const Orion *nave, double energiaCinetica,
                         double trabajoExterno);

#endif
