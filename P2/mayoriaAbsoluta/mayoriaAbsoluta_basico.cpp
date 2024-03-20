#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// ---------------------------------------------------------------------
// Función que determina si hay algún candidato con mayoría absoluta
// ---------------------------------------------------------------------
void mayoriaAbsoluta(const vector<int> urna){
    // 1. Creación de un unordered_map<int,int> recuento (un mapa hash)
    //    La clave será el número del candidato y el valor será el número.
    unordered_map<int, int> recuento;

    // 2. Recorremos la urna de votos y actualizamos el recuento de votos:
    for (int i = 0; i < urna.size(); ++i) {
        int voto = urna[i]; // Inicializamos voto con el voto actual.

        if (recuento.find(voto) != recuento.end()) {
            // Si el candidato SÍ está registrado en el mapa de recuento...
            recuento[voto]++;
        } else {
            // Si el candidato NO está registrado en el mapa de recuento...
            recuento[voto] = 1;
        }
    }

    int n = recuento.size(); // Donde n es el número de candidatos
    
    // 3. Comprobamos si hay algún candidato con mayoría absoluta:
    bool mayoriaAbsoluta = false;
    int candidatoConMayoria;
    int votosNecesarios = n/2 + 1;

    auto it = recuento.begin(); // Iterador inicializado en el primer elemento del mapa

    while (it != recuento.end()) {
        // Si el candidato tiene más votos que los necesarios para la mayoría absoluta...
        if (it->second > votosNecesarios) {
            mayoriaAbsoluta = true;
            candidatoConMayoria = it->first;
            break;
        }
        ++it;
    }

    // 4. Imprimimos el resultado:
    cout << "-------------------------------" << endl;
    cout << "RESULTADO" << endl;
    cout << "-------------------------------" << endl;

    if (mayoriaAbsoluta) {
        cout << "El candidato con mayoría absoluta es: " << candidatoConMayoria << endl;
        cout << "Votos obtenidos: " << recuento[candidatoConMayoria] << endl;
    } else {
        cout << "No hay ningún candidato con mayoría absoluta." << endl;
    }
}

// ---------------------------------------------------------------------

int main() {



}