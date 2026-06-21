# Tarea 2 – Comparación de Algoritmos
---
Nombre: Gabriel Toro Varela - 21486437-1 - 202204557-4 - P200

---
Se aconseja abrir este README en github para una mejor visibilidad.

Esta tarea implementa cuatro enfoques distintos para resolver un tipo de problema, siendo:

- Problema modelable como  multiple-choice knapsack

Los algoritmos implementados son:

- Fuerza Bruta (BF)

- Programcion Dinamica (DP)

- Greedy 1 (G1)

- Greedy 2 (G2)

El proyecto incluye:

- Implementación de los 4 algoritmos en C++

- El programa principal (general.cpp) que ejecuta sus algoritmos con distintos casos de prueba

- Scripts para generar estos casos de prueba automaticamente

- Scripts para medir los tiempos

- Generación automática de gráficos comparativos

La finalidad es analizar rendimiento y escalabilidad en calidad de respuesta y tiempo de ejecucion.

### Estructura del Proyecto
```
/code/
  ├── implementation/
  │        ├── algorithms/
  │        │      ├── brute-force.cpp
  │        │      ├── dynamic-programming.cpp
  │        │      ├── greedy1.cpp
  │        │      └── greedy2.cpp
  │        │
  │        ├── bin/ (creado post-run)
  │        │      └── ...
  │        │
  │        ├── data/
  │        │      ├── inputs/
  │        │      ├── measurements/
  │        │      ├── ouputs/
  │        │      └── plots/
  │        │
  │        ├── include/
  │        │      ├── brute-force.h
  │        │      ├── dynamic-programming.h
  │        │      ├── estructuras.h
  │        │      ├── greedy1.h
  │        │      └── greedy2.h
  │        │
  │        ├── scripts/
  │        │      └── plot_generator.py
  │        │      └── testcases_generator.py
  │        │
  │        ├── general.cpp
  │        └── makefile
  │
  │
  └── README (El que estas leyendo ahora)


```

## Implementacion

### 🔢 Fuerza Bruta

`BruteForce` de toda la vida, utilizando como `Backtracking` las 2 restricciones del ejercicio.

### 🔢 Programacion Dinamica

Se utilizan Tablas DP de tiempo y energía, reutilizando soluciones parciales.

### 🧩 Greedy 1

`Greedy` elige la mejor opcion en una seleccion iterativa por mejor score = calidad/precio.

Para cada anime, G1 revisa las opciones que tiene, ver 0, 1, 2,...,n capitulos (consecutivos), descarta las que rompen restricciones (M,E), y luego para cada opcion calcula:

`Score` = $\frac{\text{v}}{\frac{t}{M} + \frac{c}{E}}$

luego elige la opcion con mejor `Score`, añade v a la solucion y pasa al siguiente anime en la lista.

### 🧩 Greedy 2

`Greedy` basado en ganancia marginal por expansión incremental de la solución.

Elige comparando opciones, evalua que pasa si agrego o no una opcion a la solucion, calculando

$\Delta \text{satisfacción} = \text{nuevo} - \text{actual}$

para cada opcion, luego añade v a la solucion y pasa al siguiente anime en la lista.

- Diferencia con G1: se basa en mejoras incrementales de la situacion actual, en vez de elegir la mejor relacion global beneficio/costo

## Programa principal

general.cpp sigue la siguiente logica:

- Recorren a los casos de prueba

- Ejecutan los algoritmos por cada caso

- Miden resultados y tiempo utilizados

- Guardan los datos (measurements/ + outputs/)

Ademas cabe recalcar muy importante, los posibles casos a evaluar por pauta pueden ser de hasta n = 200, pero por la muchisima demora que causaba, se hizo solamente hasta n =30 ya que los otros casos tiraba TimeOut Error.

### Scripts

## Generacion de Gráficos 📊

```scripts/plot_generator.py``` lee todos los ```comp_datos.txt``` y ```comp_tiempo.txt``` dentro de ```data/measurements/``` y genera 6 graficos comparativos de velocidades segun el input mas la comparacion de respuestas optimas, los 4 outputs elegidos para los graficos de barras son un intento de tomar un promedio (1 grafico cada 3 casos de prueba), esto es completamente editable y no refleja cambios en las conclusiones de este proyecto.

- Eje X: tamaño del input (n)

- Eje Y: tiempo de ejecución en ms / satisfaccion del cliente

## Makefile 🏗️

El proyecto se controla con varias reglas:

| Comando         | Acción                                      |
|-----------------|---------------------------------------------|
| make crear      | Ejecuta el generador de testcases           |
| make run        | Ejecuta los .cpp sobre todos los inputs     |
| make graficar   | Genera los gráficos comparativos            |

Para ejecutar todo desde 0 se debe escribir en este orden ```make crear``` -> ```make run``` -> ```make graficar``` en el entorno que se va a trabajar, code/implementation/, acordar que estamos trabajando en la terminal de Ubuntu.
