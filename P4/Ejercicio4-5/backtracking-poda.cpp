#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    ifstream file("input.txt");

    if (!file) {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    int tam;
    file >> tam;

    vector<vector<bool>> laberinto(tam, vector<bool>(tam));

    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            int value;
            file >> value;
            laberinto[i][j] = value;
        }
    }

    file.close();

    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            cout << laberinto[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}