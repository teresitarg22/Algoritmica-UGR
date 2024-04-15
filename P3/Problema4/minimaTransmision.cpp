#include <iostream>
#include <vector>
#include <limits>

#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int infinito = numeric_limits<int>::max();

// ------------------------------------------------------------------
// Función encargada de calcular la mínima transmisión entre nodos
// ------------------------------------------------------------------
pair<vector<int>, vector<char>> minimaTransmision(vector<vector<int>> &L, vector<char> &S){
    // 1. Inicialización de los conjuntos principales.
    int n = L.size(); // Número de nodos sensores.

    vector<char> C; // Conjunto de nodos candidatos.
    vector<char> P(n, 'S'); // Conjunto de nodos predecesores.
    vector<int> D(n, numeric_limits<int>::max()); // Distancia mínima entre el nodo S y los demás nodos.
    

    // Inicializar el conjunto de candidatos : {A, B, ..., n}
    for(int i = 1; i < n; i++){
        char nodo = 'A' + i - 1;
        C.push_back(nodo);
    }

    cout << endl;

    // Inicializar la distancia mínima entre el nodo S y los demás nodos + los predecesores.
    for(int i = 0; i < n; i++){
        D[i] = L[0][i];
    }

    // 2. Selección de nodos
    while(!C.empty()){
        char v = C[0];
        int posV = -1;
        int minDist = infinito;

        for(int i = 0; i < C.size(); i++){
            char letraNodo = C[i];
            int pos = letraNodo - 'A' + 1;

            if(D[pos] < minDist && D[pos] > 0){
                v = C[i];
                posV = pos;
                minDist = D[pos];
            }
        }

        char nodoBorrar = 'A' + posV-1;     // Nodo a borrar del conjunto de candidatos.
        int posBorrar = -1;                 // Posición del nodo a borrar en el conjunto de candidatos.

        // Buscamos en el conjunto de candidatos la posición del nodo seleccionado.
        for(int i = 0; i < C.size(); i++){
            if(C[i] == nodoBorrar){
                posBorrar = i;
                break;
            }
        }

        // Agregar el nodo v al conjunto de seleccionados.
        S.push_back(v);
        C.erase(C.begin() + posBorrar);

        for(int j = 0; j < C.size(); j++){
            char letraNodo = C[j];
            int pos = letraNodo - 'A' + 1;

            // Si el nodo seleccionado tiene conexión con el nodo candidato j:
            if(L[posV][pos] != infinito){
                if(D[pos] > D[posV] + L[posV][pos]){
                    D[pos] = D[posV] + L[posV][pos];
                    P[pos] = v;
                }
            }
        }
    }

    // 4. Soluciones obtenidas.
    return make_pair(D, P);
}

// -------------------------------------------------------
// Función encargada de generar matrices de adyacencia.
// -------------------------------------------------------
vector<vector<int>> generarMatrizAdyacencia(int n){
    // Inicialización de la matriz de adyacencia.
    vector<vector<int>> matriz(n+1, vector<int>(n+1, infinito));

    // La diagonal sabemos que será 0.
    for(int i = 0; i < n+1; i++){
        matriz[i][i] = 0;
    }
    
    // Generar las distancias entre los nodos. Habrá nodos que no tengan conexión directa.
    srand(time(0));
    for(int i = 0; i < n+1; i++){
        for(int j = i + 1; j < n+1; j++){
            // Generar un número aleatorio.
            int probabilidad = rand() % 10 ;

            if(probabilidad > 3){
                int distancia = rand() % 10 + 1;
                matriz[i][j] = distancia;
                matriz[j][i] = distancia;
            }
            else{
                matriz[i][j] = infinito;
                matriz[j][i] = infinito;
            }
        }
    }

    return matriz;
}

// -------------------------------------------------------
// Función encargada de imprimir la matriz.
// -------------------------------------------------------
void imprimirMatriz(const vector<vector<int>>& matriz) {
    // Imprimir la primera fila con los nombres de los nodos
    cout << setw(3) << " ";
    cout << setw(3) << "S";
    for (int i = 0; i < matriz.size()-1; ++i) {
        cout << setw(6) << char('A' + i);
    }
    cout << endl;

    // Separador entre la primera fila y el contenido de la matriz
    cout << setw(3) << "-----";
    for (int i = 0; i < matriz.size()-1; ++i) {
        cout << setw(6) << "------";
    }
    cout << endl;

    // Imprimir el contenido de la matriz
    for (int i = 0; i < matriz.size(); ++i) {
        if(i == 0){
            cout << setw(3) << "  S |";
        }
        else{
            cout << setw(3) << char('A' + i - 1) << " |";
        }

        for (int j = 0; j < matriz[i].size(); ++j) {
            if (matriz[i][j] == infinito) {
                cout << setw(4) << "  ∞ " << " "; // Imprimir infinito si la distancia es infinita
            } else {
                cout << setw(4) << matriz[i][j] << " "; // Imprimir la distancia
            }
        }
        cout << endl;
    }
}

// --------------------------------------------------------------

int main(){
    
    int n;
    cout << "Ingrese el número de nodos sensores: ";
    cin >> n;

    // 1. Generar la matriz de adyacencia.
    vector<vector<int>> L = generarMatrizAdyacencia(n);

    // 2. Imprimir la matriz de adyacencia.
    cout << "Matriz de adyacencia: " << endl;
    imprimirMatriz(L);

    // 3. Definir la lista de seleccionados al inicio.
    vector<char> S;
    S.push_back('S');

    // 4. Calcular la mínima transmisión entre nodos.
    pair<vector<int>, vector<char>> solucion = minimaTransmision(L, S);

    // 5. Imprimir la solución. 
    cout << "\n-----------------";
    cout << "\nRESULTADOS " << endl;

    cout << "\nNodos seleccionados: ";
    for(int i = 0; i < S.size(); i++){
        cout << S[i] << " ";
    }
    cout << endl;

    cout << "Distancias mínimas: ";
    for(int i = 0; i < solucion.first.size(); i++){
        if(solucion.first[i] == infinito){
            cout << " ∞ ";
        }
        else{
            cout << solucion.first[i] << " ";
        }
    }
    cout << endl;

    cout << "Predecesores: ";
    for(int i = 0; i < solucion.second.size(); i++){
        cout << solucion.second[i] << " ";
    }
    cout << endl;

    return 0;
}


