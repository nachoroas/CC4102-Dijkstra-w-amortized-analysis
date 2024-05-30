#include "Basic_definitionsFibonacci.h"

using namespace std;

pair<vector<double>,vector<int>> dijkstraFibonacci(vector<vector<pair<int,int>>> grafo, int raiz){
    
    vector<double> distancias(grafo.size(), INT_MAX);
    vector<int> previos(grafo.size(), INT_MIN);

    distancias[raiz] = 0;
    previos[raiz] = -1;

    QFibonacci cola = QFibonacci(grafo.size());

    cola.insert(0, raiz);
    
    for (int i = 0; i < grafo.size(); i++){
        if (i != raiz){
            cola.insert(INT_MAX, i);
        }
    }

    while(!cola.empty()){
        FibonacciNodo* x= cola.extractMin();

        for(auto [distancia_vecino, nodo_vecino]: grafo[x->nodeIndex]){

            if(distancias[nodo_vecino] > distancias[x->nodeIndex] + distancia_vecino){
                distancias[nodo_vecino] = distancias[x->nodeIndex] + distancia_vecino;
                previos[nodo_vecino] = x->nodeIndex;
                cola.decreaseKey(nodo_vecino, distancias[x->nodeIndex]+distancia_vecino);
            }
        }
    }

    return {distancias,previos};
    
}
