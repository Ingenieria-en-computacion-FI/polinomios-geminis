#include <stdio.h>
#include "polinomio.h"
#include <stdlib.h>

int main() {
    Polinomio* p1 = crearPolinomio();
    Polinomio* p2 = crearPolinomio();

    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    insertarTermino(p2, 1, 2);
    insertarTermino(p2, -2, 1);
    insertarTermino(p2, 4, 0);

    char* texto1 = polinomioToString(p1);
    char* texto2 = polinomioToString(p2);

    printf("Polinomio 1: %s\n", texto1);
    printf("Polinomio 2: %s\n", texto2);

    Polinomio* suma = sumarPolinomios(p1, p2);
    char* textoSuma = polinomioToString(suma);

    printf("Suma: %s\n", textoSuma);

    Polinomio* multiplicacion = multiplicarPolinomios(p1, p2);

    char* textoMult = polinomioToString(multiplicacion);

    printf("Multiplicacion: %s\n", textoMult);

    float valor = evaluarPolinomio(p1, 2);

    printf("Evaluacion de P1 en x = 2: %.2f\n", valor);

    free(texto1);
    free(texto2);
    free(textoSuma);
    free(textoMult);

    destruirPolinomio(p1);
    destruirPolinomio(p2);
    destruirPolinomio(suma);
    destruirPolinomio(multiplicacion);

    return 0;
}
