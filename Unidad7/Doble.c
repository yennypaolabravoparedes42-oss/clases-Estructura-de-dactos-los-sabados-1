#include <stdio.h>
#include <stdlib.h>

typedef struct Pasajero {
    char genero[20];
    char apellido[50];
    struct Pasajero* anterior;
    struct Pasajero* siguiente;
} Pasajero;

Pasajero* lista = NULL;
Pasajero* abordados = NULL;
Pasajero* noAbordados = NULL;

int capacidad = 0;
int totalVendidos = 0;
int abordajeIniciado = 0;

void establecerCapacidad() {
    if (capacidad > 0) {
        printf("La capacidad ya fue establecida.\n");
        return;
    }
    printf("Ingrese la capacidad máxima del avión: ");
    scanf("%d", &capacidad);
    printf("Capacidad establecida en %d pasajeros.\n", capacidad);
}

void venderTiquete() {
    if (capacidad == 0) {
        printf("Primero debe establecer la capacidad del avión.\n");
        return;
    }
    if (abordajeIniciado) {
        printf("No se pueden vender más tiquetes, el abordaje ya inició.\n");
        return;
    }

    int limiteSobreventa = capacidad + (capacidad * 0.1);
    if (totalVendidos >= limiteSobreventa) {
        printf("Se alcanzó el límite de sobreventa (%d tiquetes).\n", limiteSobreventa);
        return;
    }

    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    printf("Ingrese el género (Femenino/Masculino/No Binario): ");
    scanf("%19s", nuevo->genero);
    printf("Ingrese el primer apellido: ");
    scanf("%49s", nuevo->apellido);

    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        Pasajero* temp = lista;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }

    totalVendidos++;
    printf("Tiquete vendido a %s (%s)\n", nuevo->apellido, nuevo->genero);
}

void iniciarAbordaje() {
    if (abordajeIniciado) {
        printf(" El abordaje ya fue iniciado.\n");
        return;
    }
    if (lista == NULL) {
        printf(" No hay pasajeros registrados.\n");
        return;
    }

    abordajeIniciado = 1;
    int contador = 0;
    Pasajero* actual = lista;

    while (actual != NULL) {
        Pasajero* siguiente = actual->siguiente;
        if (contador < capacidad) {
            actual->siguiente = abordados;
            if (abordados != NULL) {
                abordados->anterior = actual;
            }
            abordados = actual;
            actual->anterior = NULL;
            contador++;
        } else {
            actual->siguiente = noAbordados;
            if (noAbordados != NULL) {
                noAbordados->anterior = actual;
            }
            noAbordados = actual;
            actual->anterior = NULL;
        }
        actual = siguiente;
    }

    lista = NULL;
    printf(" Abordaje completado. %d pasajeros abordaron.\n", contador);
}

void verLista(Pasajero* lista) {
    if (lista == NULL) {
        printf("(Sin registros)\n");
        return;
    }
    Pasajero* temp = lista;
    while (temp != NULL) {
        printf("- %s (%s)\n", temp->apellido, temp->genero);
        temp = temp->siguiente;
    }
}

void verAbordados() {
    printf("\nPasajeros abordados:\n");
    verLista(abordados);
}

void verNoAbordados() {
    printf("\nPasajeros que no abordaron:\n");
    verLista(noAbordados);
}

int main() {
    int opcion;
    do {
        printf("\n===== MENÚ PRINCIPAL =====\n");
        printf("1. Establecer Capacidad\n");
        printf("2. Vender Tiquete\n");
        printf("3. Iniciar Abordaje\n");
        printf("4. Ver Abordados\n");
        printf("5. Ver No Abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: establecerCapacidad(); break;
            case 2: venderTiquete(); break;
            case 3: iniciarAbordaje(); break;
            case 4: verAbordados(); break;
            case 5: verNoAbordados(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opción no válida.\n");
        }
    } while (opcion != 6);

    return 0;
}