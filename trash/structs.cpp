#include "structs.h"

class Graph {
private:
    vector<Vertex*> *_vertices;
public:
    Graph() {
        int *nVertice, *nEdges;
        readSize(nVertice, nEdges);
        readInputVertices(_vertices);
        readInputEdges(_vertices);
        // for (int i = 0; i < size; i++) {            
        //     _vertices->push_back(new Vertex(i, verticesVec[i]));
        // }
        
        // _edges = EdgeStruct(EdgesVec);
    }
    vector<int> getChildren(Vertex *v){
        return vector(_edges.getConnecion(_vertices.get)
    }
};


class Vertex {
private:
    int _idx;
    int _value;
    int _visited = NOT_VISITED;
    Vertex* _next = NULL;
    
public:
    Vertex(int idx, int value) : _idx(idx), _value(value) {}

    int getIndex() {
        return _idx;
    }

    int isVisited() {
        return _visited;
    }

    int getValue() {
        return _value;
    }
};