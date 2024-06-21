#include <iostream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;


class QHeap{

    public:
        vector<pair<double,int>> Heap;
        vector<int> indices;

    void buildHeap(vector<pair<double,int>> input){
        Heap = input;
        indices = vector<int>(input.size());

        for(int i = Heap.size()/2 - 1; i >= 0 ;i--){
            heapify(i);
        }

        for(int i = 0; i < Heap.size();i++){
            this->indices[this->Heap[i].second] = i;  
        }
    }

    void heapify(int i){
        int smallest = i;
        int l = 2*i + 1;
        int r = 2*i +2;

        if(l < Heap.size() && Heap[l].first < Heap[smallest].first){

            smallest = l;
        }

        if(r < Heap.size() && Heap[r].first < Heap[smallest].first){

            smallest = r;
        }
        
        
        if(smallest != i){
            swap(Heap[i],Heap[smallest]);
            heapify(smallest);
        }
    }

    // Funcion para revisar si es un heap, es para debugear

    bool isHeap() {

        int n = Heap.size();

        for (int i = 0; i <= (n / 2) - 1; ++i) {

            int left = 2 * i + 1;

            int right = 2 * i + 2;


            if (left < n && Heap[left].first < Heap[i].first)
                return false;


            if (right < n && Heap[right].first < Heap[i].first)
                return false;
        }

        return true;
    }
    

    void pop(){
        Heap[0] = Heap[Heap.size()-1];
    
        Heap.pop_back();
        int pos = 0;
        while(2*pos+1 < Heap.size()){
            int left = 2*pos+1;
            int right = 2*pos+2;
            int next = pos;
            if(Heap[left].first < Heap[next].first) next = left;
            if(right < Heap.size() && Heap[right].first < Heap[next].first) next = right;
            if(next == pos) break;
            swap(indices[Heap[pos].second],indices[Heap[next].second]);
            swap(Heap[pos], Heap[next]);
            pos = next;
        }
    }

    pair<double,int> top(){
        return Heap[0];
    }

    bool empty(){
        return Heap.size() == 0;
    }

    void decreaseKey(int nodo, double new_distance){

        int pos = indices[nodo];

        Heap[pos].first = new_distance;
        
        while(pos > 0){
            int parent = (pos-1)/2;
            if(Heap[parent].first <= Heap[pos].first) break;
            swap(indices[Heap[parent].second],indices[Heap[pos].second]);
            swap(Heap[parent], Heap[pos]);
            pos = parent;
        }

    }
    
};