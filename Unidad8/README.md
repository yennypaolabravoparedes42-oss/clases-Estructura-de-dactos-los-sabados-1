🧮 Unidad 8 – Estructuras Dinámicas en C

Este proyecto reúne una serie de simulaciones y ejercicios prácticos que implementan pilas, colas y listas circulares dinámicas en lenguaje C.
Cada módulo demuestra una aplicación distinta de estas estructuras mediante menús interactivos en consola.

📘 Contenido del Proyecto
1️⃣ Simulador de Undo/Redo

Simula el funcionamiento clásico de deshacer y rehacer usando dos pilas dinámicas (UNDO y REDO).

Características:

Permite registrar acciones de texto.

Deshacer (undo) y rehacer (redo) las acciones.

Muestra en cualquier momento el contenido actual de ambas pilas.

Comandos disponibles:

cmd> accion       → registra una nueva acción
cmd> undo         → deshace la última acción
cmd> redo         → rehace la última acción
cmd> verundo      → muestra la pila UNDO
cmd> verredo      → muestra la pila REDO
cmd> salir        → finaliza la simulación

2️⃣ Conversión Infija → Postfija (Notación Polaca Inversa)

Implementa el algoritmo Shunting-Yard de Dijkstra para convertir expresiones infijas a postfijas.

Soporta: operadores + - * / ^ y paréntesis ()
Ejemplo:

Entrada:  A+B*(C-D)
Salida:   A B C D - * +

3️⃣ Evaluación de Expresiones Postfijas

Evalúa expresiones postfijas numéricas usando una pila dinámica de operandos.

Ejemplo:

Entrada:  2 3 4 * +
Proceso:  2 + (3 * 4)
Salida:   14

4️⃣ Simulación de Cola de Impresora

Modelo de una cola FIFO para gestionar trabajos de impresión.

Funciones principales:

Encolar un nuevo trabajo con ID automático y número de páginas.

Procesar (desencolar) el siguiente trabajo.

Visualizar la cola actual de impresión.

5️⃣ Gestión de Turnos en Banco (Cola Circular)

Simula un sistema de atención al cliente en un banco mediante una cola circular dinámica.

Opciones del menú:

Ingresar cliente (nuevo turno).

Atender cliente (desencolar).

Ver estado actual de la cola.

6️⃣ Cola de Prioridad Simple

Implementa una cola con prioridades descendentes, donde el elemento con mayor prioridad es atendido primero.

Ejemplo:

Enqueue (valor=10, prioridad=5)
Enqueue (valor=3, prioridad=8)
Dequeue → (valor=3, prioridad=8)

7️⃣ Planificación Round Robin

Simula un planificador de procesos tipo Round Robin, usando una cola circular de procesos.

Cada proceso incluye:

ID único

Tiempo restante de ejecución (burst)

Ejemplo:

Proceso 1: burst = 8
Proceso 2: burst = 4
Quantum = 3


Salida esperada:

Proceso 1 ejecutado por 3, rest=5
Proceso 2 ejecutado por 3, rest=1
Proceso 1 ejecutado por 3, rest=2
...

⚙️ Estructuras dinámicas utilizadas
Módulo	Estructura usada
Simulador Undo/Redo	Pilas (LIFO)
Infija → Postfija	Pila de caracteres
Evaluación Postfija	Pila numérica
Cola de impresora	Cola (FIFO)
Turnos banco	Cola circular
Cola de prioridad	Cola ordenada
Round Robin	Cola circular de procesos
🧩 Compilación y Ejecución

Compilar:

gcc unidad8_ejercicios.c -o unidad8_ejercicios


Ejecutar:

./unidad8_ejercicios

🖥️ Menú Principal

Al ejecutar el programa, se muestra:

==== MENU PRINCIPAL - EJERCICIOS UNIDAD 8 ====
1. Simulador Undo/Redo
2. Infija -> Postfija (RPN)
3. Evaluación Postfija (números)
4. Cola de impresora
5. Gestión de turnos en banco
6. Cola de prioridad simple
7. Planificación Round Robin
0. Salir

🧼 Liberación de Memoria

Cada módulo libera su memoria dinámica antes de finalizar:

Pilas → free()

Colas → free()

Listas circulares → free()

Reinicio de contadores (IDs, trabajos, procesos)