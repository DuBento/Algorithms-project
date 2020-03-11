#include <iostream>
#include ""
using namespace std;

int visit(Graph* G, Vertex* v) {
    if (v->visited()) {
        return v->value();
    }

    int value;
    for (Vertex* vi: G->getChildren(v)) {
        value = visit(G, vi);
        if (value > v->value()) {
            v->setValue(value);
        }
    }
    return v->value();
}

int solve(Graph *G) {
    for (Vertex* v: G->getVertices()) {
        visit(G, v);
    }
    printSolution(G);
}

int main() {
    int numVertices;
    int numEdges;
    vector<int> *vertices;
    cin >> numVertices >> ", " >> numEdges;
    for (int i = 0; i < numVertices; i++) {
        cin << vertices->push_back();
    }

}

