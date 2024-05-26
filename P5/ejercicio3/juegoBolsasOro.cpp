#include <algorithm>
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <map>

using namespace std;

enum Movimiento { IZQUIERDA, DIAGONAL, ABAJO, NULO };


pair<vector<Movimiento>,int> caminoMasOro(const vector<vector<int>>& mapa) {
    int f = mapa.size();
    int c = mapa[0].size();

    vector<vector<pair<int, Movimiento>>> T(f, vector<pair<int, Movimiento>>(c, make_pair(INT_MIN, NULO)));

    T[0][c-1] = make_pair(static_cast<int>(mapa[0][c-1]), NULO);

    for (int i=0; i<f; i++)
        for (int j=c-1; j>=0; j--)
            if (mapa[i][j] != 2) {

                // Diagonal derecha arriba (el ancestro es el movimiento DIAGONAL IZQUIERDA ABAJO)
                if ( i-1>=0 && j+1<c && T[i-1][j+1].first != INT_MIN ) {
                    int nuevoValor = T[i-1][j+1].first + mapa[i][j];
                    if (nuevoValor > T[i][j].first)
                        T[i][j] = make_pair(nuevoValor, DIAGONAL);
                }
                
                // Derecha (el ancestro es el movimiento hacia la IZQUIERDA)
                if ( j+1<c && T[i][j+1].first != INT_MIN ) {
                    int nuevoValor = T[i][j+1].first + mapa[i][j];
                    if (nuevoValor > T[i][j].first)
                        T[i][j] = make_pair(nuevoValor, IZQUIERDA);
                }

                // Abajo (el ancestro es el movimiento hacia ARRIBA)
                if ( i-1>=0 && T[i-1][j].first != INT_MIN ) {
                    int nuevoValor = T[i-1][j].first + mapa[i][j];
                    if (nuevoValor > T[i][j].first)
                        T[i][j] = make_pair(nuevoValor, ABAJO);
                }
            }

    pair<vector<Movimiento>, int> solucion;

    int i = f-1, j = 0;

    while (T[i][j].second != NULO) {
        solucion.first.push_back(T[i][j].second);
        switch (T[i][j].second) {
            case IZQUIERDA:
                j++;
                break;
            case ABAJO:
                i--;
                break;
            case DIAGONAL:
                i--;
                j++;
                break;
            default:
                break;
        }
    }

    reverse(solucion.first.begin(), solucion.first.end());

    solucion.second = T[f-1][0].first;

    return solucion;
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nombre_archivo>" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int tamVertical, tamHorizontal;
    file >> tamVertical >> tamHorizontal;

    vector<vector<int>> mapa(tamVertical, vector<int>(tamHorizontal));

    for (int i = 0; i < tamVertical; ++i)
        for (int j = 0; j < tamHorizontal; ++j) {
            int value;
            file >> value;
            // 0=VACIA, 1=ORO, 2=MURO
            mapa[i][j] = value;
        }

    file.close();

    if (mapa[0][tamHorizontal-1]==2 || mapa[tamVertical-1][0]==2) {
        cerr << "La casilla de salida o de fin no puede ser muro." << endl;
        return 1;
    }

    cout << "Mapa:" << endl;
    for (int i = 0; i < tamVertical; ++i) {
        for (int j = 0; j < tamHorizontal; ++j)
            cout << mapa[i][j] << '\t';
        cout << endl;
    }

    pair<vector<Movimiento>, int> resultado = caminoMasOro(mapa);
    
    cout << endl << "Camino con mas oro: \n{";
    for (auto movimiento : resultado.first) {
        switch (movimiento) {
            case IZQUIERDA:
                cout << "IZQUIERDA ";
                break;
            case DIAGONAL:
                cout << "DIAGONAL ";
                break;
            case ABAJO:
                cout << "ABAJO ";
                break;
            default:
                break;
        }
        
        cout << ", ";
    }

    

    cout << "}\n\nOro total: " << resultado.second << endl;
}