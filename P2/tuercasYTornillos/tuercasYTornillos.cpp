#include <iostream>
// #include <unordered_map>
#include <vector>
#include <string>

#include <chrono>
// #include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

#include <random>   // Necesario para std::shuffle
#include <algorithm> // Necesario para std::shuffle

using namespace std;


// ---------------------------------------------------------------------
// Funciones que asigna a cada tornillo su tuerca correspondiente
// ---------------------------------------------------------------------

// FUERZA BRUTA
void tuercasYTornillos_FB(const vector<int> tornillos, vector<int> & tuercas) {
    int aux;

    for(int i=0; i<tornillos.size(); i++)
        for(int j=i; j<tuercas.size(); j++) 
            if(tornillos[i] == tuercas[j] and i != j){
                aux = tuercas[i];
                tuercas[i] = tuercas[j];
                tuercas[j] = aux;
            }
}

// DIVIDE Y VENCERÁS
void tuercasYTornillos_DyV(vector<int> & tornillos, vector<int> & tuercas)  {
    int tornillo_elegido = tornillos[0];
    int tuerca_pareja;

    vector<int> tornillos_menores, tornillos_mayores, tuercas_menores, tuercas_mayores;


    for (int i=0; i<tuercas.size(); i++)
        if(tuercas[i] < tornillo_elegido)
            tuercas_menores.push_back(tuercas[i]);

        else if(tuercas[i] > tornillo_elegido)
            tuercas_mayores.push_back(tuercas[i]);

        else
            tuerca_pareja = tuercas[i];

    for (int i=1; i<tornillos.size(); i++)
        if(tornillos[i] < tuerca_pareja)
            tornillos_menores.push_back(tornillos[i]);

        else if(tornillos[i] > tuerca_pareja)
            tornillos_mayores.push_back(tornillos[i]);

    tornillos.clear();
    tuercas.clear();

    if(tornillos_menores.size() > 1) {
        tuercasYTornillos_DyV(tornillos_menores, tuercas_menores);
        for (int i=0; i<tornillos_menores.size(); i++) {
            tornillos.push_back(tornillos_menores[i]);
            tuercas.push_back(tuercas_menores[i]);
        }
    }
    else if(tornillos_menores.size() == 1) {
        tornillos.push_back(tornillos_menores[0]);
        tuercas.push_back(tuercas_menores[0]);
    }

    tornillos.push_back(tornillo_elegido);
    tuercas.push_back(tuerca_pareja);

    if(tornillos_mayores.size() > 1) {
        tuercasYTornillos_DyV(tornillos_mayores, tuercas_mayores);
        for (int i=0; i<tornillos_mayores.size(); i++) {
            tornillos.push_back(tornillos_mayores[i]);
            tuercas.push_back(tuercas_mayores[i]);
        }
    }
    else if(tornillos_mayores.size() == 1) {
        tornillos.push_back(tornillos_mayores[0]);
        tuercas.push_back(tuercas_mayores[0]);
    }
}


// ---------------------------------------------------------------------

int main(int argc, char **argv) {

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./mayoriaAbsoluta_basico <fichero_salida> 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
        return(1);
    }else{
        int num_ejecucion = 3; // Los tres primeros elementos son el nombre del ejecutable, el nombre del fichero de salida y la semilla de rand
        unsigned long int semilla = atoi(argv[2]);

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
        unsigned long tejecucionFB, tejecucionDyV;

        ofstream fsalida;

        // ----------------------------
        // Abrimos fichero de salida
        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }

        while (num_ejecucion  < argc){
            // Vectores de eneteros que simulan las cajas de tornillos y tuercas de distintos tamaños 
            vector<int> tornillos, tuercas;

            unsigned int tam = atoi(argv[num_ejecucion]);
           
            // --------------------------------------------------------------------
            
            // Generamos vector inicial ordenado de manera que los elementos de tornillos no se repitan y sean los mismos que los de tuercas
            for (int i= 0; i<tam; i++)
                tornillos.push_back(i);

            // Desordenamos los tornillos para simular la caja en la que están mezclados de manera randomizada con la semilla
            shuffle(tornillos.begin(), tornillos.end(), default_random_engine(semilla));

            // Los tamaños de las tuercas deben corresponder con cada uno de los tornillos
            tuercas = tornillos;

            // Desordenamos las tuercas para simular la caja en la que están mezclados de manera randomizada con la semilla
            shuffle(tuercas.begin(), tuercas.end(), default_random_engine(semilla));

            vector<int> tornillos_copia = tornillos;
            vector<int> tuercas_copia = tuercas;

            // --------------------------------------------------------------------

            t0= std::chrono::high_resolution_clock::now();
            tuercasYTornillos_FB(tornillos, tuercas);
            tf= std::chrono::high_resolution_clock::now();
            
            tejecucionFB= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

            t0= std::chrono::high_resolution_clock::now();
            tuercasYTornillos_DyV(tornillos_copia, tuercas_copia);
            tf= std::chrono::high_resolution_clock::now();
            
            tejecucionDyV= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();


            cout << "Tiempo FB: " << tejecucionFB << " DyV: " << tejecucionDyV << "(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida /*<< tam << " "*/ << tejecucionFB << "\t" << tejecucionDyV << "\n";

            num_ejecucion ++;
        }

        fsalida.close();
    }

}