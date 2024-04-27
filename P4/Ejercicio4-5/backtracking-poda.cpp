#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Nodo {
    pair<int,int> pos = make_pair(0,0);
    const Nodo *padre = nullptr;
};

vector<Nodo> generarHijos(const Nodo& nodo, const unordered_map<pair<int,int>,bool>& casillas_visitadas, const vector<vector<bool>>& laberinto) {
    vector<Nodo> hijos;
    int x = nodo.pos.first;
    int y = nodo.pos.second;

    Nodo hijo;

    // Tenemos en cuenta los límites del laberinto para que no genere hijos fuera de él

    // Movimiento hacia arriba
    if ( x > 0 && laberinto[x-1][y] && !casillas_visitadas.at(make_pair(x-1, y)) ) {
        hijo.pos = make_pair(x-1, y);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
    }

    // Movimiento hacia abajo
    if ( x < laberinto.size()-1 && laberinto[x+1][y] && !casillas_visitadas.at(make_pair(x+1, y)) ) {
        hijo.pos = make_pair(x+1, y);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
    }

    // Movimiento hacia la izquierda
    if ( y > 0 && laberinto[x][y-1] && !casillas_visitadas.at(make_pair(x, y-1)) ) {
        hijo.pos = make_pair(x, y-1);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
    }

    // Movimiento hacia la derecha
    if ( y < laberinto[0].size()-1 && laberinto[x][y+1] && !casillas_visitadas.at(make_pair(x, y+1)) ) {
        hijo.pos = make_pair(x, y+1);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
    }

    return hijos;
}


// Dado que tamaño mínimo debe ser 3x3 y la salida es  n-1,n-1, la casilla 0,0 nunca podrá ser de salida
vector<pair<int,int>> backtracking(const vector<vector<bool>>& laberinto,  unordered_map<pair<int,int>,bool>& casillas_visitadas, Nodo actual = Nodo()) {

    cout << "Actual: " << actual.pos.first << " " << actual.pos.second << endl;

    casillas_visitadas[actual.pos] = true;

    vector<Nodo> hijos = generarHijos(actual, casillas_visitadas, laberinto);
                                                                                                                                                                                                                                                                             
    for (const auto& n : hijos){
        if (n.pos == make_pair(int(laberinto.size()-1), int(laberinto[0].size()-1))){
            vector<pair<int,int>> resultado;
            Nodo aux = n;

            while (aux.padre != nullptr){
                resultado.push_back(actual.pos);
                aux = *(n.padre);
            }

            return resultado;
        }
        else {
            vector<pair<int,int>> resultado = backtracking(laberinto, casillas_visitadas, n);
            if (!resultado.empty())
                return resultado;
        } 
    }
}

vector<pair<int,int>> poda(const vector<vector<bool>>& laberinto) {

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

    int tam;
    file >> tam;

    vector<vector<bool>> laberinto(tam, vector<bool>(tam));
    unordered_map<pair<int,int>,bool> casillas_visitadas = {{}};

    for (int i = 0; i < tam; ++i)
        for (int j = 0; j < tam; ++j) {
            int value;
            file >> value;
            laberinto[i][j] = value;
            if (value)
                casillas_visitadas[make_pair(i,j)] = false;
        }

    file.close();


    cout << "Laberinto:" << endl;
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j)
            cout << laberinto[i][j] << " ";

        cout << endl;
    }

    
    // Hemos supuesto que el tamaño mínimo de la matriz ha de ser de 3x3
    if (tam < 3 || laberinto.size() != tam || laberinto[0].size() != tam) {
        cerr << "El tamaño de la matriz debe ser al menos 3x3 y cuadrada." << endl;
        return 1;
    }

    if (!laberinto[0][0]) {
        cerr << "La casilla de salida debe estar vacía." << endl;
        return 1;
    }


    vector<pair<int,int>> resultado_backtracking = backtracking(laberinto, casillas_visitadas);

    // vector<pair<int,int>> resultado_poda = poda(laberinto);


    cout << endl << "Resultado Backtracking:" << endl;

    if (resultado_backtracking.empty())
        cout << "No existe una solución en Backtracking para ir desde la casilla {0,0} a la {" << laberinto.size()-1 << "," << laberinto[0].size()-1 << "}." << endl;

    else
        for (const auto& p : resultado_backtracking)
            cout << "(" << p.first << ", " << p.second << ")" << endl;


    // cout << endl << "Resultado Poda:" << endl;

    // if (resultado_poda.empty())
    //     cout << "No existe una solución en Poda para ir desde la casilla {0,0} a la {" << laberinto.size()-1 << "," << laberinto[0].size()-1 << "}." << endl;

    // else
    //     for (const auto& p : resultado_poda)
    //         cout << "(" << p.first << ", " << p.second << ")" << endl;


    return 0;
}