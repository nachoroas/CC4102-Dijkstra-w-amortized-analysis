#include <iostream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

struct FibonacciNode {
	int degree; 
	FibonacciNode* parent; 
	FibonacciNode* child; 
	FibonacciNode* left; 
	FibonacciNode* right;
	bool mark; 
	double distance; 
	int indice; 
};

class QFibonacci{
	public:
	FibonacciNode* minNode;
	int n;
	vector<FibonacciNode*> degTable;
	vector<FibonacciNode*> nodePtrs;

	public:
	QFibonacci(int n) {
		//Constructor function
		this->n = 0;
		this->minNode = NULL;
		this->degTable = {};
		this->nodePtrs.resize(n);
	}

	bool empty() {
		return this->n == 0;
	}

	void insert(int nodo, double distance) {
		//Insert the vertex u with the specified distance (value for L(nodo)) into the Fibonacci heap. O(1) operation
		this->nodePtrs[nodo] = new FibonacciNode;
		this->nodePtrs[nodo]->indice = nodo;
		FibonacciNode* node = this->nodePtrs[nodo];
		node->distance = distance;
		node->degree = 0;
		node->parent = NULL;
		node->child = NULL;
		node->left = node;
		node->right = node;
		node->mark = false;
		FibonacciNode* minN = this->minNode;
		if (minN != NULL) {
			FibonacciNode* minLeft = minN->left;
			minN->left = node;
			node->right = minN;
			node->left = minLeft;
			minLeft->right = node;
		}
		if (minN == NULL || minN->distance > node->distance) {
			this->minNode = node;
		}
		this->n++;
	}

	FibonacciNode* extractMin() {
		//Extract the node with the minimum distance from the heap. O(log n) operation, where n is the number of nodes in the heap
		FibonacciNode* minN = this->minNode;
		if (minN != NULL) {
			int deg = minN->degree;
			FibonacciNode* child = minN->child;
			FibonacciNode* otherChild;
			for (int i = 0; i < deg; i++) {
				otherChild = child;
				child = child->right;
				_addToRoot(otherChild);
			}
			_removeFromRoot(minN);
			this->n--;
			if (this->n == 0) {
				this->minNode = NULL;
			}
			else {
				this->minNode = minN->right;
				FibonacciNode* minNLeft = minN->left;
				this->minNode->left = minNLeft;
				minNLeft->right = this->minNode;
				_consolidate();
			}
		}
		return minN;
	}
	
	void decreaseKey(int nodo, double new_distance) {
		//Decrease the distance of the node in the Fibonacci heap that has index nodo. O(1) operation
		FibonacciNode* node = this->nodePtrs[nodo];
		if (new_distance > node->distance){
			return;
		}
		node->distance = new_distance;
		FibonacciNode* parentNode = node->parent;
		if (parentNode != NULL && node->distance < parentNode->distance) {
			_cut(node);
			_cascadingCut(parentNode);
			
		}
		if (node->distance < this->minNode->distance) {
			this->minNode = node;
		}
	}

	private:
	//The following are private functions used by the public methods above
	void _addToRoot(FibonacciNode* new_node) {
		FibonacciNode* minN = this->minNode;
		new_node->parent = NULL;
		new_node->mark = false;
		if (minN != NULL) {
			FibonacciNode* minLeft = minN->left;
			minN->left = new_node;
			new_node->right = minN;
			new_node->left = minLeft;
			minLeft->right = new_node;
			if (minN->distance > new_node->distance) {
				this->minNode = new_node;
			}
		}
		else {
			this->minNode = new_node;
			new_node->right = new_node;
			new_node->left = new_node;
		}
	}

	void _removeFromRoot(FibonacciNode* node) {
		if (node->right != node) {
			node->right->left = node->left;
			node->left->right = node->right;
		}
		if (node->parent != NULL) {
			if (node->parent->degree == 1) {
				node->parent->child = NULL;
			}
			else {
				node->parent->child = node->right;
			}
			node->parent->degree--;
		}
	}

	void _cut(FibonacciNode* node) {
		_removeFromRoot(node);
		_addToRoot(node);
	}

	void _addChild(FibonacciNode* parentNode, FibonacciNode* newChildNode) {
		if (parentNode->degree == 0) {
			parentNode->child = newChildNode;
			newChildNode->right = newChildNode;
			newChildNode->left = newChildNode;
		}
		else {
			FibonacciNode* child1 = parentNode->child;
			FibonacciNode* child1Left = child1->left;
			child1->left = newChildNode;
			newChildNode->right = child1;
			newChildNode->left = child1Left;
			child1Left->right = newChildNode;
		}
		newChildNode->parent = parentNode;
		parentNode->degree++;
	}

	void _cascadingCut(FibonacciNode* node) {
		FibonacciNode* parentNode = node->parent;
		if (parentNode != NULL) {
			if (node->mark == false) {
				node->mark = true;
			}
			else {
				_cut(node);
				_cascadingCut(parentNode);
			}
		}
	}

	void _link(FibonacciNode* highNode, FibonacciNode* lowNode) {
		_removeFromRoot(highNode);
		_addChild(lowNode, highNode);
		highNode->mark = false;
	}

	void _consolidate() {
		int deg, rootCnt = 0;
		if (this->n > 1) {
			this->degTable.clear();
			FibonacciNode* currNode = this->minNode;
			FibonacciNode* currDeg, * currConsolNode;
			FibonacciNode* temp = this->minNode, * itNode = this->minNode;
			do {
				rootCnt++;
				itNode = itNode->right;
			} while (itNode != temp);
			for (int cnt = 0; cnt < rootCnt; cnt++) {
				currConsolNode = currNode;
				currNode = currNode->right;
				deg = currConsolNode->degree;
				
				while (true) {
					while (deg >= int(this->degTable.size())) {
						this->degTable.push_back(NULL);
					}
					if (this->degTable[deg] == NULL) {
						this->degTable[deg] = currConsolNode;
						break;
					}
					else {
						currDeg = this->degTable[deg];
						if (currConsolNode->distance > currDeg->distance) {
							swap(currConsolNode, currDeg);
						}
						if (currDeg == currConsolNode) break;
						_link(currDeg, currConsolNode);
						this->degTable[deg] = NULL;
						deg++;
					}
				}
				
			}
			this->minNode = NULL;
			for (size_t i = 0; i < this->degTable.size(); i++) {
				if (this->degTable[i] != NULL) {
					_addToRoot(this->degTable[i]);
				}
			}
		}
	}
};