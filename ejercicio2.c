#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Definición de tipos básicos
typedef char DATA;

typedef struct elemento {
    DATA d;
    struct elemento *siguiente;
} ELEMENTO;

typedef struct {
    int cnt;
    ELEMENTO *tope;
} PILA;

// --- Funciones de Pila ---
void inicializar(PILA *s) {
    s->cnt = 0;
    s->tope = NULL;
}

int estavacia(PILA *s) {
    return s->tope == NULL;
}

void push(PILA *s, DATA x) {
    ELEMENTO *nuevo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    nuevo->d = x;
    nuevo->siguiente = s->tope;
    s->tope = nuevo;
    s->cnt++;
}

DATA pop(PILA *s) {
    if (estavacia(s)) {
        return '\0';
    }

    ELEMENTO *temp = s->tope;
    DATA valor = temp->d;

    s->tope = temp->siguiente;
    free(temp);
    s->cnt--;

    return valor;
}

/**
 * Determinar si la cadena es palíndromo.
 */
int esPalindromo(char cadena[]) {

    PILA original, invertida;
    inicializar(&original);
    inicializar(&invertida);

    int i, longitud = strlen(cadena);
    int letras = 0;

    // 1. Filtrar y llenar pila original
    for (i = 0; i < longitud; i++) {
        if (isalpha(cadena[i])) {
            char letra = tolower(cadena[i]);
            push(&original, letra);
            letras++;
        }
    }

    // 2. Pasar a pila invertida (invierte orden)
    while (!estavacia(&original)) {
        push(&invertida, pop(&original));
    }

    // 3. Comparar reconstruyendo original
    while (!estavacia(&invertida)) {
        char a = pop(&invertida);
        push(&original, a);   // reconstruimos original
    }

    // ahora original tiene orden normal e invertida quedará al revés
    while (!estavacia(&original)) {
        char a = pop(&original);
        push(&invertida, a);
    }

    // comparar
    while (!estavacia(&original) && !estavacia(&invertida)) {
        if (pop(&original) != pop(&invertida)) {
            return 0;
        }
    }

    return 1;
}

int main() {

    char prueba1[] = "Anita lava la tina";
    char prueba2[] = "Estructuras de Datos";

    printf("--- TEST DE PALINDROMOS ---\n");

    printf("Prueba 1: '%s' -> %s\n", prueba1,
           esPalindromo(prueba1) ? "ES PALINDROMO" : "NO ES PALINDROMO");

    printf("Prueba 2: '%s' -> %s\n", prueba2,
           esPalindromo(prueba2) ? "ES PALINDROMO" : "NO ES PALINDROMO");

    return 0;
}
