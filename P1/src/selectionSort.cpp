#include <iostream>
#include <vector>
#include "../include/selectionSort.h"

using namespace std;

void selectionSort(vector<int> & vec){
    int min, aux;

    for(int i=0; i<vec.size(); i++) {
        min = i;

        for(int j = i+1; j < vec.size(); j++)
            if(vec[j] < vec[min])
                min = j;

        aux = vec[i];
        vec[i] = vec[min];
        vec[min] = aux;
    }
}

