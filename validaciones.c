
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

//Función leer línea. Lee una linea completa. Devuelve 1 si es valida, 0 si era demasiado larga.
//Si se cierra la entrada (EOF), termina el programa en forma ordenada.
static int leerLinea(char *buf, int tam) {
    if (fgets(buf, tam, stdin) == NULL) {
        printf("\nEntrada cerrada. Finalizando programa.\n");
        exit(1);
    }
    if (strchr(buf, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    buf[strcspn(buf, "\n")] = '\0';
    return 1;
}
// Permite ingresar un numero decimal
double ingresarDouble(const char *mensaje) {
    char linea[TAM_LINEA];
    char *fin;
    double valor;

     while (1) {
        printf("%s", mensaje);
        if (!leerLinea(linea, TAM_LINEA)) {
            mostrarAdvertencia("Entrada demasiado larga.");
            continue;
        }
         for (char *p = linea; *p; p++) {   // acepta coma decimal: 10,9
            if (*p == ',') *p = '.';
        }
        errno = 0;
        valor = strtod(linea, &fin);
        if (fin == linea) {
            mostrarAdvertencia("Debe ingresar un numero.");
            continue;
        }
         while (isspace((unsigned char)*fin)) fin++;
        if (*fin != '\0') {
            mostrarAdvertencia("Hay caracteres invalidos despues del numero.");
            continue;
        }
        if (errno == ERANGE || !isfinite(valor)) {
            mostrarAdvertencia("Numero fuera del rango representable.");
            continue;  
           }
        return valor;
    }
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
