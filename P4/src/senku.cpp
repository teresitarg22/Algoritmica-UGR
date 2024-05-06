#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------------------
// Función para mostrar el tablero
void mostrarTablero(const vector<vector<char>> &tablero) {
    for (size_t i = 0; i < tablero.size(); i++) {
        for (size_t j = 0; j < tablero[i].size(); j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

// -------------------------------------------------------------------------------
// Función para comprobar si un movimiento es factible: cumple las normas
bool factible(int x1, int y1, int x2, int y2, const vector<vector<char>> &tablero) {
    // ¿Es válido el movimiento de (x1,y1) a (x2,y2)?
    if (tablero[x1][y1] == 'O' && tablero[x2][y2] == ' ' && ((x1 == x2 && abs(y1 - y2) == 2) || (y1 == y2 && abs(x1 - x2) == 2))) {
        // ¿Hay una canica entre (x1,y1) y (x2,y2)?
        if (tablero[(x1 + x2) / 2][(y1 + y2) / 2] == 'O') {
            return true;
        }
    }

    return false;
}

// -------------------------------------------------------------------------------
// Función principal para resolver el problema
bool senku(vector<vector<char>> &tablero, int &canicas) {
    vector<pair<int, int>> direcciones = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool final = false;

    // ¿Hemos llegado al estado final?
    if (canicas == 1 && tablero[3][3] == 'O') {
        cout << "¡Solución encontrada!\n" << endl;
        return true;
    } 
    else{
        // Recorremos nuestro tablero en busca de movimientos
        for (size_t i = 0; i < tablero.size(); i++) {
            for (size_t j = 0; j < tablero[i].size(); j++) {
                // Si hay una canica en la posición (i,j)
                if (tablero[i][j] == 'O') {
                    // Calculamos posibles movimientos para cada dirección
                    for (auto dir : direcciones) {
                        int x2 = i + (2 * dir.first);
                        int y2 = j + (2 * dir.second);

                        // Si el movimiento es factible, actualizamos el tablero
                        if(x2 >= 0 && x2 < (int)tablero.size() && y2 >= 0 && y2 < (int)tablero[i].size()){
                            if (factible(i, j, x2, y2, tablero)) {
                                tablero[i][j] = ' ';                        // Pos inicial
                                tablero[(i + x2) / 2][(j + y2) / 2] = ' ';  // Pos intermedia
                                tablero[x2][y2] = 'O';                      // Pos final
                                canicas--;

                                if (senku(tablero, canicas)) {   // RECURSIVIDAD
                                    final = true;

                                    // Imprimimos el movimiento
                                    cout << "Movimiento: (" << i << "," << j << ") -> (" << x2 << "," << y2 << ")" << endl;
                                }
                                else{
                                    // Si la llamada recursiva no da solución, BACKTRACKING:
                                    tablero[i][j] = 'O';                        // Pos inicial
                                    tablero[(i + x2) / 2][(j + y2) / 2] = 'O';  // Pos intermedia
                                    tablero[x2][y2] = ' ';                      // Pos final
                                    canicas++;
                                }

                                if (final) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Si no hay solución:
    return false;
}

// -------------------------------------------------------------------------------

int main() {

    // ESTADO INICIAL DEL PROBLEMA:
    // 'X' -- posición no válida
    // 'O' -- posición de una canica
    // ' ' -- posición vacía
    vector<vector<char>> tablero = {
        {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', ' ', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'O', 'O', 'X', 'X'}
    };

    int canicas = 32;

    if (senku(tablero, canicas)) {
        cout << "\nTablero final:\n" << endl;
        mostrarTablero(tablero);
    } else {
        cout << "No hay solución" << endl;
    }

    return 0;
}
