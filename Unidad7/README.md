# ✈️ Sistema de Gestión de Tiquetes de Avión

## Curso: 
- Estructura de Datos

## Integrantes:
- Yenny Paola Bravo Paredes

Este proyecto implementa un **simulador de venta de tiquetes y abordaje de un avión** en lenguaje C, aplicando **gestión de memoria dinámica** y **listas enlazadas** (simple y doble).

---

## 🧩 Archivos

| Archivo     | Descripción |
|--------------|--------------|
| `Simple.c`   | Implementa el sistema usando una **lista enlazada simple**. |
| `Doble.c`    | Implementa el sistema usando una **lista doblemente enlazada**. |

---

## ⚙️ Funcionalidades

1. **Establecer capacidad** del avión.  
2. **Vender tiquetes** con hasta un **10% de sobreventa**.  
3. **Iniciar abordaje** (los primeros N pasajeros abordan según capacidad).  
4. Mostrar **pasajeros abordados**.  
5. Mostrar **pasajeros no abordados**.  
6. **Salir** del programa.

---

## 🚀 Ejecución

Compilar y ejecutar:

```bash
# Para la versión simple
gcc Simple.c -o simple
./simple

# Para la versión doble
gcc Doble.c -o doble
./doble

📦 Datos que se almacenan

Cada pasajero contiene:

Género (Femenino, Masculino, No Binario)

Primer apellido

🧠 Conceptos Aplicados

Memoria dinámica: Uso de malloc() y free() (para crear nodos de pasajeros).

Listas enlazadas: Inserción y recorrido secuencial (simple y doble).

Control lógico: Restricción de venta al iniciar abordaje.

Estructuras de datos: Manejo ordenado de información según el flujo del programa.