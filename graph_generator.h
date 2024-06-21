#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <iostream>


using namespace std;

using namespace std::chrono;

// Nota: El grafo generado es conexo aunque la cantidad de vertices supere e
vector<vector<pair<int,double>>> generadorGrafo(int v, int e){

    // Semilla para el rng

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    srand(seed);

    std::mt19937 gen(seed);

    // Generador de doubles para los pesos

    uniform_real_distribution<double> peso(0.000001,1);

    // Declaración de de generador de enteros para los primeros v-1 arcos

    uniform_int_distribution<int> nodos;

    int numero_aristas = 0;

    // Vector que indica si dos nodos estan conectados, su uso es para no repetir uno de los v-1 primeros arcos insertados

    vector<vector<bool>> connected(v, vector(v,false));

    // Vector con todos los pares posibles de arcos
    // De la forma {i,j}, con i < j; no existe {j, i} en el vector

    vector<pair<int,int>> aristas_posibles(v*(v-1)/2);

    // Llenamos el vector de aristas posibles

    int current = 0;

    for(int i = 0; i < v; i++){
        for(int j = i+1; j < v; j++){
            aristas_posibles[current] = {i,j};
            current++;
        }
    }

    //Inicializamos el grafo a entregar

    vector<vector<pair<int,double>>> lista(v);

    int a = 0;

    // Primeras v-1 aristas

    for(int i = 1; i < v; i++){

        a += 1;

        // Cambiamos el generador al rango nodo 0 y el nodo i-1
        
        nodos = uniform_int_distribution<int>(0, i-1);

        // Generamos el nodo a conectar y insertamos el arco al grafo, en los dos sentidos al ser bidireccional
        
        int nodo = nodos(gen);

        connected[nodo][i] = true;
        connected[i][nodo] = true;

        double weight = peso(gen);

        lista[i].push_back({nodo,weight});
        lista[nodo].push_back({i,weight});

        numero_aristas ++;
    }

    // Llenamos con aristas hasta llegar al numero pedido o no podemos agregar mas 

    while((numero_aristas < (v*(v-1))/2 && numero_aristas < e)){
        
        // Elegimos una arista

        int i = rand() % aristas_posibles.size();

        auto[x,y] = aristas_posibles[i];

        // Si esta conectada la borramos del vector y repetimos el while

        if(connected[x][y] || x == y){

            swap(aristas_posibles[i], aristas_posibles[aristas_posibles.size()-1]);
            aristas_posibles.pop_back();
            continue;
        }

        // Generamos peso y agregamos el arco al grafo

        double weight = peso(gen);

        lista[x].push_back({y,weight});
        lista[y].push_back({x,weight});

        connected[x][y] = true;
        connected[y][x] = true;

        numero_aristas ++;

        // Eliminamos la arista insertada

        swap(aristas_posibles[i], aristas_posibles[aristas_posibles.size()-1]);
        aristas_posibles.pop_back();


    }

    return lista;
}





