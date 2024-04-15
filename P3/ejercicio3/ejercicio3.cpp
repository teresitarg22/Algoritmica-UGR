#include <iostream>
#include <vector>

using namespace std;

struct Gasolinera {
    int kilometro;
};

vector<Gasolinera> Gasolineras(int Origen, int Destino, int k, const vector<Gasolinera>& gasolineras) {
    vector<Gasolinera> paradas;
    int gasolina_restante = k;
    int posicion_autobus = Origen;

    for (int i = 0; i < gasolineras.size(); ++i) {
        int distancia_hasta_siguiente = gasolineras[i].kilometro - posicion_autobus;

        // Verificar si es necesario repostar antes de llegar a la siguiente gasolinera
        if (distancia_hasta_siguiente > gasolina_restante) {// Si no se puede llegar a la siguiente gasolinera, se agrega la última como parada
            paradas.push_back(gasolineras[i - 1]);
            gasolina_restante = k;
        } else {
            gasolina_restante -= distancia_hasta_siguiente;
            posicion_autobus = gasolineras[i].kilometro;
        }

        // Verificar si es necesario repostar para llegar al destino
        int distancia_hasta_destino = Destino - posicion_autobus;
        if (distancia_hasta_destino <= gasolina_restante) {
            // Si es posible llegar al destino con la gasolina restante, no es necesario repostar más
            break;
        }
    }

    return paradas;
}

int main() {
    vector<Gasolinera> gasolineras = {
        {20},
        {40},
        {60},
        {80},
        {95}
    };

    vector<Gasolinera> resultado = Gasolineras(0, 100, 30, gasolineras);
    if (!resultado.empty()) {
        cout << "Gasolineras en las que debe repostar el conductor:" << endl;
        for (auto it = resultado.begin(); it != resultado.end(); ++it)
            cout << (*it).kilometro << " km" << endl;
        } else {
        cout << "No es posible llegar al destino" << endl;
    }

    return 0;
}
