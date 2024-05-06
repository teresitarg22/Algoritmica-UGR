#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

// Función para leer la matriz desde un archivo
int leerMatrizDesdeArchivo(const string& nombreArchivo, vector<vector<int>> & afinidades) {
    ifstream archivo(nombreArchivo);  // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return 0;
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
   
    return numeroFilas;

}


int crearMesa(const vector<vector<int>> & matrizAfinidad, vector<vector<int>> &adyacentes){
    set<int> candidatos;

    for(long unsigned int i = 0; i < adyacentes.size(); i++){
        candidatos.insert(i);
    }

    int afinidadTotal = 0; 

    

    while(candidatos.size() > 0){

        int invitado = *candidatos.begin();
        candidatos.erase(invitado);
        

        // for(auto it = candidatos.begin(); it != candidatos.end(); it++){
        //     cout << *it ;
        // }

        // cout <<endl;
	
        for (int m = 0; m < 2; m++){
            bool cambio1 = false;
        bool cambio2 = false;
            int mayorAfinidad = 0; 
            int candidato = -1;
            
            for(auto j = candidatos.begin();  j != candidatos.end(); j++){
                int afinidad = matrizAfinidad[invitado][*j] + matrizAfinidad[*j][invitado];

                if ( afinidad > mayorAfinidad && adyacentes[invitado][0] != *j){
                    mayorAfinidad = afinidad;
                    candidato = *j;
                }
               
            }
        
            for (int x = 0; x < 2; x++){
                
                if(adyacentes[invitado][x] == -1 && cambio1 == false){
                        adyacentes[invitado][x] = candidato;
                    cambio1 = true;
                }
                
                if(adyacentes[candidato][x] == -1 && cambio2 == false){
                        adyacentes[candidato][x] = invitado;
                    
                    cambio2 = true;
                    if(x == 1){
                    
                        candidatos.erase(candidato);
                        
                    }
                }
                
            }
                afinidadTotal += mayorAfinidad;
                
        }

        // for(int i = 0; i < adyacentes.size(); i++){
        //     for(int j = 0; j < adyacentes[0].size(); j++){
        //         cout << adyacentes[i][j] << " ";
        //     }
        //     cout <<endl;
        // }
        // cout <<endl;
    }
    
    return afinidadTotal;
}

int crearMesaBackTracking(const vector<vector<int>> & matrizAfinidad, vector<int> &adyacentes, set<int>&disponibles, vector<int> &adyacentesTemporal,int afinidad, int &afinidadMaxima){
    
    //Ultimo invitado
    if(disponibles.size() == 2){

        auto primero = adyacentesTemporal.begin();
        //Escogemos la primera persona disponible
        auto invitado = disponibles.begin();
        auto adyacente = invitado++;
        //Asignamos al invitadoseleccionado su adyacente y viceversa
        adyacentesTemporal[*invitado] = *adyacente;
        adyacentesTemporal[*adyacente] = *invitado;

        afinidad += matrizAfinidad[*invitado][*adyacente]+ matrizAfinidad[*adyacente][*invitado];
        //como la mesa es redonda le sumamos el primer elemento al ultimo escogido ya que este tambien presenta afinidad con el que se siente a su lado
        afinidad += matrizAfinidad[*primero][*invitado]+ matrizAfinidad[*invitado][*primero];
        if (afinidad > afinidadMaxima){
            afinidadMaxima = afinidad;
            adyacentes = adyacentesTemporal;
        }

    }else{

        set<int> disponiblesDespuesDeElegir = disponibles;
        int afinidadHastaElMomento = afinidad;
        for( auto i =  disponibles.begin(); i != disponibles.end(); i++){
            //cout << "paso por aqui" <<endl;
            disponiblesDespuesDeElegir.erase(*i);
            
            
            for(auto j = disponibles.begin(); j != disponibles.end(); j++){

                if(i!=j){
                    adyacentesTemporal[*i] = *j;
                    adyacentesTemporal[*j] = *i;

                    afinidad += matrizAfinidad[*i][*j]+ matrizAfinidad[*j][*i];

                    
                    disponiblesDespuesDeElegir.erase(*j);


                    crearMesaBackTracking(matrizAfinidad, adyacentes,disponiblesDespuesDeElegir,adyacentesTemporal, afinidad, afinidadMaxima);
                    disponiblesDespuesDeElegir.insert(*j);
                }
                afinidad = afinidadHastaElMomento;
                
            }
            

            disponiblesDespuesDeElegir.insert(*i);
            
        }

    }

    
    return afinidad;

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
    vector<int> adyacentesTemporal (afinidades.size(),-1);
    set<int> disponibles;
    int afinidad = 0;

    for(long unsigned int i = 0; i < afinidades.size(); i ++){
        disponibles.insert(i);
    }

    int afinidadTotal =0;
    crearMesaBackTracking(afinidades, adyacentes, disponibles,adyacentesTemporal, afinidad, afinidadTotal);

    // // Mostrar la matriz en la consola
   
    // for (long unsigned int i = 0; i < afinidades.size(); ++i) {
    //     for (long unsigned int j = 0; j < afinidades[i].size(); ++j) {
    //         cout << afinidades[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //Mostrar la mesa completa

    for(long unsigned int i = 0; i < adyacentes.size(); i++){
        cout << adyacentes[i] << " ";
    }
     cout << adyacentes[0] << " ";

    cout << endl << "Afinidad total: " << afinidadTotal <<endl;

    return 0;
}
