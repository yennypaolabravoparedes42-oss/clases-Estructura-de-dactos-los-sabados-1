#include <stdio.h>
#define MAX 5

typedef struct {
    int codigo;
    float nota;
} Estudiante;


Estudiante estudiantes[] = {
    {2024101, 4.5},
    {2024102, 3.2},
    {2024103, 2.8},
    {2024104, 5.0},
    {2024105, 4.0},
}

int n = sizeof(estudiantes) / sizeof(estudiantes[0]);


float notaMaxima(Estudiante arr[], int i, int n) {
    if (i == n - 1) return arr[i].nota;
    float maxResto = notaMaxima(arr, i + 1, n);
    return (arr[i].nota > maxResto) ? arr[i].nota : maxResto;
}

float sumaNotas(Estudiante arr[], int i, int n) {
    if (i == n) return 0;
    return arr[i].nota + sumaNotas(arr, i + 1, n);
}

float promedioCurso(Estudiante arr[], int n) {
    return sumaNotas(arr, 0, n) / n;
}

void selectionSort(Estudiante arr[], int inicio, int n) {
    if (inicio >= n - 1) return;

    int minIndex = inicio;
    for (int j = inicio + 1; j < n; j++) {
        if (arr[j].codigo < arr[minIndex].codigo) {
            minIndex = j;
        }
    }

    if (minIndex != inicio) {
        Estudiante temp = arr[inicio];
        arr[inicio] = arr[minIndex];
        arr[minIndex] = temp;
    }

    selectionSort(arr, inicio + 1, n);
}

void mostrarEstudiantes(Estudiante arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Código: %d | Nota: %.2f\n", arr[i].codigo, arr[i].nota);
    }
}

int main() {
    int opcion;
    do {
        printf("\n==== MENU ====\n");
        printf("1. Buscar la Nota Máxima del Curso\n");
        printf("2. Calcular el Promedio del Curso\n");
        printf("3. Ordenar Códigos de Estudiantes (Selection Sort Recursivo)\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Nota máxima del curso: %.2f\n", notaMaxima(estudiantes, 0, n));
                break;
            case 2:
                printf("Promedio del curso: %.2f\n", promedioCurso(estudiantes, n));
                break;
            case 3:
                selectionSort(estudiantes, 0, n);
                printf("Lista de estudiantes ordenada:\n");
                mostrarEstudiantes(estudiantes, n);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}