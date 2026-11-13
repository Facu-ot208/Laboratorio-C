
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include "validaciones.h"

//Tamaño máximo del texto que se lee por vez
#define TAM_LINEA 100

//Para una interfaz limpia, imprime un mensaje con el formato [!] ante un error
void mostrarAdvertencia(const char *texto) {
    printf("  [!] %s\n", texto);
}

// Permite ingresar un numero decimal
double ingresarDouble(char mensaje[]) {
    double valor;

    printf("%s", mensaje);
    scanf("%lf", &valor);

    return valor;
}

// Permite ingresar solamente valores positivos
double ingresarPositivo(char mensaje[]) {
    double valor;

    do {
        valor = ingresarDouble(mensaje);

        if (valor <= 0) { // Validación para asegurar que el valor sea positivo
            printf("Error: el valor debe ser mayor que cero.\n");
        }

    } while (valor <= 0);

    return valor;
}
