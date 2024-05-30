#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <iostream>


using namespace std;

using namespace std::chrono;


vector<vector<pair<int,double>>> generadorGrafo(int v, int e){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 gen(seed);

    srand(seed);

    uniform_real_distribution<double> dis(0.000001,1);

    int numero_aristas = 0;

    // Primeras v-1 aristas

    vector<vector<bool>> connected(v, vector(v,false));

    vector<pair<int,int>> aristas_posibles(v*(v-1)/2);

    int current = 0;

    for(int i = 0; i < v; i++){
        for(int j = i+1; j < v; j++){
            aristas_posibles[current] = {i,j};
            current++;
        }
    }

    vector<vector<pair<int,double>>> lista(v);

    for(int i = 1; i <= v; i++){

        
        int nodo = rand() % i;
        
        if(nodo != 0){
            nodo = nodo-1;
        }

        connected[nodo][i-1] = true;
        connected[i-1][nodo] = true;

        double weight = dis(gen);

        lista[i-1].push_back({nodo,weight});
        lista[nodo].push_back({i-1,weight});

        numero_aristas ++;
    }

    while((numero_aristas < (v*(v-1))/2 && numero_aristas < e)){


        int i = rand() % aristas_posibles.size();

        auto[x,y] = aristas_posibles[i];

        if(connected[x][y] || x == y){

            swap(aristas_posibles[i], aristas_posibles[aristas_posibles.size()-1]);
            aristas_posibles.pop_back();
            continue;
        }

        double weight = dis(gen);

        lista[x].push_back({y,weight});
        lista[y].push_back({x,weight});

        connected[x][y] = true;
        connected[y][x] = true;

        numero_aristas ++;


    }

    return lista;
}





