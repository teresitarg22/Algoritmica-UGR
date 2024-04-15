#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

// Función para leer la matriz desde un archivo
void leerMatrizDesdeArchivo(const string& nombreArchivo, vector<vector<int>> & afinidades) {
    ifstream archivo(nombreArchivo);  // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    int numeroFilas;
    archivo >> numeroFilas;  // Leer el número de filas desde el archivo

    if (numeroFilas % 2 != 0) {
        cout << "El número de filas debe ser par." << endl;
        archivo.close();
        return;
    }

     afinidades.resize(numeroFilas, vector<int>(numeroFilas, -1));  // Crear la matriz

    // Leer los valores de la matriz desde el archivo
    for (int i = 0; i < numeroFilas; ++i) {

        for (int j = 0; j < numeroFilas; ++j) {
            archivo >> afinidades[i][j];
        }
    }
    

    archivo.close();  // Cerrar el archivo

}


int crearParejas(const vector<vector<int>> & matrizAfinidad, vector<int> &parejas){
    set<int> candidatos;

    for(long unsigned int i = 0; i < parejas.size(); i++){
        candidatos.insert(i);
    }

    int afinidadTotal = 0; 

    while(candidatos.size() > 0){

        int alumno = *candidatos.begin();
        candidatos.erase(alumno);

        int mayorAfinidad = 0; 
        int pareja = -1;

        for(auto j = candidatos.begin();  j != candidatos.end(); j++){
            int afinidad = matrizAfinidad[alumno][*j] * matrizAfinidad[*j][alumno];

            if ( afinidad > mayorAfinidad){
                mayorAfinidad = afinidad;
                pareja = *j;
            }
        }

        parejas[alumno] = pareja;
        parejas[pareja] = alumno;

        afinidadTotal += mayorAfinidad;
        candidatos.erase(pareja);

    }

    return afinidadTotal;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " afinidades.txt" << endl;
        return 1;  // Salir del programa con un código de error
    }

    string nombreArchivo = argv[1];

    vector<vector<int>> afinidades;
    leerMatrizDesdeArchivo(nombreArchivo, afinidades);

    vector<int> parejas (afinidades.size(),-1);

    int afinidadTotal = crearParejas(afinidades,parejas);

    // // Mostrar la matriz en la consola
   
    // for (long unsigned int i = 0; i < afinidades.size(); ++i) {
    //     for (long unsigned int j = 0; j < afinidades[i].size(); ++j) {
    //         cout << afinidades[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //Mostrar las parejas elegidas

    for(long unsigned int i = 0; i < parejas.size(); i++){
        cout << parejas[i] << " ";
    }

    cout << endl << "Afinidad total: " << afinidadTotal <<endl;

    return 0;
}
