#include <iostream>
#include <vector>

#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

using namespace std;

// ---------------------------------------------------------------------
// Función que realiza el algoritmo de ordenamiento Counting Sort
void countingSort(vector<int> &elementos){
    // ------------------------------------------
    // Imprimimos por terminal el vector inicial.
    printf("\n-------------------------------------");
    printf("\nEl vector inicial es: \n");

    for(int i = 0; i < elementos.size(); i++) {
        if(i == elementos.size()-1)
            cout << elementos[i] << endl;
        else    
            cout << elementos[i] << ", ";
    }

    // 1. Averiguar el intervalo de los datos --> máximo y mínimo.
    int min = elementos[0]; // inicializamos el elemento mínimo.
    int max = elementos[0]; // inicializamos el elemento máximo.

    // Buscamos el elemento más pequeño y el más grande recorriendo el vector.
    for(int i = 1; i < elementos.size(); i++){
        if(elementos[i] < min)
            min = elementos[i];
        else if(elementos[i] > max)
            max = elementos[i];
    }

    // 2. Creamos el vector de números enteros: [minimo, maximo].
    // 3. A cada elemento se le da el elemento 0 (0 apariciones).
    vector<int> aux;

    for(int i = 0; i < (max-min+1); i++){
        aux.push_back(0);
    }

    // 4. Recorremos los elementos a ordenar y contamos el num de apariciones (frecuencia).
    //    Almacenamos la frecuencia en el vector auxiliar.
    for(int i = 0; i < elementos.size(); i++) {
        int elemento = elementos[i];
        aux[elemento - min]++;
    }
    
    // 5. Reconstruimos la lista ordenada utilizando el vector auxiliar.
    int indice = 0;

    for(int i = min; i <= max; i++) {
        while(aux[i - min] > 0) {
            elementos[indice++] = i;
            aux[i - min]--;
        }
    }

    // ----------------------------------------
    // Imprimimos por terminal el vector final.
    printf("\nEl vector una vez ordenado es: \n");

    for(int i = 0; i < elementos.size(); i++) {
        if(i == elementos.size()-1)
            cout << elementos[i] << endl << endl;
        else    
            cout << elementos[i] << ", ";
    }
}

// ----------------------------------------------

int main(int argc, char **argv){

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./countingSort <fichero_salida> 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
        return(1);
    }else{
        unsigned long int semilla;
        int num_ejecucion = 3; //Los tres primeros elementos son el nombre del ejecutable, el nombre del fichero de salida y la semilla de rand
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

            vector<int> elementos;
            unsigned long int tam = atoi(argv[num_ejecucion]);

            // --------------------------------------------------------------------
            // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int i= 0; i<tam; i++)
                elementos.push_back(rand()%tam);

            t0= std::chrono::high_resolution_clock::now();
            countingSort(elementos);
            tf= std::chrono::high_resolution_clock::now();
            
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida<<tam<<" "<<tejecucion<<"\n";
            
            num_ejecucion ++;
        }

        fsalida.close();
    }
}