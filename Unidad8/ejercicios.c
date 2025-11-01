#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpiarEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char *leerTexto(const char *mensaje) {
    char buffer[512];
    printf("%s", mensaje);
    if (!fgets(buffer, sizeof(buffer), stdin)) return NULL;
    buffer[strcspn(buffer, "\n")] = 0;
    char *res = malloc(strlen(buffer) + 1);
    strcpy(res, buffer);
    return res;
}


typedef struct PilaTexto {
    char *texto;
    struct PilaTexto *siguiente;
} PilaTexto;

PilaTexto *pushTexto(PilaTexto *pila, const char *texto) {
    PilaTexto *nuevo = malloc(sizeof(PilaTexto));
    nuevo->texto = strdup(texto);
    nuevo->siguiente = pila;
    return nuevo;
}

PilaTexto *popTexto(PilaTexto *pila, char **valor) {
    if (!pila) { *valor = NULL; return NULL; }
    PilaTexto *tmp = pila;
    *valor = pila->texto;
    pila = pila->siguiente;
    free(tmp);
    return pila;
}

void mostrarPila(PilaTexto *p) {
    int i = 1;
    if (!p) { printf("  (vacia)\n"); return; }
    while (p) {
        printf("  %d) %s\n", i++, p->texto);
        p = p->siguiente;
    }
}

void liberarPila(PilaTexto *p) {
    while (p) {
        PilaTexto *tmp = p;
        p = p->siguiente;
        free(tmp->texto);
        free(tmp);
    }
}

void simuladorUndoRedo() {
    PilaTexto *undo = NULL, *redo = NULL;
    printf("\n--- MODULO UNDO/REDO ---\n");
    printf("Comandos: texto | undo | redo | verundo | verredo | salir\n");
    while (1) {
        char *linea = leerTexto("cmd> ");
        if (!linea) break;
        if (strcmp(linea, "salir") == 0) { free(linea); break; }

        if (strcmp(linea, "undo") == 0) {
            char *acc = NULL;
            undo = popTexto(undo, &acc);
            if (!acc) printf("Nada que deshacer.\n");
            else {
                redo = pushTexto(redo, acc);
                printf("Deshecho: %s\n", acc);
                free(acc);
            }
        } else if (strcmp(linea, "redo") == 0) {
            char *acc = NULL;
            redo = popTexto(redo, &acc);
            if (!acc) printf("Nada que rehacer.\n");
            else {
                undo = pushTexto(undo, acc);
                printf("Rehecho: %s\n", acc);
                free(acc);
            }
        } else if (strcmp(linea, "verundo") == 0) {
            printf("Pila UNDO:\n");
            mostrarPila(undo);
        } else if (strcmp(linea, "verredo") == 0) {
            printf("Pila REDO:\n");
            mostrarPila(redo);
        } else {
            undo = pushTexto(undo, linea);
            liberarPila(redo);
            redo = NULL;
            printf("Acción registrada: %s\n", linea);
        }
        free(linea);
    }
    liberarPila(undo);
    liberarPila(redo);
}


typedef struct PilaChar {
    char c;
    struct PilaChar *sig;
} PilaChar;

int prioridad(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int esOperador(char c) {
    return strchr("+-*/^", c) != NULL;
}

PilaChar *pushChar(PilaChar *p, char c) {
    PilaChar *nuevo = malloc(sizeof(PilaChar));
    nuevo->c = c;
    nuevo->sig = p;
    return nuevo;
}

PilaChar *popChar(PilaChar *p, char *out) {
    if (!p) { *out = 0; return NULL; }
    PilaChar *tmp = p;
    *out = p->c;
    p = p->sig;
    free(tmp);
    return p;
}

void convertirInfijaPostfija() {
    char *expr = leerTexto("Expresión infija (ej: A+B*(C-D)) : ");
    if (!expr) return;
    char salida[1024] = {0};
    int pos = 0;
    PilaChar *pila = NULL;

    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (isspace(c)) continue;
        if (isalnum(c)) {
            salida[pos++] = c; salida[pos++] = ' ';
        } else if (c == '(') pila = pushChar(pila, c);
        else if (c == ')') {
            char t;
            while (pila) {
                pila = popChar(pila, &t);
                if (t == '(') break;
                salida[pos++] = t; salida[pos++] = ' ';
            }
        } else if (esOperador(c)) {
            char t;
            while (pila && esOperador(pila->c) &&
                   ((prioridad(pila->c) > prioridad(c)) ||
                    (prioridad(pila->c) == prioridad(c) && c != '^'))) {
                pila = popChar(pila, &t);
                salida[pos++] = t; salida[pos++] = ' ';
            }
            pila = pushChar(pila, c);
        }
    }

    char t;
    while (pila) {
        pila = popChar(pila, &t);
        if (t != '(') { salida[pos++] = t; salida[pos++] = ' '; }
    }

    printf("Postfija: %s\n", salida);
    free(expr);
}


typedef struct NodoNum {
    long val;
    struct NodoNum *sig;
} NodoNum;

NodoNum *pushNum(NodoNum *p, long v) {
    NodoNum *n = malloc(sizeof(NodoNum));
    n->val = v;
    n->sig = p;
    return n;
}

NodoNum *popNum(NodoNum *p, long *out) {
    if (!p) { *out = 0; return NULL; }
    NodoNum *tmp = p;
    *out = p->val;
    p = p->sig;
    free(tmp);
    return p;
}

void evaluarPostfija() {
    char *expr = leerTexto("Expresión postfija (ej: 2 3 4 * +):\n> ");
    if (!expr) return;
    NodoNum *pila = NULL;
    char *tok = strtok(expr, " ");
    while (tok) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pila = pushNum(pila, atol(tok));
        } else if (strlen(tok) == 1 && esOperador(tok[0])) {
            long b, a, r = 0;
            pila = popNum(pila, &b);
            pila = popNum(pila, &a);
            switch (tok[0]) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': r = (b ? a / b : 0); break;
                case '^': r = 1; for (int i = 0; i < b; i++) r *= a; break;
            }
            pila = pushNum(pila, r);
        }
        tok = strtok(NULL, " ");
    }
    long res = 0;
    pila = popNum(pila, &res);
    printf("Resultado: %ld\n", res);
    free(expr);
    while (pila) { long tmp; pila = popNum(pila, &tmp); }
}


typedef struct Trabajo {
    int id, paginas;
    struct Trabajo *sig;
} Trabajo;

Trabajo *inicioImp = NULL, *finImp = NULL;
int idImp = 1;

void agregarTrabajo(int pags) {
    Trabajo *t = malloc(sizeof(Trabajo));
    t->id = idImp++;
    t->paginas = pags;
    t->sig = NULL;
    if (!inicioImp) inicioImp = finImp = t;
    else { finImp->sig = t; finImp = t; }
    printf("Trabajo agregado: ID=%d, páginas=%d\n", t->id, t->paginas);
}

void procesarTrabajo() {
    if (!inicioImp) { printf("Cola vacía.\n"); return; }
    Trabajo *t = inicioImp;
    inicioImp = inicioImp->sig;
    if (!inicioImp) finImp = NULL;
    printf("Procesando ID=%d (%d páginas)...\n", t->id, t->paginas);
    free(t);
}

void verColaImp() {
    if (!inicioImp) { printf("Sin trabajos.\n"); return; }
    for (Trabajo *t = inicioImp; t; t = t->sig)
        printf("ID=%d, páginas=%d\n", t->id, t->paginas);
}

void limpiarImp() { while (inicioImp) { Trabajo *t = inicioImp; inicioImp = inicioImp->sig; free(t); } finImp = NULL; idImp = 1; }

typedef struct Cliente {
    int id;
    struct Cliente *sig;
} Cliente;

Cliente *iniBanco = NULL, *finBanco = NULL;
int idBanco = 1;

void nuevoCliente() {
    Cliente *c = malloc(sizeof(Cliente));
    c->id = idBanco++;
    if (!iniBanco) { iniBanco = finBanco = c; c->sig = c; }
    else { c->sig = iniBanco; finBanco->sig = c; finBanco = c; }
    printf("Cliente ingresado: %d\n", c->id);
}

void atenderCliente() {
    if (!iniBanco) { printf("Sin clientes.\n"); return; }
    Cliente *c = iniBanco;
    printf("Atendiendo cliente %d\n", c->id);
    if (iniBanco == finBanco) { free(c); iniBanco = finBanco = NULL; }
    else { iniBanco = iniBanco->sig; finBanco->sig = iniBanco; free(c); }
}

void mostrarBanco() {
    if (!iniBanco) { printf("Cola vacía.\n"); return; }
    Cliente *c = iniBanco;
    do { printf("%d -> ", c->id); c = c->sig; } while (c != iniBanco);
    printf("(inicio)\n");
}

typedef struct NodoPrio {
    int valor, prioridad;
    struct NodoPrio *sig;
} NodoPrio;

NodoPrio *inicioPrio = NULL;

void insertarPrio(int val, int pr) {
    NodoPrio *n = malloc(sizeof(NodoPrio));
    n->valor = val; n->prioridad = pr; n->sig = NULL;
    if (!inicioPrio || pr > inicioPrio->prioridad) {
        n->sig = inicioPrio; inicioPrio = n;
    } else {
        NodoPrio *t = inicioPrio;
        while (t->sig && t->sig->prioridad >= pr) t = t->sig;
        n->sig = t->sig; t->sig = n;
    }
}

void retirarPrio() {
    if (!inicioPrio) { printf("Vacía.\n"); return; }
    NodoPrio *t = inicioPrio;
    inicioPrio = inicioPrio->sig;
    printf("Retirado: val=%d prio=%d\n", t->valor, t->prioridad);
    free(t);
}

void verPrio() {
    if (!inicioPrio) { printf("Vacía.\n"); return; }
    for (NodoPrio *t = inicioPrio; t; t = t->sig)
        printf("val=%d prio=%d\n", t->valor, t->prioridad);
}

typedef struct Proceso {
    int id, restante;
    struct Proceso *sig;
} Proceso;

Proceso *iniRR = NULL, *finRR = NULL;
int idRR = 1;

void agregarProceso(int tiempo) {
    Proceso *p = malloc(sizeof(Proceso));
    p->id = idRR++; p->restante = tiempo;
    if (!iniRR) { iniRR = finRR = p; p->sig = p; }
    else { p->sig = iniRR; finRR->sig = p; finRR = p; }
    printf("Proceso agregado: %d (burst=%d)\n", p->id, tiempo);
}

void ejecutarRR() {
    if (!iniRR) { printf("Sin procesos.\n"); return; }
    int quantum;
    printf("Quantum: ");
    if (scanf("%d", &quantum) != 1) { limpiarEntrada(); return; }
    limpiarEntrada();
    while (iniRR) {
        Proceso *p = iniRR;
        if (p->restante <= quantum) {
            printf("Proceso %d finaliza.\n", p->id);
            if (iniRR == finRR) { free(p); iniRR = finRR = NULL; }
            else { iniRR = iniRR->sig; finRR->sig = iniRR; free(p); }
        } else {
            p->restante -= quantum;
            printf("Proceso %d ejecutado (%d restantes)\n", p->id, p->restante);
            iniRR = iniRR->sig;
            finRR = finRR->sig;
        }
    }
}


int main() {
    int op;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Undo/Redo\n");
        printf("2. Infija → Postfija\n");
        printf("3. Evaluar Postfija\n");
        printf("4. Cola Impresora\n");
        printf("5. Cola Circular Banco\n");
        printf("6. Cola con Prioridad\n");
        printf("7. Round Robin\n");
        printf("0. Salir\n> ");
        if (scanf("%d", &op) != 1) { limpiarEntrada(); break; }
        limpiarEntrada();

        switch (op) {
            case 1: simuladorUndoRedo(); break;
            case 2: convertirInfijaPostfija(); break;
            case 3: evaluarPostfija(); break;
            case 4: {
                int c;
                do {
                    printf("\n--- IMPRESORA ---\n1. Agregar\n2. Procesar\n3. Ver\n4. Volver\n> ");
                    if (scanf("%d", &c) != 1) { limpiarEntrada(); break; }
                    limpiarEntrada();
                    if (c == 1) { int p; printf("Páginas: "); scanf("%d", &p); limpiarEntrada(); agregarTrabajo(p); }
                    else if (c == 2) procesarTrabajo();
                    else if (c == 3) verColaImp();
                } while (c != 4);
                break;
            }
            case 5: {
                int c;
                do {
                    printf("\n--- BANCO ---\n1. Nuevo cliente\n2. Atender\n3. Ver cola\n4. Volver\n> ");
                    if (scanf("%d", &c) != 1) { limpiarEntrada(); break; }
                    limpiarEntrada();
                    if (c == 1) nuevoCliente();
                    else if (c == 2) atenderCliente();
                    else if (c == 3) mostrarBanco();
                } while (c != 4);
                break;
            }
            case 6: {
                int c;
                do {
                    printf("\n--- PRIORIDAD ---\n1. Insertar\n2. Retirar\n3. Ver\n4. Volver\n> ");
                    if (scanf("%d", &c) != 1) { limpiarEntrada(); break; }
                    limpiarEntrada();
                    if (c == 1) { int v,p; printf("Valor: "); scanf("%d",&v); printf("Prioridad: "); scanf("%d",&p); limpiarEntrada(); insertarPrio(v,p); }
                    else if (c == 2) retirarPrio();
                    else if (c == 3) verPrio();
                } while (c != 4);
                break;
            }
            case 7: {
                int c;
                do {
                    printf("\n--- ROUND ROBIN ---\n1. Agregar proceso\n2. Ejecutar\n3. Volver\n> ");
                    if (scanf("%d", &c) != 1) { limpiarEntrada(); break; }
                    limpiarEntrada();
                    if (c == 1) { int t; printf("Tiempo burst: "); scanf("%d",&t); limpiarEntrada(); agregarProceso(t); }
                    else if (c == 2) ejecutarRR();
                } while (c != 3);
                break;
            }
        }
    } while (op != 0);

    printf("Saliendo del programa.\n");
    limpiarImp();
    return 0;
}