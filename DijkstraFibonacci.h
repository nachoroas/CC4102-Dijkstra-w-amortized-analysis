#include "Basic_definitionsFibonacci.h"

using namespace std;

pair<vector<double>,vector<int>> dijkstraFibonacci(vector<vector<pair<int,double>>> grafo, int raiz){
    
    vector<double> distancias(grafo.size(), INT_MAX);
    vector<int> previos(grafo.size(), INT_MIN);

    distancias[raiz] = 0;
    previos[raiz] = -1;

    QFibonacci cola = QFibonacci(grafo.size());

    cola.insert(raiz, 0);
    
    for (int i = 0; i < grafo.size(); i++){
        if (i != raiz){
            cola.insert(i, INT_MAX);
        }
    }

    while(!cola.empty()){

        //cout << cola.n << endl;

        FibonacciNode* x= cola.extractMin();

        for(auto [nodo_vecino, distancia_vecino]: grafo[x->indice]){

            if(distancias[nodo_vecino] > distancias[x->indice] + distancia_vecino){
                distancias[nodo_vecino] = distancias[x->indice] + distancia_vecino;
                previos[nodo_vecino] = x->indice;
                cola.decreaseKey(nodo_vecino, distancias[x->indice]+distancia_vecino);
            }
        }

        delete x;
    }

    return {distancias,previos};
    
}
