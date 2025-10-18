#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Ingrese el tamaño del arreglo: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Tamaño inválido.\n");
        return 1;
    }

    int *numeros = malloc(n * sizeof(int)); 
    if (numeros == NULL) {
        printf("Error en la asignación de memoria.\n");
        return 1;
    }

    printf("\nContenido del arreglo:\n");
    for (int i = 0; i < n; i++) {
        numeros[i] = i * 10;
        printf("%d ", numeros[i]);
    }

    printf("\n");

    free(numeros);
    return 0;
}