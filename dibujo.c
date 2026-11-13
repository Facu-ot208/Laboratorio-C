#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"

#define ANCHO_BARRA 30
    // Limpia la consola segun el sistema operativo
    void limpiarPantalla(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    // Dibujo ASCII de la nave. Se imprime linea por linea
    void dibujarNave(int desplazamiento) {
    int i;

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("        _\n");

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("      /   \\\n");

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("======|  o  |========================.\n");

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("<     |     |                         \\____\n");

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("======|  o  |========================/\n");

    for (i = 0; i < desplazamiento; i++) printf(" ");
    printf("      \\ _ /\n");
}

    // Barra de progreso: relleno proporcional a lo recorrido
    void dibujarBarraViaje(double recorrido, double total) {
        double fraccion = recorrido / total;
        int llenos, i;

        if (fraccion < 0.0) fraccion = 0.0;   // se limita a [0, 1]
        if (fraccion > 1.0) fraccion = 1.0;

        llenos = (int)(fraccion * ANCHO_BARRA);

        printf(" TIERRA [");
        for (i = 0; i < ANCHO_BARRA; i++) {
            if (i < llenos)       printf("=");
            else if (i == llenos) printf(">");
            else                  printf("-");
        }
        printf("] LUNA\n");
        printf("         %.0f%%\n", fraccion * 100.0);
    }

    // Pantalla completa de un turno
    void mostrarPanelTurno(int turno, double velocidad, double distancia, double total, int desplazamiento) {
        printf("==============================================\n");
        printf("        MISION ARTEMIS - TURNO %d\n", turno);
        printf("==============================================\n");
        dibujarNave(desplazamiento);
        printf("\n  Velocidad : %.2f km/s\n", velocidad / 1000.0);
        printf("  Distancia : %.0f km\n\n", distancia / 1000.0);
        dibujarBarraViaje(distancia, total);
        printf("==============================================\n");
    }
