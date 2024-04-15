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

     afinidades.resize(numeroFilas, vector<int>(numeroFilas, -1));  // Crear la matriz

    // Leer los valores de la matriz desde el archivo
    for (int i = 0; i < numeroFilas; ++i) {

        for (int j = 0; j < numeroFilas; ++j) {
            archivo >> afinidades[i][j];
        }
    }
    
    archivo.close();  // Cerrar el archivo

}


int crearMesa(const vector<vector<int>> & matrizAfinidad, vector<int> &adyacentes){
    set<int> candidatos;

    for(long unsigned int i = 0; i < adyacentes.size(); i++){
        candidatos.insert(i);
    }

    int afinidadTotal = 0; 

    while(candidatos.size() > 0){

        int alumno = *candidatos.begin();
        candidatos.erase(alumno);
	bool cambio1 = false;
	bool cambio2 = false;
	
	for (int m = 0; m < 2; m++){
        int mayorAfinidad = 0; 
        int candidato = -1;

        for(auto j = candidatos.begin();  j != candidatos.end(); j++){
            int afinidad = matrizAfinidad[alumno][*j] + matrizAfinidad[*j][alumno];

            if ( afinidad > mayorAfinidad){
                mayorAfinidad = afinidad;
                candidato = *j;
            }
        }
	
	for (int m = 0; m < 2; m++){
		if(P[i][x] == 0 && cambio1 == false){
        		parejas[alumno] = candidato;
			cambio1 = true;
		}

		if(P[j][x] == 0 && cambio2 == false){
        		parejas[candidato] = alumno;
			cambio2 = true;
			if(x == 1)
				candidatos.erase(candidato);
		}
	}
        afinidadTotal += mayorAfinidad;
        
	}

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

    vector<int> adyacentes (afinidades.size(),-1);

    int afinidadTotal = crearMesa(afinidades,adyacentes);

    // // Mostrar la matriz en la consola
   
    // for (long unsigned int i = 0; i < afinidades.size(); ++i) {
    //     for (long unsigned int j = 0; j < afinidades[i].size(); ++j) {
    //         cout << afinidades[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //Mostrar las personas que se encuentran adyacentes a cada candidato

    for(long unsigned int i = 0; i < adyacentes.size(); i++){
	for(long unsigned int j = 0; i < 2; j++){
        	cout << adyacentes[i][j] << " ";
	}
    }

    cout << endl << "Afinidad total: " << afinidadTotal <<endl;

    return 0;
}
