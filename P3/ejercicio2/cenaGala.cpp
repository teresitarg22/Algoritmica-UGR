#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

// Función para leer la matriz desde un archivo
int leerMatrizDesdeArchivo(const string& nombreArchivo, vector<vector<int>> & afinidades) {
    cout <<"hola";
    ifstream archivo(nombreArchivo);  // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 0;
    }

    int numeroFilas;
    archivo >> numeroFilas;  // Leer el número de filas desde el archivo
    cout << numeroFilas;
     afinidades.resize(numeroFilas, vector<int>(numeroFilas, -1));  // Crear la matriz

    // Leer los valores de la matriz desde el archivo
    for (int i = 0; i < numeroFilas; ++i) {

        for (int j = 0; j < numeroFilas; ++j) {
            archivo >> afinidades[i][j];
        }
    }

    archivo.close();  // Cerrar el archivo
    cout << numeroFilas;
    return numeroFilas;

}


int crearMesa(const vector<vector<int>> & matrizAfinidad, vector<vector<int>> &adyacentes){
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
		if(adyacentes[alumno][m] == 0 && cambio1 == false){
        		adyacentes[alumno][m] = candidato;
			cambio1 = true;
		}

		if(adyacentes[candidato][m] == 0 && cambio2 == false){
        		adyacentes[candidato][m] = alumno;
			cambio2 = true;
			if(m == 1)
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
    cout << "soy subnormal";
    string nombreArchivo = argv[1];
    cout << "soy subnormal";
    vector<vector<int>> afinidades;
    int numeroFilas = leerMatrizDesdeArchivo(nombreArchivo, afinidades);

    ifstream archivo(nombreArchivo); 

    vector<vector<int>> adyacentes;
    cout << numeroFilas;
    adyacentes.resize(numeroFilas, vector<int>(2, 0));

    for( int i = 0; i < numeroFilas; i++){
	    for( int j = 0; j < 2; j++){
        	cout << adyacentes[i][j] << " ";
	    }
    }

    int afinidadTotal = crearMesa(afinidades,adyacentes);

    // // Mostrar la matriz en la consola
   
    // for (long unsigned int i = 0; i < afinidades.size(); ++i) {
    //     for (long unsigned int j = 0; j < afinidades[i].size(); ++j) {
    //         cout << afinidades[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //Mostrar las personas que se encuentran adyacentes a cada candidato

    for( int i = 0; i < 4; i++){
	for( int j = 0; j < 2; j++){
        	cout << adyacentes[i][j] << " ";
	}
    }

    cout << endl << "Afinidad total: " << afinidadTotal <<endl;

    return 0;
