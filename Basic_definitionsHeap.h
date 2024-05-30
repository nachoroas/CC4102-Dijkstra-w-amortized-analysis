#include <iostream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;


class QHeap{

    public:
        vector<pair<double,int>> Heap;
        vector<int> indices;

    QHeap(int graph_size){
        indices = vector<int>(graph_size);
    }

    void buildHeap(vector<pair<double,int>> input){
        Heap = input;

        for(int i = Heap.size() - 1; i > -1;i--){
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

    void push(pair<double,int> x){
        Heap.push_back(x);
        int pos = Heap.size()-1;
        this->indices[x.second] = pos;
        while(pos > 0){
            int parent = (pos-1)/2;
            if(Heap[parent].first <= Heap[pos].first) break;
            swap(Heap[parent], Heap[pos]);
            swap(indices[parent],indices[pos]);
            pos = parent;
        }
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
            swap(Heap[pos], Heap[next]);
            swap(indices[pos],indices[next]);
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
            swap(Heap[parent], Heap[pos]);
            swap(indices[parent],indices[pos]);
            pos = parent;
        }
    }
    
};
