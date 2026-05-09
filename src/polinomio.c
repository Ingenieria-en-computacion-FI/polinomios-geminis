#include "polinomio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Nodo* crearNodo(float coef, int exp){
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));

    nuevo -> termino.coeficiente = coef;
    nuevo -> termino.exponente = exp;

    nuevo -> siguiente = NULL;
    nuevo -> anterior = NULL;

    return nuevo;
}

void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo) {
    if (p -> cabeza == NULL){
        p -> cabeza = nuevo;
        p -> cola = nuevo;

        return;
    }
    Nodo* actual = p -> cabeza;
    while (actual !=NULL && actual -> termino.exponente > nuevo -> termino.exponente){
        actual = actual -> siguiente;
    }
    if (actual == p -> cabeza){
        nuevo -> siguiente = p -> cabeza;
        p -> cabeza -> anterior = nuevo;
        p -> cabeza -> anterior = nuevo;

        return;
    }
    nuevo -> siguiente = actual;
    nuevo -> anterior = actual -> anterior;
    
    actual -> anterior -> siguiente = nuevo;
    actual -> anterior = nuevo;
}
void eliminarNodo(Polinomio* p, int exp){
    Nodo* actual = p -> cabeza;

    while(actual != NULL && actual -> termino.exponente != exp){
        actual = actual -> siguiente;
    }
    if (actual == NULL){
        
        return;
    }
    if(p -> cabeza == actual && p -> cola == actual){
        p -> cabeza = NULL;
        p -> cola = NULL;

        free(actual);

        return;
    }
    if(actual == p->cola){
        p -> cola = actual -> anterior;
        p -> cola -> siguiente = NULL;

        free(actual);

        return;
    }
    actual -> anterior -> siguiente = actual -> siguiente;
    actual -> siguiente -> anterior = actual -> anterior;

    free(actual);
}
Polinomio* crearPolinomio(){
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));

    p -> cabeza = NULL;
    p -> cola = NULL;

    return p;
}
void insertarTermino(Polinomio* p, float coef, int exp){
    if(coef == 0){
        return;
    }
    Nodo* actual = p -> cabeza;
    while(actual != NULL){
        if(actual -> termino.exponente == exp){
            actual -> termino.coeficiente += coef;
            if(actual -> termino.coeficiente == 0){
                eliminarNodo(p, exp);
            }
            return;
        }
        actual = actual -> siguiente;
    }
    Nodo* nuevo = crearNodo(coef, exp);
    insertarNodoOrdenado(p, nuevo);
}
float evaluarPolinomio(Polinomio* p, float x){
    float resultado = 0;
    Nodo* actual = p -> cabeza;
    while(actual != NULL){
        resultado += actual -> termino.coeficiente * pow(x, actual -> termino.exponente);
        actual = actual -> siguiente;
    }

    return resultado;
}
Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* resultado = crearPolinomio();
    Nodo* actual = p1 -> cabeza;
    while(actual != NULL){
        insertarTermino(resultado, actual -> termino.coeficiente, actual -> termino.exponente);
        actual = actual -> siguiente;
    }
    actual = p2 -> cabeza;
    while(actual != NULL){
        insertarTermino(resultado, actual -> termino.coeficiente, actual -> termino.exponente);
        actual = actual -> siguiente;
    }
    return resultado;
}
Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* resultado = crearPolinomio();
    Nodo* actual1 = p1 -> cabeza;
    while(actual1 != NULL){
        Nodo* actual2 = p2 -> cabeza;
        while(actual2 != NULL){
            float coeficiente = actual1 -> termino.coeficiente * actual2 -> termino.coeficiente;
            int exponente = actual1 -> termino.exponente + actual2 -> termino.exponente;
            insertarTermino(resultado, coeficiente, exponente);
            actual2 = actual2 -> siguiente;
        }
        actual1 = actual1 -> siguiente;
    }

    return resultado;
}
char* polinomioToString(Polinomio* p){
    char* cadena = (char*)malloc(1024);
    cadena[0] = '\0';
    if(p -> cabeza == NULL){
        strcpy(cadena, "0");

        return cadena;
    }
    Nodo* actual = p -> cabeza;
    while(actual != NULL){
        char termino[100];
        float coef = actual -> termino.coeficiente;
        int exp = actual -> termino.exponente;
        if(strlen(cadena) > 0 && coef > 0){
            strcat(cadena, "+");
        }
        if(exp == 0){
            sprintf(termino, "%.0f", coef);
        }
        else if(exp == 1){
            if(coef == 1){
                sprintf(termino, "x");
            }
            else if(coef == -1){
                sprintf(termino, "-x");
            }
            else{
                sprintf(termino, "%.0fx", coef);
            }
        }
        else{
            if(coef == 1){
                sprintf(termino, "x^%d", exp);
            }
            else if(coef == -1){
                sprintf(termino, "-x^%d", exp);
            }
            else{
                sprintf(termino, "%.0fx^%d", coef, exp);
            }
        }
        strcat(cadena, termino);
        actual = actual -> siguiente;
    }

    return cadena;
}
void destruirPolinomio(Polinomio* p){
    Nodo* actual = p -> cabeza;
    while(actual != NULL){
        Nodo* temp = actual;
        actual = actual -> siguiente;
        free(temp);
    }
    free(p);
}
