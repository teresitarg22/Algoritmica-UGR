#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

void unir(std::vector<int>& vec, std::vector<int>& vIzq, int& pivote, std::vector<int>& vDcha);
int comparaTres(std::vector<int>& vec);
void quickSort(std::vector<int>& vec);

#endif // QUICKSORT_H
