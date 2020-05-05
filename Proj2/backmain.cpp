#include <iostream>
#include <vector>

#define VISITED 1
#define NOT_VISITED 0

using namespace std;
class Vertex;

Vertex*** map;
int nAvenues = 1;
int nStreets = 1;
Vertex *s;  
Vertex *t;
int **edgesMatrix;

enum Type {NORMAL, CLIENT, SHOP};
enum Flux {EMPTY, FULL};

class Vertex {
public:
    vector<Vertex*> _parents = {s};
    vector<Vertex*> _children = {t};
    Type _type = NORMAL;
    int _flux = 0;
    int _xPos, _yPos;

    Vertex(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) {}
    
    int getFlux() { return _flux; }

    Type getType() {
        return _type;
    }

    void setType(Type type) {
        _type = type;
    }

    void swapFlux() {
        _flux = (_flux + 1) % 2;
    }

/*
         3
         |
    1 -- V -- 2
         |
         4
*/

    void auxFillEdges(Type type, vector<Vertex*> *v) {
        if (_xPos > 0 && map[_xPos-1][_yPos]->getType() != type){ 
            v->push_back(map[_xPos-1][_yPos]);
            cout << "1\n";
        }
        if (_xPos < nAvenues-1 && map[_xPos+1][_yPos]->getType() != type) {
            v->push_back(map[_xPos+1][_yPos]);
            cout << "2\n";
        }
        if (_yPos > 0 && map[_xPos][_yPos-1]->getType() != type){
            v->push_back(map[_xPos][_yPos-1]);
            cout << "3\n";
        }
        if (_yPos < nStreets-1 && map[_xPos][_yPos+1]->getType() != type){ 
            v->push_back(map[_xPos][_yPos+1]);
            cout << "4\n";
        }
    }

    virtual void fillEdges() {}
        // cout << _xPos << ";" << _yPos << "\n";
        // auxFillEdges(SHOP, &_parents);
        // cout << "END OF Parent NORMAL" << "\n";
        // auxFillEdges(CLIENT, &_children);
        // cout << "END OF NORMAL" << "\n";
    

    friend ostream& operator<<(ostream &stream, Vertex const v) {
        stream << "posX " << v._xPos << " posY" << v._yPos << '\n';
        return stream;
    }

    ~Vertex() {
        //TODO delete vector??     
    }
};

class Normal : public Vertex {
public:
    Normal(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(NORMAL);
    }
    // shops dont have children except for t
    void fillEdges() override {
        cout << _xPos << ";" << _yPos << "\n";
        auxFillEdges(SHOP, &_parents);
        cout << "END OF Parent NORMAL" << "\n";
        auxFillEdges(CLIENT, &_children);
        cout << "END OF NORMAL" << "\n";
    }
};

class Shop : public Vertex {
public:
    Shop(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(SHOP);
    }
    // shops dont have children except for t
    void fillEdges() override {
        _children.push_back(t);
        auxFillEdges(SHOP, &_parents);
    }
};

class Client : public Vertex {
public:
    Client(int xPos, int yPos) : Vertex(xPos, yPos) {
        setType(CLIENT);
    }
    
    
    // clients dont have parents except for s
    void fillEdges() override {
        _parents.push_back(s);
        auxFillEdges(CLIENT, &_children); 
    } 
};

// ================================
// Input Parser
// ================================

void createMap() {
    scanf("%d %d", &nAvenues, &nStreets);

    // alloc map memory
    map = (Vertex***)malloc(nAvenues*sizeof(Vertex**));
    for(int i=0; i<nAvenues; i++) map[i] = (Vertex**)malloc(nStreets*sizeof(Vertex*));  
    
    // inicialize each Vertice
    for (int i = 0; i < nAvenues; i++)
        for (int j = 0; j < nStreets; j++)
            map[i][j] = new Normal(i,j);    // every vertex is an empty corner by default

    s = new Normal(-1,-1);   
    t = new Normal(nAvenues, nStreets);    
    // Vertex* map[10][10];
    // map1 = Vertex[10][10]; //XXX BAD??? ;)
    
}

void parseValues() {
    int nClients, nShops;
    int x, y;
    scanf("%d %d", &nShops, &nClients);

    // read Shops (x,y) coordinates
    for (int i = 0; i < nShops; i++) {
        scanf("%d %d", &x, &y);
        x--; y--; // input offset
        delete map[x][y];
        map[x][y] = new Shop(x,y);
    }

    // read Clients (x,y) coordinates    
    for (int i = 0; i < nClients; i++) {
        scanf("%d %d", &x, &y);
        x--; y--; // input offset
        delete map[x][y];
        map[x][y] = new Client(x,y); 
    }
}

void createEdges() {
    for (int i = 0; i < nAvenues; i++) {
        for (int j = 0; j < nStreets; j++) {
            map[i][j]->fillEdges();
        }
    }
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





int main() {
    createMap();
    parseValues();
    createEdges();

    //cout << map[0][0]->getType();
    cout << *(map[0][2]->_children[0]);
    // for (auto k : map[0][0]->_children)
    //     cout << 0 << ";" << 0 << "\t" << *k << ' ';

    // for (int k = 0; k != map[0][0]->_children.size(); ++k)
    //     cout << 0 << ";" << 0 << "\t" << *map[0][0]->_children[k] << ' ';
    
    for(int i = 0; i<nAvenues; i++)
        for(int j=0; j<nStreets; j++){
            cout << "---------- " << i << ";" << j << '\n';
            if ((i!=0 || j!=2)){
            
            for (vector<Vertex*>::const_iterator k = map[i][j]->_children.begin(); k != map[i][j]->_children.end(); ++k)
                cout << i << ";" << j << "\t" << **k << '\n';
            }
        }
    edgesMatrix = (int**)malloc(nAvenues*nStreets*sizeof(int*));
    for(int i=0; i<nAvenues*nStreets; i++) map[i] = (Vertex**)malloc(nAvenues*nStreets*sizeof(int));












    //im a little sprout :)
   
    return 0;
}