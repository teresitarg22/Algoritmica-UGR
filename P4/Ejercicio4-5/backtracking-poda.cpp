#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
    pair<int,int> pos;
    int longitud; // Longitud del camino desde el inicio hasta este nodo, para B&B
    const Nodo *padre;

    Nodo(pair<int, int> pos, int len, const Nodo* par) : pos(pos), longitud(len), padre(par) {}
    Nodo() : pos(make_pair(0,0)), longitud(0), padre(nullptr) {}
};

vector<Nodo> generarHijos(const Nodo& nodo, const vector<vector<bool>>& casillas_visitadas, const vector<vector<bool>>& laberinto) {
    vector<Nodo> hijos;
    int x = nodo.pos.first;
    int y = nodo.pos.second;
            

    Nodo hijo;
   
    // Tenemos en cuenta los límites del laberinto para que no genere hijos fuera de él

    // Movimiento hacia arriba
    if ( x > 0 && laberinto[x-1][y] && !casillas_visitadas[x-1][y] ) {
        hijo.pos = make_pair(x-1, y);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
       
    }

    // Movimiento hacia abajo
    if ( x < laberinto.size()-1 && laberinto[x+1][y] && !casillas_visitadas[x+1][y] ) {
        hijo.pos = make_pair(x+1, y);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
        
    }

    // Movimiento hacia la izquierda
    if ( y > 0 && laberinto[x][y-1] && !casillas_visitadas[x][y-1] ) {
        hijo.pos = make_pair(x, y-1);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
       
    }

    // Movimiento hacia la derecha
    if ( y < laberinto[0].size()-1 && laberinto[x][y+1] && !casillas_visitadas[x][y+1] ) {
        hijo.pos = make_pair(x, y+1);
        hijo.padre = &nodo;
        hijos.push_back(hijo);
        
    }
 
    return hijos;
}


// Dado que tamaño mínimo debe ser 3x3 y la salida es  n-1,n-1, la casilla 0,0 nunca podrá ser de salida
vector<pair<int,int>> backtracking(const vector<vector<bool>>& laberinto, vector<vector<bool>>& casillas_visitadas, Nodo actual = Nodo()) {

    casillas_visitadas[actual.pos.first][actual.pos.second] = true;

    vector<Nodo> hijos = generarHijos(actual, casillas_visitadas, laberinto);
                                                                                                                                                                                                                                                                  
    for (const auto& n : hijos)
        if (n.pos == make_pair(int(laberinto.size()-1), int(laberinto[0].size()-1))){
            vector<pair<int,int>> resultado;
            Nodo aux = n;

            while (aux.padre != nullptr){
                resultado.push_back(aux.pos);
                aux = *(aux.padre);
            }

            resultado.push_back(aux.pos);

            return resultado;
        }
        else {
            vector<pair<int,int>> resultado = backtracking(laberinto, casillas_visitadas, n);
            if (!resultado.empty())
                return resultado;
        } 

    return vector<pair<int,int>>();
}

vector<pair<int,int>> poda(const vector<vector<bool>>& laberinto, vector<vector<bool>>& casillas_visitadas, Nodo inicial = Nodo()) {
   int n = laberinto.size();
    priority_queue<pair<int, Nodo*>> cola_prioridad;

    cola_prioridad.push({0, new Nodo({0, 0}, 0, nullptr)});
    vector<pair<int, int>> camino_mas_corto;

    int longitud_minima = INT_MAX;

    while (!cola_prioridad.empty()) {
        const Nodo* actual = cola_prioridad.top().second;
        int longitud = -cola_prioridad.top().first;
        cola_prioridad.pop();

        if (actual->pos == make_pair(n - 1, n - 1)) {
            // Encontramos la salida
            camino_mas_corto.clear();
            while (actual != nullptr) {
                camino_mas_corto.push_back(actual->pos);
                actual = actual->padre;
            }
            reverse(camino_mas_corto.begin(), camino_mas_corto.end());
            longitud_minima = longitud;
            break;
        }

        if (longitud >= longitud_minima) {
            // Podar si la longitud actual es mayor o igual a la longitud mínima encontrada hasta el momento
            continue;
        }

        casillas_visitadas[actual->pos.first][actual->pos.second] = true;

        vector<Nodo> hijos = generarHijos(*actual, casillas_visitadas, laberinto);
        for (auto& hijo : hijos) {
            int longitud_hijo = longitud + 1;
            cola_prioridad.push({-longitud_hijo, new Nodo(hijo.pos, longitud_hijo, actual)});
        }
    }

    // Liberar la memoria de los nodos creados
    while (!cola_prioridad.empty()) {
        delete cola_prioridad.top().second;
        cola_prioridad.pop();
    }

    return camino_mas_corto;
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
    vector<vector<bool>> casillas_visitadas(tam, vector<bool>(tam));
    vector<vector<bool>> casillas_visitadas_poda(tam, vector<bool>(tam));

    for (int i = 0; i < tam; ++i)
        for (int j = 0; j < tam; ++j) {
            int value;
            file >> value;
            laberinto[i][j] = value;
            casillas_visitadas[i][j] = false;
            casillas_visitadas_poda[i][j] = false;
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

    
    vector<pair<int,int>> resultado_backtracking = backtracking(laberinto,casillas_visitadas);
    reverse(resultado_backtracking.begin(), resultado_backtracking.end());
    

    cout << endl << "Resultado Backtracking:" << endl;

    if (resultado_backtracking.empty())
        cout << "No existe una solución en Backtracking para ir desde la casilla {0,0} a la {" << laberinto.size()-1 << "," << laberinto[0].size()-1 << "}." << endl;

    else
        for (const auto& p : resultado_backtracking)
            cout << "(" << p.first << ", " << p.second << ")" << " ";

    vector<pair<int,int>> resultado_poda = poda(laberinto, casillas_visitadas_poda);
   // reverse(resultado_poda.begin(), resultado_poda.end());

    cout << endl << "Resultado Poda:" << endl;

    if (resultado_poda.empty())
        cout << "No existe una solución en Poda para ir desde la casilla {0,0} a la {" << laberinto.size()-1 << "," << laberinto[0].size()-1 << "}." << endl;

    else
        for (const auto& p : resultado_poda)
            cout << "(" << p.first << ", " << p.second << ")" << " ";


    return 0;
}