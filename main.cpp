#include <iostream>

#include <vector>

#define WHITE 0
#define GREY 1
#define BLACK 2

#define MAX(a,b) a > b ? a : b

using namespace std;

class Graph;
class Vertex;

void readInputVertice(Graph*);
void readInputEdges(Graph*);
void readSize(Graph*);
int getMax(Graph*, Vertex*);
int visit(Graph*, Vertex*);
void solve(Graph*);

class Vertex {
private:
    int _idx;
    int _value;
    int _color = WHITE;
    Vertex* _next = NULL;
    
public:
    Vertex() : _idx(0), _value(0) {}
    Vertex(int idx, int value) : _idx(idx), _value(value) {}
    Vertex(const Vertex* v) : Vertex(v->getIndex(), v->getValue()) {}

    int getIndex() const {
        return _idx;
    }

    int getColor() const {
        return _color;
    }

    bool isWhite() {
        return _color == WHITE;
    }

    bool isGrey() {
        return _color == GREY;
    }
    
    bool isBlack() {
        return _color == BLACK;
    }

    void setGrey() {
        // printf("SETGREY\n");
        _color = GREY;
    }
    void setBlack() {
        _color = BLACK;
    }

    int getValue() const {
        return _value;
    }

    void setValue(int v) { _value = v; }

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
    
    // For debug
    friend ostream& operator<<(ostream &stream, const Vertex &v) {
        stream << "IDX:" << v.getIndex() + 1 << "\n";
        stream << "Value:" << v.getValue() << "\n";
        stream << "Color:" << v.getColor() << "\n";
        return stream;
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
        readSize(this);
        // creates the list of Vertex*
        _vertice = new Vertex*[_nVertice];
        readInputVertice(this);
        readInputEdges(this);
    }

    
    Vertex** getVertice() const {
        return _vertice;
    }

    Vertex* getVertex(int idx) const {
        // DEBUG
        // cout  << *_vertice[idx];
        return _vertice[idx];
    }

    void setVertex(Vertex *v, int idx) {
        _vertice[idx] = v;
    }

    int getNVertice() const { return _nVertice; }

    void setNVertices(int val) { _nVertice = val; }

    int getNEdges() const { return _nEdges; }
    
    void setNEdges(int val) { _nEdges = val; }

    Vertex* getOriginalVertex(Vertex* v) {
        return getVertex(v->getIndex());
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
        // TODO
    }
};



void readInputVertice(Graph* G) {
    //Fill in the already created list of size nVertice
    int value;
    for (int i = 0; i < G->getNVertice(); i++) {
        scanf("%d", &value);
        // Vertex* v = G->getVertex(i);
        G->setVertex(new Vertex(i, value), i);
        // cout << "INPUTED:\t" << G->getVertex(i)->getValue() << "\n";
        // G->getVertex(i)->setValue(value);
        // G->getVertex(i)->setIdx(i);
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

void readSize(Graph* G) {
    int nVertice, nEdges;
    scanf("%d,%d", &nVertice, &nEdges);
    G->setNVertices(nVertice);
    G->setNEdges(nEdges);
}

int getMax(Graph* G, Vertex* v) {
    int maxValue = 0;
    int value = v->getValue();
    Vertex* vPrev;
    Vertex* vTmp = v;
    Vertex* vOrig;
    do{
        getchar();
        // cout << "TMP\t" << *vTmp << "\n";
        vOrig = G->getOriginalVertex(vTmp);
        if (vOrig->isGrey() && vOrig->getNext() != NULL){
            vOrig->setBlack();
            value = getMax(G, vOrig->getNext());
            vOrig->setGrey();
        }
        else if (vOrig->isBlack())
            value = vOrig->getValue();
        else
            return -1; // in case of v color is white

        maxValue = MAX(maxValue, value);
        // debug
        // printf("VALUE %d ::: MAXVALUE %d\n", value, maxValue);
        vPrev = vTmp; //next

    }while ((vTmp = vPrev->getNext()) != NULL);

        // if (vTmp->isGrey() && (value = getMax(G, vTmp) > maxValue))
        //     maxValue = value;
           
        // else if (vTmp->isBlack() && (value = vTmp->getValue()) > maxValue))
        //     maxValue = value;
        
    // printf("ACABOU GETMAX!!!!\n");
    return maxValue;
}


int visit(Graph* G, Vertex* v) {
    int value;
    Vertex* vPrev = v;
    Vertex* vTmp;
    Vertex* vOrig;
    getchar();
    // cout << "WHITE\t" << *v ; 
    //vertex visited 
    v->setGrey();

    while ((vTmp = vPrev->getNext()) != NULL){
        vOrig = G->getOriginalVertex(vTmp);
        if (vOrig->isWhite()){
            // cout << "VTMP\t" << *vTmp << "\n"; 
            // cout << "VORIG\t" << *vOrig << "\n"; 
            visit(G, vOrig);
        }
        vPrev = vTmp;
    }

    // cout << "GREY\t" << *v; 

    //vertex terminated
    v->setBlack();
    
    vPrev = v; //reboot vPrev
    while ((vTmp = vPrev->getNext()) != NULL){
        vOrig = G->getOriginalVertex(vTmp);

        value = getMax(G, vOrig);
        // printf("\tGETMAX RESULT: %d\n", value);
        v->setValue(MAX(value, v->getValue()));
        vPrev = vTmp;
    }

    // cout << "BLACK\t" << *v << "\n"; 

    return v->getValue();
}

void solve(Graph *G) {
    for (int i = 0; i < G->getNVertice(); i++) {
    //    cout << "ITER:\t" << i << "\n";
       visit(G, G->getVertex(i));
    }
}


int main() {
    Graph *G = new Graph();
    solve(G);
    cout << *G;
}