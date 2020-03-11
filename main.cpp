#include <iostream>

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

int solve(G) {
    for (Vertex* v: G->getVertices()) {
        visit(G, v);
    }
    printSolution(G);
}