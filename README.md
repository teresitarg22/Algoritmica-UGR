# :chart_with_upwards_trend: Algorítmica

En este repositorio vamos a reflejar el trabajo que realizamos en la asignatura de Algorítmica de Ingeniería Informática.

### :bulb: Miembros del equipo de desarrollo

- :bust_in_silhouette: España Maldonado, Sergio
- :bust_in_silhouette: López García, Manuel Jesús
- :bust_in_silhouette: Reyes García, Teresa Fernanda
- :bust_in_silhouette: Rincón Otero, Marta
- :bust_in_silhouette: Velázquez Ortuño, Diego

## :file_folder: Práctica 1 : Cálculo de la eficiencia de algoritmos

El **objetivo** de la práctica consiste en que seamos capaces de analizar y calcular la eficiencia teórica, práctica e híbrida de algoritmos. En esta práctica vamos a trabajar con algoritmos de ordenación concretamente.

- Eficiencia teórica.
- Eficiencia práctica.
- Eficiencia híbrida.
  - Cálculo de la constante oculta.
 
Los **algoritmos de ordenación** son utilizados para organizar un conjunto de datos en un orden específico basado en algún criterio concreto. La elección de un algoritmo de ordenación adecuado para un problema depende de factores como el tamaño del conjunto de datos, la naturaleza de los mismos… En esta práctica vamos a trabajar con los siguientes algoritmos.

- Algoritmo de conteo o counting sort.
- Algoritmo de inserción o insertion sort.
- Algoritmo rápido o quicksort.
- Algoritmo de selección o selection sort.
- Algoritmo de ordenamiento shell o shell sort.


## :file_folder: Práctica 2 : Algoritmos Divide y Vencerás

El **objetivo** de la práctica consiste en que analicemos una serie de problemas propuestos y elaboremos para cada uno de ellos un diseño mediante un método básico, junto el análisis de su eficiencia, un diseño mediante Divide y Vencerás, junto el análisis de su eficiencia, y una implementación de ambos diseños en C++. Trataremos de resolver el problema del umbral de forma experimental.

Los problemas que se van a abordar en esta práctica son los siguientes:

- **La mayoría absoluta.** El problema consiste en determinar si en unas elecciones, representadas por un vector de n votos, hay algún candidato que obtenga mayoría absoluta (n/2 + 1).

- **Tuercas y tornillos.** Se plantea emparejar cada tornillo con su tuerca correspondiente, pero los elementos de cada conjunto no se pueden comparar entre sí directamente. 

- **Producto de tres elementos.** Buscar si un número natural dado N puede ser expresado como el producto de tres números naturales consecutivos, es decir, encontrar si existe un valor k tal que k * (k+1) * (k+2) = N.

- **Eliminar elementos repetidos.** Dado un vector de elementos, se requiere eliminar los elementos duplicados, es decir, aquellos que aparezcan más de una vez en el vector.

- **Organización del calendario de un campeonato.** Se trata de organizar un torneo entre n participantes de manera que cada uno compita exactamente una vez contra todos los demás. Se debe generar una tabla de emparejamientos consistente que permita cumplir con esta condición en un número mínimo de jornadas.


## :file_folder: Práctica 3 : Algoritmos Voraces

El **objetivo** de la práctica consiste en que el alumno sea capaz de analizar una serie de problemas y resolverlos mediante la técnica Greedy (algoritmos voraces), siendo capaz de justificar su eficacia en términos de optimalidad.  Cada ejercicio será evaluado según diferentes criterios, que incluyen el diseño de componentes, el diseño del algoritmo, el estudio de optimalidad, ejemplos paso a paso y el correcto funcionamiento de la implementación.

Los problemas que se van a abordar en esta práctica son los siguientes:

- **Problema 1** – Este problema plantea la formación de parejas entre los estudiantes de una clase, buscando la maximización de la satisfacción de los estudiantes de la clase.

- **Problema 2** – Este problema consiste en asignar asientos a los invitados de una cena, alrededor de una mesa circular. Buscamos maximizar el nivel de conveniencia total entre los invitados. Se tendrá en cuenta, por tanto, la conveniencia de cada par de invitados contiguos.

- **Problema 3** – El problema consiste en minimizar el número de paradas de un autobús durante una ruta determinada. Con el tanque de gasolina lleno, el autobús puede recorrer k kilómetros sin parar.

- **Problema 4** – El problema consiste en minimizar el tiempo de envío de datos entre los sensores de una red de sensores inalámbrica. Para cada par de nodos sensores de la red ni, nj (entre los que se incluye el servidor central), conocemos el tiempo de envío entre ambos nodos como t(ni, nj).

- **Problema 5** – El problema plantea la solución de asfaltar el número de calles necesarias que permitan acceder a todas las plazas de un pueblo. Buscamos dar como resultado un conjunto de calles tal que, si las asfaltamos, se puede ir de una plaza a otra con el coste total mínimo.


## :file_folder: Práctica 4 : Algoritmos de exploración de grafos.

El objetivo de la práctica consiste en que seamos capaces de analizar una serie de problemas y resolverlos mediante las técnicas de diseño de algoritmos basadas en exploración de grafos. Los problemas que se van a abordar en esta práctica son los siguientes:

- **Problema 1** – emparejar n estudiantes en parejas, maximizando la suma de los valores de emparejamiento. Cada estudiante tiene un nivel de preferencia para trabajar con otros estudiantes, representado en una matriz p de tamaño n×n. Se busca encontrar el emparejamiento óptimo.

- **Problema 2** – organizar la distribución de n invitados alrededor de una mesa circular, donde cada invitado tiene asignados dos asientos contiguos. Cada par de invitados tiene un nivel de conveniencia asociado, que indica cuán deseable es que se sienten juntos. El objetivo es maximizar el nivel total de conveniencia de la distribución de invitados en la mesa.

- **Problema 3**– algoritmo de backtracking que encuentre una serie de movimientos para alcanzar con éxito el final del juego Senku, consistente en dejar solo una pieza en el tablero, ubicada en la posición central. 

- **Problema 4 y 5** – encontrar un camino desde la entrada hasta la salida de un laberinto representado por una matriz bidimensional. Para el problema 4 se pide usar backtracking, mientras que para el problema 5 aplicar B&B.


## :file_folder: Práctica 5 : Algoritmos de exploración de grafos.

El objetivo de la práctica consiste en que seamos capaces de analizar un problema y resolverlo mediante la técnica de Programación Dinámica, siendo capaz de justificar su eficacia en términos de optimalidad. Los problemas que se van a abordar en esta práctica son los siguientes:

- **Problema 1** – A lo largo de un río hay n aldeas, donde en cada una se puede alquilar una canoa para viajar a otras aldeas. Determinar el coste mínimo de viajar en canoa a favor de la corriente desde cualquier aldea 𝑖 hasta cualquier aldea 𝑗 (donde 𝑖 < 𝑗) a lo largo de un río.

- **Problema 2** – Se realizan planificaciones de viajes aéreos entre n ciudades, donde para llegar de una ciudad a otra puede ser necesario coger varios vuelos. Conocer la forma de volar desde cualquier ciudad i hasta cualquier otra j en el menor tiempo posible.

- **Problema 3** – Un videojuego que se juega por turnos y está basado en avanzar por un mapa, por las casillas transitables, hasta llegar a la salida pudiendo recoger tanto oro como sea posible. El jugador tiene una serie de movimientos permitidos que podrá realizar para encontrar la salida. Cada casilla del mapa puede estar vacía, contener un muro, o contener una bolsa de oro. Todas las casillas son transitables salvo las que tienen muros.

- **Problema 4** – Trata de avanzar por una montaña, ascendiendo desde una posición baja hasta la cumbre, buscando el recorrido con menor dificultad. En la ascensión siempre se sube (sin desfallecer) pero moviéndose directamente hacia arriba, o desplazándose a la izquierda o derecha en diagonal. En cada posible posición de la montaña hay un coste asociado de la dificultad que tiene llegar a esa posición.



