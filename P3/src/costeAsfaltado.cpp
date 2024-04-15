#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string vectorPair_toString(const vector<pair<int,int>>& pares) {
    string resultado = "";

    resultado += "{";
    for (const auto& par : pares) {
        resultado += " {";
        resultado += to_string(par.first);
        resultado += ",";
        resultado += to_string(par.second);
        resultado += "}";
    }
    resultado += " } ó ";

    resultado += "{";
    for (const auto& par : pares) {
        resultado += " {";
        resultado += static_cast<char>('a' + par.first);
        resultado += static_cast<char>('a' + par.second);
        resultado += "}";
    }
    resultado += " }";

    return resultado;
}

int encontrarComponente(vector<vector<int>>& componenteConexa, int plaza) {
    for (vector<vector<int>>::size_type i=0; i<componenteConexa.size(); i++)
        for (vector<int>::size_type j=0; j<componenteConexa[i].size(); j++)
            if (componenteConexa[i][j] == plaza)
                return i;
    return -1;
}

pair<int,vector<pair<int,int>>> kruskal(vector<vector<int>>& matrizPlazas_Costes) {
    int n_P = matrizPlazas_Costes.size();

    vector< pair< pair<int,int>, int >> calles;

    for (int i=0; i<n_P; i++)
        for (int j=i+1; j<n_P; j++)
            if (matrizPlazas_Costes[i][j] != -1)
                calles.push_back({{i, j},matrizPlazas_Costes[i][j]});

    sort(calles.begin(), calles.end(), [](pair<pair<int,int>,int> a, pair<pair<int,int>,int> b) {
        return a.second < b.second;
    });

    vector<vector<int>> componentesConexas;
    for (int i = 0; i < n_P; ++i)
        componentesConexas.push_back({i});

    int costeTotal = 0;
    vector<pair<int,int>> callesAsfaltadas;

    for (auto calle : calles) {
        int p1 = calle.first.first;
        int p2 = calle.first.second;
        int coste = calle.second;

        int componenteP1 = encontrarComponente(componentesConexas, p1);
        int componenteP2 = encontrarComponente(componentesConexas, p2);

        if (componenteP1 == -1 || componenteP2 == -1) {
            cerr << "Error: nodo no pertenece a ninguna componente" << endl;
            exit(1);
        }

        if (componenteP1 != componenteP2) {
            costeTotal += coste;
            callesAsfaltadas.push_back({p1,p2});

            for (int plaza : componentesConexas[componenteP2])
                componentesConexas[componenteP1].push_back(plaza);

            componentesConexas.erase(componentesConexas.begin() + componenteP2);
        }

        if (componentesConexas.size() == 1)
            break;
    }

    return {costeTotal, callesAsfaltadas};
}

int main() {
    string archivo = "matrizPlazas.txt";
    ifstream entrada(archivo);

    if (!entrada.is_open()) {
        cout << "Error al abrir el archivo " << archivo << endl;
        return 1;
    }

    int n;
    entrada >> n;
    vector<vector<int>> matrizPlazas_Costes(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            entrada >> matrizPlazas_Costes[i][j];

    entrada.close();

    pair<int,vector<pair<int,int>>> resultadoKruskal = kruskal(matrizPlazas_Costes);

    cout << "Coste total: " << resultadoKruskal.first << endl;
    cout << "Conjunto de calles seleccionadas: " << vectorPair_toString(resultadoKruskal.second) << endl;

    return 0;
}