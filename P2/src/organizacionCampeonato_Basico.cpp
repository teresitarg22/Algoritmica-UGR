#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <math.h>
#include <fstream> // Para usar ficheros

using namespace std;


bool organizacionCampeonato(vector< vector<int> > & calendario, int jornada, int equipo, set<int> &partidosRestantesJornada){
    
    set<int> partidosRestantesEquipoActual ;
    bool res = false, libreEncontrado = false;

    partidosRestantesEquipoActual = partidosRestantesJornada;
    partidosRestantesEquipoActual.erase(equipo);

    //Eliminamos los que ya hemos jugado
    for(int i = jornada-1; i >= 0 ; i --){
        partidosRestantesEquipoActual.erase(calendario[i][equipo]);
    }
    

    if(partidosRestantesEquipoActual.size() == 0){
        return  res;
    }
    else{
        
        for(auto it = partidosRestantesEquipoActual.begin(); it != partidosRestantesEquipoActual.end() && !res; it++){
            
            //Asignamos  el partido de forma temporal
            calendario[jornada][equipo] = *it;
            calendario[jornada][*it] = equipo;

            partidosRestantesJornada.erase(*it);
            partidosRestantesJornada.erase(equipo);

            res = true;

            libreEncontrado = false;
            for(long unsigned int j = equipo+1; j < calendario[jornada].size() && !libreEncontrado; j++){
                if(calendario[jornada][j] == -1){
                    res = organizacionCampeonato(calendario, jornada, j, partidosRestantesJornada);
                    libreEncontrado = true;
                }
            }

            if(!res){
                partidosRestantesJornada.insert(*it);
                partidosRestantesJornada.insert(equipo);
                calendario[jornada][equipo] = -1;
                calendario[jornada][*it] = -1;
            }            
        }

    }

    return res;
}


int main (int argc, char **argv){

    if(argc < 3){
        printf("Faltan argumentos. Ejemplo: ./organizacionCampamento_Basico salida.txt exponente_1 exponente_2 ... \n");
        return(1);
    }else{
        int equipos;
        set<int> partidosrestantesJornada;
        vector< vector<int>> calendario;
        chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
        ofstream fsalida;

        unsigned long tejecucion;

        fsalida.open(argv[1]);
        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }
           
        for(int i = 2; i < argc; i++){
            equipos = atoi(argv[i]);

            if(equipos == 0 || equipos > 29){
                printf("El exponente tiene que ser mayor que 0 y menor que 30\n");
                return 1;
            }
            
            equipos = pow(2,equipos);
            calendario = vector<vector<int>>(equipos-1, vector<int> (equipos,-1));

            t0= std::chrono::high_resolution_clock::now();
            
            for(long unsigned int i = 0; i< calendario.size(); i++){
                partidosrestantesJornada.clear();
                for(long unsigned int j = 0; j < calendario[i].size(); j++){
                    partidosrestantesJornada.insert(j);
                }

                organizacionCampeonato(calendario,i,0,partidosrestantesJornada);
                
            }

            tf= std::chrono::high_resolution_clock::now();

            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            cout << "Tiempo de ejecución: " << tejecucion << "(us) para competición con  " << equipos << " equipos." <<endl;
            fsalida<<equipos<<" "<<tejecucion<<"\n";

            //DESCOMENTAR  ABAJO PARA VER RESULTADOS/////////////////////////////////////////

        

            // for(unsigned long int i = 0; i < calendario.size(); i++){
            //     for( unsigned long int j = 0; j < calendario[i].size(); j++){
            //         if (calendario[i][j] < 10 && calendario[i][j] >= 0)
            //             cout << calendario [i][j] << "  ";
            //         else
            //              cout << calendario [i][j] << " ";
            //     }

            //     cout << endl;
            // }
        }

        fsalida.close();
    }
    
    
}

