#include <iostream>
#include <vector>

#define VISITED 1
#define NOT_VISITED 0

using namespace std;
class Vertex;

Vertex*** map_in;
Vertex*** map_out;
int nAvenues = 1;
int nStreets = 1;
Vertex *s;  
Vertex *t;
int maxFlow = 0;

enum Type {NORMAL, CLIENT, SHOP, BLOCKED};

class Vertex {
public:
    vector<Vertex*> _children;
    Type _type = NORMAL;
    int _xPos, _yPos;
    bool _visited;       // used in BFS

    Vertex(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) {}

    Type getType() {
        return _type;
    }

    void setType(Type type) {
        _type = type;
    }

    bool isVisited() {
        return _visited;
    }

    void setVisited() {
        _visited = true;
    }

    void setNotVisited() {
        _visited = false;
    }


/*
         3
         |
    1 -- V -- 2
         |
         4
*/

    void auxFillEdges(Vertex*** map, Type type) {
        if (_xPos > 0 && map[_xPos-1][_yPos]->getType() != type
            && map[_xPos-1][_yPos]->getType() != BLOCKED)
            _children.push_back(map[_xPos-1][_yPos]);
        if (_xPos < nAvenues-1 && map[_xPos+1][_yPos]->getType() != type
            && map[_xPos+1][_yPos]->getType() != BLOCKED)
            _children.push_back(map[_xPos+1][_yPos]);
        if (_yPos > 0 && map[_xPos][_yPos-1]->getType() != type
            && map[_xPos][_yPos-1]->getType() != BLOCKED)
            _children.push_back(map[_xPos][_yPos-1]);
        if (_yPos < nStreets-1 && map[_xPos][_yPos+1]->getType() != type
            && map[_xPos][_yPos+1]->getType() != BLOCKED) 
            _children.push_back(map[_xPos][_yPos+1]);
    }


    virtual void fillEdgesIn() {        // fill edges for vertices of type in
        // cout << _xPos << ";" << _yPos << "\n";
        _children.push_back(map_out[_xPos][_yPos]);
    }

    virtual void fillEdgesOut() {       // fill edges for vertices of type out
        // cout << _xPos << ";" << _yPos << "\n";
        auxFillEdges(map_in, CLIENT);
    }

    void addChild(Vertex *v) {
        _children.push_back(v);
    }

    void removeChild(Vertex *v) {
        for (long unsigned int i = 0; i < _children.size(); i++) 
            if (v == _children.at(i)) {
                _children.erase(_children.begin()+i); 
                return;
            }
    }


    friend ostream& operator<<(ostream &stream, Vertex const v) {
        stream << "posX " << v._xPos+1 << " posY" << v._yPos+1 << '\n';
        return stream;
    }

    
    virtual ~Vertex() { }
   
};

class Shop : public Vertex {
public:
    Shop(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(SHOP);
    }
    // shops dont have children except for t
    void fillEdgesIn() override {
        _children.push_back(map_out[_xPos][_yPos]);
    }
    void fillEdgesOut() override {
        _children.push_back(t);
    }
};

class Client : public Vertex {
public:
    Client(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(CLIENT);
    }
    
    
    // clients dont have parents except for s
    void fillEdgesIn() override {
        _children.push_back(map_out[_xPos][_yPos]);
    } 
    
    void fillEdgesOut() override {
        auxFillEdges(map_in, CLIENT); 
    } 
};

class Blocked : public Vertex {
public:
    Blocked(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(BLOCKED);
    }

    // blocked vertices dont have edges
    void fillEdgesIn() override {}
    void fillEdgesOut() override {}
};

// ================================
// Input Parser
// ================================

void createMap() {
    scanf("%d %d", &nAvenues, &nStreets);

    // alloc map memory
    map_in = (Vertex***)malloc(nAvenues*sizeof(Vertex**));
    map_out = (Vertex***)malloc(nAvenues*sizeof(Vertex**));
    for(int i=0; i<nAvenues; i++) {
        map_in[i] = (Vertex**)malloc(nStreets*sizeof(Vertex*));  
        map_out[i] = (Vertex**)malloc(nStreets*sizeof(Vertex*));  
    }

    // inicialize each Vertice
    for (int i = 0; i < nAvenues; i++)
        for (int j = 0; j < nStreets; j++) {
            map_in[i][j] = new Vertex(i,j);    // every vertex is an empty corner by default
            map_out[i][j] = new Vertex(i,j);    // every vertex is an empty corner by default
        }

    s = new Vertex(-1,-1);   
    t = new Vertex(nAvenues, nStreets);    
    
}

void parseValues() {
    int nClients, nShops;
    int x, y;
    scanf("%d %d", &nShops, &nClients);

    // read Shops (x,y) coordinates
    for (int i = 0; i < nShops; i++) {
        scanf("%d %d", &x, &y);
        x--; y--; // input offset
        delete map_in[x][y];
        delete map_out[x][y];
        map_in[x][y] = new Shop(x,y);
        map_out[x][y] = new Shop(x,y);
        //add to target
    }

    // read Clients (x,y) coordinates    
    for (int i = 0; i < nClients; i++) {
        scanf("%d %d", &x, &y);
        x--; y--; // input offset
        if (map_in[x][y]->getType() == SHOP || map_in[x][y]->getType() == BLOCKED) {
            if (map_in[x][y]->getType() == SHOP) maxFlow++;
            delete map_in[x][y];
            delete map_out[x][y];
            map_in[x][y] = new Blocked(x,y);
            map_out[x][y] = new Blocked(x,y); 
        }
        
        else {
            delete map_in[x][y];
            delete map_out[x][y];
            map_in[x][y] = new Client(x,y);
            //add to source
            s->addChild(map_in[x][y]); 
            map_out[x][y] = new Client(x,y); 
        }
    }
}

void createEdges() {
    for (int i = 0; i < nAvenues; i++) {
        for (int j = 0; j < nStreets; j++) {
            map_in[i][j]->fillEdgesIn();
            map_out[i][j]->fillEdgesOut();
        }
    }
}

void visit(Vertex* v, vector<Vertex*> *path, bool *endFound) {
    if (v == t) {
        path->push_back(t);
        *endFound = true;
        return;
    } else {
        v->setVisited();
        path->push_back(v);
    }
    
    for (Vertex* vChild : v->_children){
        if (*endFound) break;
        if (!vChild->isVisited())
            visit(vChild, path, endFound);
    }
    
    if (!*endFound) path->pop_back();
}

//debug
void printPath(vector<Vertex*> path) {
    //cout << "_-_--___PATH____----____\n";
    for(Vertex* v: path)
        cout << *v << "\n";
    //cout << "--__--__END_OF_PATH____-_----\n";

}

void findPath(vector<Vertex*> *path) {
    // initialize all vertices as not visited
    for (int i = 0; i < nAvenues; i++)
        for (int j = 0; j < nStreets; j++) {
            map_in[i][j]->setNotVisited();
            map_out[i][j]->setNotVisited();
        }
    
    s->setNotVisited();
    t->setNotVisited();
    bool endFound = false;
    // saves augmentation path from s to t
    visit(s, path, &endFound);
    
    /*
    list<Vertex*> queue;
    queue.push_back(s);
    while(!queue.empty()) {
        visit(queue.pop_front());

        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    }
    */
}

int computeMaxFlow() {
    vector<Vertex*> path;
    findPath(&path);
    Vertex* previous;
    
    //debug


    while (!path.empty()) {
        previous = NULL;
        
        // printPath(path);

        // loop through path
        for(Vertex* v : path) {
            if (previous != NULL) {
                previous->removeChild(v);
                v->addChild(previous);
            }
            previous = v;
        }
        maxFlow++;
        path.erase(path.begin(), path.end());
        findPath(&path);
    }

    return maxFlow;
}





// void readInputVertice(Graph* G) {
//     //Fill in the already created list of size nVertice
//     int value;
//     for (int i = 0; i < G->getNVertice(); i++) {
//         scanf("%d", &value);
//         G->setVertex(new Vertex(i, value), i);
//     }
// }

// void readInputEdges(Graph* G) {
//     //Introducing vertice in the linked list
//     int from, to;
//     for (int i = 0; i < G->getNEdges(); i++) {
//         scanf("%d %d", &from, &to);
//         // Index shift for the array starts at 0
//         from--; 
//         to--;
//         Vertex* v = new Vertex(G->getVertex(to));
//         // Insert in begining of linked list
//         G->pushFront(v, from);
//     }
// }


//debug
void printChildren(Vertex*** map){
    cout << "CHILDREN" << "\n";
    for(int i = 0; i<nAvenues; i++)
        for(int j=0; j<nStreets; j++){
            cout << "---------- " << i << ";" << j << "\tsize" << map[i][j]->_children.size() <<'\n';
            unsigned sk = map[i][j]->_children.size();
            for(unsigned int k =0 ; k < sk; k++)
                cout << i+1 << ";" << j+1 << "\t" << *(map[i][j]->_children[k]) << '\n';
        }
}



int main() {
    createMap();
    parseValues();
    createEdges();

    // DEBUG
    // cout << "MAP_IN" << "\n";
    // printChildren(map_in);
    
    // cout << "MAP_OUT" << "\n";
    // printChildren(map_out);
    
    cout << computeMaxFlow() << "\n";

    //im a little sprout :)
    
    for (int i=0; i<nAvenues; i++){
        for(int j=0; j<nStreets; j++) {
            delete map_in[i][j];
            delete map_out[i][j];
        }
        free(map_in[i]);
        free(map_out[i]);
    }

    free(map_in);
    free(map_out);    
    delete s;
    delete t;

    return 0;
}