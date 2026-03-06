# Generador y Solucionador de Laberintos en C++

## Introducción

Este proyecto implementa un generador de laberintos aleatorios completamente resolubles y un algoritmo capaz de encontrar automáticamente la salida.

El objetivo del ejercicio fue aplicar conceptos fundamentales de algoritmos y estructuras de datos, especialmente búsqueda en grafos, generación procedural y análisis de tiempo de ejecución.

El programa genera un laberinto distinto en cada ejecución, garantiza que exista al menos un camino entre la entrada y la salida, y posteriormente utiliza un algoritmo de búsqueda para encontrar la solución automáticamente.

Este proyecto fue desarrollado como parte de un desafío de programación enfocado en lógica algorítmica y diseño estructurado en C++.

---

## Objetivos del Proyecto

- Generar laberintos aleatorios completamente resolubles.
- Implementar algoritmos clásicos de búsqueda.
- Separar claramente las responsabilidades del código:
  - generación
  - visualización
  - resolución
- Permitir que el tamaño del laberinto sea configurable.
- Medir el tiempo de ejecución del algoritmo.

---

## Tecnologías Utilizadas

Lenguaje:

- C++

Librerías estándar utilizadas:

- `iostream` para entrada y salida en consola.
- `vector` para manejar matrices dinámicas.
- `stack` para el algoritmo de generación de laberinto.
- `queue` para el algoritmo de resolución.
- `algorithm` y `random` para generación aleatoria.
- `ctime` para medición del tiempo de ejecución.

No se utilizaron librerías externas.

---

## Representación del Laberinto

El laberinto se representa como una matriz bidimensional de caracteres.

Símbolos utilizados:

| Símbolo | Significado |
|-------|-------------|
| `#` | muro |
| espacio | camino libre |
| `S` | entrada |
| `E` | salida |
| `*` | camino encontrado por el algoritmo |

La entrada siempre se encuentra en la esquina superior izquierda y la salida en la esquina inferior derecha.

---

## Generación del Laberinto (DFS con Backtracking)

Para generar el laberinto se utiliza una variante del algoritmo **Depth First Search (DFS)** con **backtracking**, también conocido como *Recursive Backtracker*.

### Idea general

1. Se inicia desde la celda `(0,0)`.
2. Se visitan celdas vecinas aleatorias saltando dos posiciones para mantener muros entre caminos.
3. Cuando se avanza, se rompe el muro intermedio.
4. Si una celda no tiene vecinos disponibles, el algoritmo retrocede usando una pila.

### Características del método

- Produce laberintos **perfectos** (sin ciclos).
- Garantiza que todas las celdas accesibles estén conectadas.
- Genera una estructura aleatoria diferente en cada ejecución.

La pila (`stack`) se utiliza para recordar el camino recorrido y permitir retroceder cuando se llega a un callejón sin salida.

---

## Resolución del Laberinto (BFS)

Para resolver el laberinto se utiliza el algoritmo **Breadth First Search (BFS)**.

### Motivo de elección

BFS garantiza encontrar el **camino más corto** entre el punto inicial y el destino en grafos no ponderados.

### Funcionamiento

1. Se inicia desde la posición de entrada.
2. Se exploran las celdas vecinas válidas utilizando una cola (`queue`).
3. Cada celda guarda una referencia a su celda "padre".
4. Cuando se alcanza la salida, se reconstruye el camino retrocediendo desde la salida hasta la entrada.

El camino encontrado se marca en el laberinto con `*`.

---

## Configuración del Tamaño del Laberinto

El tamaño del laberinto puede configurarse mediante argumentos de línea de comandos.

Ejemplo:

```bash
./laberinto 21 21

## Autor: Alan Nuñez Jara
