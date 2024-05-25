#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

enum Movimiento { IZQUIERDA, DIAGONAL, ABAJO };

enum Casilla { VACIA, MURO, ORO };

std::map<Movimiento, std::pair<int, int>> movimientos = {
    {IZQUIERDA, {0, -1}},
    {DIAGONAL, {1, -1}},
    {ABAJO, {1, 0}}
};


vector<Movimiento> caminoMasOro(const vector<vector<Casilla>>& mapa) {
    
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

    vector<vector<Casilla>> mapa(tamVertical, vector<Casilla>(tamHorizontal));

    for (int i = 0; i < tamVertical; ++i)
        for (int j = 0; j < tamHorizontal; ++j) {
            int value;
            file >> value;
            // 0=VACIA, 1=MURO, 2=ORO
            mapa[i][j] = static_cast<Casilla>(value);
        }

    file.close();

    if (mapa[0][tamHorizontal-1]==MURO || mapa[tamVertical-1][0]==MURO) {
        cerr << "La casilla de salida o de fin no puede ser muro." << endl;
        return 1;
    }

    cout << "Mapa:" << endl;
    for (int i = 0; i < tamVertical; ++i) {
        for (int j = 0; j < tamHorizontal; ++j)
            cout << mapa[i][j] << '\t';
        cout << endl;
    }


}