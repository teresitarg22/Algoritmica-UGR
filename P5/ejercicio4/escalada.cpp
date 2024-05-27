#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int minDifficultyPath(const vector<vector<int>>& cost) {
    int n = cost.size();    // número de filas
    int m = cost[0].size(); // número de columnas

    // Inicializar la matriz dp con los mismos valores que cost para la primera fila
    vector<vector<int>> dp(n, vector<int>(m, INT_MAX));
    for (int j = 0; j < m; ++j) {
        dp[0][j] = cost[0][j];
    }

    // Llenar la matriz dp
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                dp[i][j] = cost[i][j] + min(dp[i-1][j], dp[i-1][j+1]);
            } else if (j == m-1) {
                dp[i][j] = cost[i][j] + min(dp[i-1][j-1], dp[i-1][j]);
            } else {
                dp[i][j] = cost[i][j] + min({dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1]});
            }
        }
    }

    // Encontrar el coste mínimo en la última fila
    int minCost = INT_MAX;
    for (int j = 0; j < m; ++j) {
        minCost = min(minCost, dp[n-1][j]);
    }

    return minCost;
}

int main() {
    vector<vector<int>> cost = {
        {2, 8, 9, 5, 8},
        {4, 4, 6, 2, 3},
        {5, 7, 5, 6, 1},
        {3, 2, 5, 4, 8}
    };

    cout << "El costo mínimo para subir la montaña es: " << minDifficultyPath(cost) << endl;

    return 0;
}
