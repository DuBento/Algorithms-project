#include <iostream>

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
    int _idx;   // allows us to identify each vertex
    int _value;
    int _visited = NOT_VISITED;
    Vertex* _next = NULL;
    
public:
    Vertex() : _idx(0), _value(0) {}
    Vertex(int idx, int value) : _idx(idx), _value(value) {}
    Vertex(const Vertex* v) : Vertex(v->getIdx(), v->getValue()) {}

    int getIdx() const { return _idx; }

    int getValue() const { return _value; }

    void setValue(int v) { _value = v; }

    int isVisited() const { return _visited; }

    void setVisited() { _visited = VISITED; }

    void setNotVisited() { _visited = NOT_VISITED; }
    
    Vertex* getNext() {
        return _next;
    }

    void setNext(Vertex* v) {
        _next = v;
    }
    
    // For debug purposes
    friend ostream& operator<<(ostream &stream, const Vertex &v) {
        stream << "IDX:" << v.getIdx() << "\n";
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
    bool _dirty = false; // to check if there were any changes in the value of the graph 
    Vertex** _vertice;
    
public:
    Graph() {
        // read number of edges and vertice from input
        readSize(this);
        // creates the list of Vertex*
        _vertice = new Vertex*[_nVertice];
        // read the value of the vertice inputed
        readInputVertice(this);
        // read the edges between two vertice inputed
        readInputEdges(this);
    }
    
    Vertex* getVertex(int idx) const { return _vertice[idx]; }

    void setVertex(Vertex *v, int idx) { _vertice[idx] = v; }

    int getNVertice() const { return _nVertice; }

    void setNVertices(int val) { _nVertice = val; }

    int getNEdges() const { return _nEdges; }
    
    void setNEdges(int val) { _nEdges = val; }

    bool isDirty() { return _dirty; }

    void setDirty() { _dirty = true; }

    void setClean() { _dirty = false; }
    
    void setVertexValue(Vertex* v, int value) {
        v->setValue(value);
        setDirty();
    }

    void pushFront(Vertex* v, int idx) {
        v->setNext(getVertex(idx)->getNext());
        getVertex(idx)->setNext(v);
    }
    
    friend ostream& operator<<(ostream &stream, const Graph &G) {
        for (int i = 0; i < G.getNVertice(); i++) {
            stream << G.getVertex(i)->getValue() << "\n";
        }
        return stream;
    }

    void refreshGraph() {
        // checks whether there were any changes in the values of the graph
        if (isDirty()) {
            // checks whether there were any changes in the values of the graph
            setClean();
            // restarts the "color" of the vertices
            for (int i = 0; i < getNVertice(); i++)
                getVertex(i)->setNotVisited();
        }
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
        // Index shift for the array starts at 0
        from--; 
        to--;
        Vertex* v = new Vertex(G->getVertex(to));
        // Insert in begining of linked list
        G->pushFront(v, from);
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
        value = visit(G, G->getVertex(vTmp->getIdx()));
        // update the value if greater
        if (value > v->getValue())
            G->setVertexValue(v, value);
        vPrev = vTmp;
    }
    // returns the value of the current vertex
    return v->getValue(); 
}

void solve(Graph *G) {
    // runs algorithm until there are no more changes to be done
    do {
        G->refreshGraph(); // resets the states altered by the algorithm of previous run
        
        // visiting all vertice (in reality one vertex is not visited twice)
        for (int i = 0; i < G->getNVertice(); i++)
            visit(G, G->getVertex(i));

    } while (G->isDirty());
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