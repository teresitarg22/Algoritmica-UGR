#include <iostream>
#include <vector>

using namespace std;

/*
    1. Averiguar el intervalo de los datos --> máximo y mínimo.
    2. Creamos el vector de números enteros: [minimo, maximo].
    3. A cada elemento se le da el elemento 0 (0 apariciones).
    4. Recorremos los elementos a ordenar y contamos el num de apariciones.
    5. Reconstruimos la lista ordenada utilizando el vector auxiliar.
*/

// ---------------------------------------------------------------------
// Función para averiguar el intervalo de los datos (máximo, mínimo)
void calculaIntervalo(const vector<int> &elementos, int &min, int &max){
    min = elementos[0]; // inicializamos el elemento mínimo.
    max = elementos[0]; // inicializamos el elemento máximo.

    // Buscamos el elemento más pequeño y el más grande recorriendo el vector.
    for(int i = 1; i < elementos.size(); i++){
        if(elementos[i] < min)
            min = elementos[i];
        else if(elementos[i] > max)
            max = elementos[i];
    }
}

// ---------------------------------------------------------------------
// Función que realiza el algoritmo de ordenamiento Counting Sort
void countingSort(vector<int> &elementos){
    int min = 0, max = 0;

    // 1. Averiguar el intervalo de los datos --> máximo y mínimo.
    calculaIntervalo(elementos, min, max);

    // 2. Creamos el vector de números enteros: [minimo, maximo].
    // 3. A cada elemento se le da el elemento 0 (0 apariciones).
    vector<int> aux;

    for(int i = 0; i < (max-min+1); i++){
        aux.push_back(0);
    }

    // 4. Recorremos los elementos a ordenar y contamos el num de apariciones (frecuencia).
    //    Almacenamos la frecuencia en el vector auxiliar.
    for(int i = 0; i < elementos.size(); i++) {
        int elemento = elementos[i];
        aux[elemento - min]++;
    }
    
    // 5. Reconstruimos la lista ordenada utilizando el vector auxiliar.
    int indice = 0;

    for(int i = min; i <= max; i++) {
        while(aux[i - min] > 0) {
            elementos[indice++] = i;
            aux[i - min]--;
        }
    }
}

// ----------------------------------------------

int main() {
    vector<int> elementos = {4, 2, 2, 8, 3, 3, 1};
    
    cout << "Lista original:" << endl;

    for (int elemento : elementos)
        cout << elemento << " ";
    cout << endl;

    countingSort(elementos);

    cout << "Lista ordenada:" << endl;
    for (int elemento : elementos)
        cout << elemento << " ";
    cout << endl;

    return 0;
}