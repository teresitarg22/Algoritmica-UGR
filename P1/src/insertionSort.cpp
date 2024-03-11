#include <iostream>
#include <vector>
#include "../include/insertionSort.h"

using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int izq = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > izq) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = izq;
    }
}
