#include "structs.h"

class Graph {
private:
    EdgeStruct _edges;
    vector<Vertex*> *_vertices; 

public:
    Graph(vector<int> *verticesVec, int **EdgesVec) {
        for (int i: *verticesVec) {
            _vertices->push_back(new Vertex(i));
        }
        
        _edges = EdgeStruct(EdgesVec);
    }
    vector<int> getChildren(Vertex *v){
        return vector(_edges.getConnecion(_vertices.get)
    }
};


class Edge {

};

class EdgeStruct {
private:
    int **_matrix;
public:
    EdgeStruct(int **vec) : _matrix(vec) {}
    int* getConnections()
};


class Vertex {
private:
    int _visited = NOT_VISITED;
    int _value;
    
public:
    Vertex(int value) : _value(value) {}

    int isVisited() {
        return _visited;
    }

    int getValue() {
        return _value;
    }
};