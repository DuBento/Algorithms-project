#include <iostream>

#include <vector>

#define VISITED 1
#define NOT_VISITED 0

using namespace std;

class Graph;
class Vertex;

void readInputVertice(Vertex**, int);
void readInputEdges(Vertex**, int);
void readSize(int*, int*);
int visit(Graph*, Vertex*);
void solve(Graph*);

class Vertex {
private:
    int _idx;
    int _value;
    int _visited = NOT_VISITED;
    Vertex* _next = NULL;
    
public:
    Vertex(){}
    Vertex(int idx, int value) : _idx(idx), _value(value) {}
    Vertex(Vertex* v) : Vertex(v->getIdx(), v->getValue()) {}

    int getIndex() {
        return _idx;
    }

    int isVisited() {
        return _visited;
    }

    int getValue() {
        return _value;
    }

    void setValue(int v) { _value = v; }

    int getIdx() {
        return _idx;
    }

    void setIdx(int idx) {
        _idx = idx;
    }
    
    /* bool hasNext() {
        return _next != NULL;
    } */

    Vertex* getNext() {
        return _next;
    }

    void setNext(Vertex* v) {
        _next = v;
    }
};

class Graph {
private:
    int _nVertice;
    int _nEdges;
    Vertex** _vertice;
public:
    Graph() {
        // read number of edges and vertice from input
        readSize(&_nVertice, &_nEdges);
        // creates the list of Vertex*
        _vertice = new Vertex*[_nVertice];
        readInputVertice(_vertice, _nVertice);
        readInputEdges(_vertice, _nEdges);
    }
    
    Vertex** getVertice() const {
        return _vertice;
    }

    Vertex* getVertex(int idx) const {
        return _vertice[idx];
    }

    int getNVertice() const { return _nVertice; }
    
    Vertex** getChildren(Vertex* vertex) {
        Vertex* vPrev = vertex;
        Vertex* v;
        Vertex** vertice;
        int i = 0;
        while ((v = vPrev->getNext()) != NULL) {
            vertice[i++] = v;
            vPrev = v;
        }
        return vertice; 
    }
    
    friend ostream& operator<<(ostream &stream, const Graph &G) {
        for (int i = 0; i < G.getNVertice(); i++) {
            stream << G.getVertex(i)->getValue() << "\n";
        }
        return stream;
    }
    ~Graph(){
        // TODO
    }
};



void readInputVertice(Vertex** vertice, int nVertice) {
    //Fill in the already created list of size nVertice
    int value;
    for (int i = 0; i < nVertice; i++) {
        cout << "antes\n";
        scanf("%d", &value);
        cout << "Depois\n";
        Vertex* v = vertice[i];
        v->setValue(value);
        v->setIdx(i);
    }
}

void readInputEdges(Vertex** vertice, int nEdges) {
    //Introducing vertice in the linked list
    int from, to;
    for (int i = 0; i < nEdges; i++) {
        scanf("%d, %d", &from, &to);
        Vertex* v = new Vertex(vertice[to]);
        v->setNext(vertice[from]->getNext());
        vertice[from]->setNext(v);
    }
}

void readSize(int *numvertice, int *numEdges) {
    scanf("%d, %d", numvertice, numEdges);
    cout << *numvertice << " ;DEBUG; " << *numEdges << "\n";
}

int visit(Graph* G, Vertex* v) {
    if (v->isVisited()) {
        return v->getValue();
    }

    int value;
    Vertex* vv;
    while ((vv = v->getNext()) != NULL){
        value = visit(G, vv);
        if (value > v->getValue()) {
            v->setValue(value);
        }
    }
    
    return v->getValue();
}

void solve(Graph *G) {
    for (int i = 0; G->getNVertice(); i++) {
        visit(G, G->getVertex(i));
    }
}


int main() {
    Graph *G = new Graph();
    solve(G);
    cout << G;
}