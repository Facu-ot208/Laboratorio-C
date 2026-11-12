
#include <stdio.h>
#include "validaciones.h"

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
