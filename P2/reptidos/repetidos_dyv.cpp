#include <iostream>
#include <vector>

#include <chrono>
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros

using namespace std;

// ---------------------------------------------------------------------
// Función que realiza el algoritmo de unificar dos vectores
void unir(vector<int> &vec, vector<int> &vDcha, vector<int> vIzq){

    vec = vIzq;
    for(int i = 0; i < vDcha.size();i++)
        vec.push_back(vDcha[i]);

    for (int i = 0; i < vec.size(); i++){
        int marca = i;
        marca++;
        for (int j = marca; j < vec.size(); j++){
            if(vec[i] == vec[j]){
                for (int x = j; x<(vec.size()-1); x++){
                    vec[x] = vec[x+1];
                }
                vec.resize(vec.size()-1);
            }
        }
    }
}

// Función que realiza el algoritmo de eliminar repetidos
void repetidos_dyv(vector<int> &vec){

    if(vec.size()==2 || vec.size()==1){
        if(vec.size()==2){
            if(vec[0] == vec[1]){
                vec.resize(vec.size()-1);
                return;
            }
            else{
                return;
            }
        }
    }

    else{
        int mitad = vec.size()/2;
        vector<int> vDcha;
        vector<int> vIzq;

        for (int i = 0; i<mitad; i++){
            vIzq.push_back(vec[i]);
        }
        for (int i = (mitad+1); i<vec.size(); i++){
            vDcha.push_back(vec[i]);
        }

        if(vDcha.size()>2)
            repetidos_dyv(vDcha);
        if(vIzq.size()>2)
            repetidos_dyv(vIzq);

        unir(vec,vIzq,vDcha);
    }
}

int main(int argc, char **argv){
    /*prueba
        vector<int> datos= {1,1,2,2,1,5,1,2,3,4,5,6,1,4,2,5,3,2,6,7,5,2,5,1};
        repetidos_dyv(datos);

        for (int i = 0 ; i < datos.size(); i++){
            cout << datos[i]<< " ";
        }
        cout << "" << endl;
    */

    if(argc < 4){
        printf("Faltan argumentos. Ejemplo: ./repetidos_dyv <fichero_salida> 12345 tam_ejecucion_1 tam_ejecucion_2 ...\n");
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

            vector<int> datos;
            datos.clear();
            unsigned long int tam = atoi(argv[num_ejecucion]);

            // --------------------------------------------------------------------
            // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int i= 0; i<tam; i++)
                datos.push_back(rand()%tam);

            t0= std::chrono::high_resolution_clock::now();
            repetidos_dyv(datos);
            tf= std::chrono::high_resolution_clock::now();
            
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para vectores de  " << tam << " elementos." <<endl;
            fsalida<<tam<<" "<<tejecucion<<"\n";
            
            num_ejecucion ++;
        }

        fsalida.close();
    }
}