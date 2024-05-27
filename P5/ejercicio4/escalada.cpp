#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

pair<int, vector<int>> minDifficultyPath(const vector<vector<int>>& montana) {
    int n = montana.size();    // número de filas
    int m = montana[0].size(); // número de columnas

    // Inicializar la matriz d con los mismos valores que montana para la primera fila
    vector<vector<int>> d(n, vector<int>(m, INT_MAX));
    vector<vector<int>> path(n, vector<int>(m, -1)); // Para rastrear el camino

    for (int j = 0; j < m; ++j) {
        d[0][j] = montana[0][j];
    }

    // Llenar la matriz d y mantener rastreo del camino
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0 && d[i][j] > montana[i][j] + d[i-1][j-1]) {
                d[i][j] = montana[i][j] + d[i-1][j-1];
                path[i][j] = j-1;
            }
            if (d[i][j] > montana[i][j] + d[i-1][j]) {
                d[i][j] = montana[i][j] + d[i-1][j];
                path[i][j] = j;
            }
            if (j < m-1 && d[i][j] > montana[i][j] + d[i-1][j+1]) {
                d[i][j] = montana[i][j] + d[i-1][j+1];
                path[i][j] = j+1;
            }
        }
    }

    // Encontrar el coste mínimo en la última fila y su posición
    int minCost = INT_MAX;
    int minIndex = -1;
    for (int j = 0; j < m; ++j) {
        if (d[n-1][j] < minCost) {
            minCost = d[n-1][j];
            minIndex = j;
        }
    }

    // Reconstruir el camino desde la cima a la base
    vector<int> bestPath(n);
    int currentIndex = minIndex;
    for (int i = n-1; i >= 0; --i) {
        bestPath[i] = currentIndex;
        currentIndex = path[i][currentIndex];
    }

    return {minCost, bestPath};
}

int main() {
    vector<vector<int>> montana = {
        {1, 3, 2, 4},
        {4, 8, 1, 6},
        {3, 2, 1, 7},
        {6, 2, 3, 4}
    };

    auto result = minDifficultyPath(montana);
    int minCost = result.first;
    vector<int> path = result.second;
    reverse(path.begin(), path.end()); // Invertir el camino (de base a cima

    cout << "El costo mínimo para subir la montaña es: " << minCost << endl;
    cout << "El camino tomado es: ";
    for (int pos : path) {
        cout << pos << " ";
    }
    cout << endl;

    return 0;
}
