#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Muestra un mensaje de advertencia con formato uniforme: "  [!] texto"
void mostrarAdvertencia(const char *texto);

// Pide un numero decimal. Acepta coma o punto. Rechaza letras, texto sobrante,
// nan, inf y numeros fuera del rango representable. Repite hasta que sea valido.
double ingresarDouble(const char *mensaje);

//Pide un numero decimal estrictamente mayor que cero.
double ingresarPositivo(const char *mensaje);

// Pide un numero decimal dentro del rango [min, max].
double ingresarDoubleRango(const char *mensaje, double min, double max);

// Pide un entero dentro del rango [min, max].
int ingresarEntero(const char *mensaje, int min, int max);

// Pide un unico caracter que este dentro de 'validas' (ej: "SN").
// Devuelve el caracter en mayuscula.
char ingresarOpcion(const char *mensaje, const char *validas);

#endif
