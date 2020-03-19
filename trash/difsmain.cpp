#include <iostream>

#include <vector>

#define VISITED 1
#define NOT_VISITED 0

using namespace std;

class Graph;
class Vertex;

void readInputVertice(Graph*);
void readInputEdges(Graph*);
void readSize(Graph*);
int visit(Graph*, Vertex*);
void solve(Graph*);

class Vertex {
private:
    int _idx;
    int _value;
    int _visited = NOT_VISITED;
    Vertex* _next = NULL;
    
public:
    Vertex() : _idx(0), _value(0) {}
    Vertex(int idx, int value) : _idx(idx), _value(value) {}
    Vertex(const Vertex* v) : Vertex(v->getIndex(), v->getValue()) {}

    int getIndex() const {
        return _idx;
    }

    int isVisited() const {
        return _visited;
    }

    void setVisited() {
        _visited = VISITED;
    }

    void setNotVisited() {
        _visited = NOT_VISITED;
    }

    int getValue() const {
        return _value;
    }

    void setValue(int v) { _value = v; }

    void setIdx(int idx) { _idx = idx; }
    
    /* bool hasNext() {
        return _next != NULL;
    } */

    Vertex* getNext() {
        return _next;
    }

    void setNext(Vertex* v) {
        _next = v;
    }
    
    // For debug
    friend ostream& operator<<(ostream &stream, const Vertex &v) {
        stream << "IDX:" << v.getIndex() << "\n";
        stream << "Value:" << v.getValue() << "\n";
        return stream;
    }

    ~Vertex() {
        delete _next;
    }
};

class Graph {
private:
    int _nVertice;
    int _nEdges;
    int _dirty = 0;
    Vertex** _vertice;
    
public:
    Graph() {
        // read number of edges and vertice from input
        readSize(this);
        // creates the list of Vertex*
        _vertice = new Vertex*[_nVertice];
        readInputVertice(this);
        readInputEdges(this);
    }

    
    Vertex** getVertice() const { return _vertice; }

    Vertex* getVertex(int idx) const { return _vertice[idx]; }

    void setVertex(Vertex *v, int idx) { _vertice[idx] = v; }

    int getNVertice() const { return _nVertice; }

    void setNVertices(int val) { _nVertice = val; }

    int getNEdges() const { return _nEdges; }
    
    void setNEdges(int val) { _nEdges = val; }

    int isDirty() { return _dirty; }

    void setDirty() { _dirty = 1; }

    void setClean() { _dirty = 0; }
    
    void setVertexValue(Vertex* v, int value) {
        v->setValue(value);
        setDirty();
    }

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
        // delete the vetex itself
        for (int i = 0; i < _nVertice ; i++) 
            delete _vertice[i];

        // delete the vector of vertices
        delete[] _vertice;
    }
};

// ================================
// Input Parser
// ================================

void readSize(Graph* G) {
    int nVertice, nEdges;
    scanf("%d,%d", &nVertice, &nEdges);
    G->setNVertices(nVertice);
    G->setNEdges(nEdges);
}

void readInputVertice(Graph* G) {
    //Fill in the already created list of size nVertice
    int value;
    for (int i = 0; i < G->getNVertice(); i++) {
        scanf("%d", &value);
        G->setVertex(new Vertex(i, value), i);
    }
}

void readInputEdges(Graph* G) {
    //Introducing vertice in the linked list
    int from, to;
    for (int i = 0; i < G->getNEdges(); i++) {
        scanf("%d %d", &from, &to);
        from--; 
        to--;
        Vertex* v = new Vertex(G->getVertex(to));
        v->setNext(G->getVertex(from)->getNext());
        G->getVertex(from)->setNext(v);

    }
}

// ================================
// Algorithm
// ================================

int visit(Graph* G, Vertex* v) {
    if (v->isVisited())
        //if already visited return the value
        return v->getValue();
    else
        v->setVisited();

    int value;
    Vertex* vPrev = v;
    Vertex* vTmp;
    while ((vTmp = vPrev->getNext()) != NULL){
        // visit friend
        value = visit(G, G->getVertex(vTmp->getIndex()));
        // update the value if greater
        if (value > v->getValue())
            G->setVertexValue(v, value);

        vPrev = vTmp;
    }
    // returns the value of the current vertex
    return v->getValue(); 
}

void solve(Graph *G) {
    for (int i = 0; i < G->getNVertice(); i++) {
       visit(G, G->getVertex(i));
    }

    if (G->isDirty()) {
        // checks whether there were any changes in the values of the graph
        G->setClean();
        // restarts the "color" of the vertices
        for (int i = 0; i < G->getNVertice(); i++)
            G->getVertex(i)->setNotVisited();
        // runs algorithm again to make sure there are no more changes to be done
        solve(G);
    }
}

// ================================
// Main
// ================================

int main() {
    Graph *G = new Graph();
    solve(G);
    cout << *G;
    delete G;
}