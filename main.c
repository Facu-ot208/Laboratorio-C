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


    return 0;
}
