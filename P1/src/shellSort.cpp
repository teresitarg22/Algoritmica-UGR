#include <iostream>
#include <vector>
#include "../include/shellSort.h"

using namespace std;

// ---------------------------------------------------------------------
// Función que realiza el algoritmo de ordenamiento Shell Sort
void shellSort(vector<int> &vec){
    int gap = vec.size()/2;
    
    while(gap > 0){
        for(int i = gap; i<vec.size(); i++){
            int seleccionado = vec[i];
            int indice = i;
            while (indice >= gap && vec[indice-gap] > seleccionado) {
                int aux = vec [indice];
                vec[indice] = vec[indice-gap];
                vec[indice-gap] = aux;
                indice = indice - gap;
            }
        }
        gap = gap/2;
    }
}

