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

// Prototipos de las funciones
void mostrarInercia();
double calcularEnergiaCinetica(Orion nave);
double calcularTrabajoExterno(Orion nave);
void mostrarAnalisisCombustible(void);

#endif
