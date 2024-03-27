#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

using namespace std;

// -----------------------------------------------------------------------
// Función para contar los votos de un candidato concreto de la urna
// -----------------------------------------------------------------------
int contarVotos(const vector<int> &urna, int inicio, int fin, int candidato){
    int votos = 0;

    for(int i = inicio; i <= fin; i++){
        if(urna[i] == candidato){
            votos++;
        }
    }

    return votos;
}

// -----------------------------------------------------------------------
// Función para encontrar la mayoría absoluta aplicando divide y vencerás
// -----------------------------------------------------------------------
void mayoriaAbsoluta(const vector<int> &urna, int inicio, int fin, int &candidato, int &votos){
    // Caso base: Si la urna tiene un solo elemento, ese elemento es el candidato con mayoría absoluta.
    if(inicio == fin){
        candidato = urna[inicio];
        votos = 1;
        return;
    }
    
    // 1. Dividimos la urna en dos partes
    int mitad = (inicio + fin) / 2;
    int candidatoIzq = 0, votosIzq = 0;
    int candidatoDer = 0, votosDer = 0;

    // 2. Llamamos recursivamente a la función para cada mitad
    mayoriaAbsoluta(urna, inicio, mitad, candidatoIzq, votosIzq);
    mayoriaAbsoluta(urna, mitad + 1, fin, candidatoDer, votosDer);

    // 3. Combinamos los resultados
    // Caso 1: Si los candidatos de ambas mitades son iguales, el candidato con mayoría absoluta es el mismo.
    if(candidatoIzq == candidatoDer){
        candidato = candidatoIzq;
        votos = votosIzq + votosDer;
    }
    // Caso 2: Si los candidatos de ambas mitades son distintos, comprobamos cuál tiene más votos.
    else{
        int votosCandidatoIzq = contarVotos(urna, inicio, fin, candidatoIzq);
        int votosCandidatoDer = contarVotos(urna, inicio, fin, candidatoDer);

        if(votosCandidatoIzq > votosCandidatoDer){
            candidato = candidatoIzq;
            votos = votosCandidatoIzq;
        }
        else{
            candidato = candidatoDer;
            votos = votosCandidatoDer;
        }
    }
}

// ---------------------------------------------------------------------
// Función que determina si hay algún candidato con mayoría absoluta
// ---------------------------------------------------------------------
int resultadosMayoriaAbsoluta(const vector<int> &urna){
    int candidato, votos;
    int k = urna.size(); // Donde k es el número de votos totales.
    mayoriaAbsoluta(urna, 0, k-1, candidato, votos);

    cout << "-------------------------------" << endl;
    cout << "Resultados de las elecciones:" << endl;
    cout << "-------------------------------" << endl;

    if(votos > k/2 + 1){
        cout << "El candidato con mayoría absoluta es: " << candidato << " con " << votos << " votos." << endl << endl;
        return candidato;
    }
    else{
        cout << "No hay candidato con mayoría absoluta." << endl << endl;
        return -1;
    }
}

// ---------------------------------------------------------------------

int main(int argc, char **argv) {

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./mayoriaAbsoluta_DyV <fichero_salida> 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
        return(1);
    }else{
        unsigned long int semilla;
        int num_ejecucion = 3; // Los tres primeros elementos son el nombre del ejecutable, el nombre del fichero de salida y la semilla de rand
        semilla = atoi(argv[2]);
        srand(semilla);

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
        unsigned long tejecucion;

        ofstream fsalida;

        // ----------------------------
        // Abrimos fichero de salida
        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }

        while (num_ejecucion  < argc){
            vector<int> urna;
            urna.clear();

            // --------------------------------------------------------------------
            // Generamos vector aleatorio de prueba para los votos (urna)
            int tam = atoi(argv[num_ejecucion]);
            int rangoCandidatos = 0;

            if(tam < 10000){
                rangoCandidatos = tam/10 + 1;
            }
            else{
                rangoCandidatos = 20 + 1;
            }

            for (int i = 0; i < tam; ++i) {
                int voto = rand() % rangoCandidatos; 
                urna.push_back(voto);
            }

            t0= std::chrono::high_resolution_clock::now();
            resultadosMayoriaAbsoluta(urna);
            tf= std::chrono::high_resolution_clock::now();
            
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida << tam << " " << tejecucion << "\n";
            
            num_ejecucion++;
        }

        fsalida.close();
    }

}