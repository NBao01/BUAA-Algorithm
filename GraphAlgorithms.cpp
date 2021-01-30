//
// Created by NBao on 2021/01/29.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define WHITE 0
#define GRAY 1
#define BLACK 2

class Graph {
private:
    class Edge;

    class Vertex {
    private:
        int id;
        int color;
        Vertex* pred;
        int dist;
        int discover;
        int finish;
        int inDegree;
        std::vector<Vertex*> adj;
        friend class Graph;
    public:
        explicit Vertex(int id) {
            this->id = id;
            this->color = 0;
            this->pred = nullptr;
            this->dist = 0;
            this->discover = 0;
            this->finish = 0;
            this->inDegree = 0;
        }
    };

    class Edge {
    private:
        Vertex* from;
        Vertex* to;
        friend class Graph;
    public:
        Edge(Vertex* v1, Vertex* v2, bool directed) {
            from = v1;
            to = v2;
            v1->adj.push_back(v2);
            if (!directed) {
                v2->adj.push_back(v1);
            }
        }
    };

    std::vector<Vertex *> vertexes;
    std::vector<Edge *> edges;
    bool directed;

    int time;

    void initialize_BFS() {
        for (auto & vertex : vertexes) {
            vertex->color = WHITE;
            vertex->pred = nullptr;
            vertex->dist = 0x3f3f3f3f;
        }
    }

    void initialize_DFS() {
        time = 0;
        for (auto & vertex : vertexes) {
            vertex->color = WHITE;
            vertex->pred = nullptr;
        }
    }

    std::vector<Vertex*>* DFS_Visit(Vertex* v) {
        auto* L = new std::vector<Vertex*>();
        v->color = GRAY;
        v->discover = ++time;
        for (auto & w : v->adj) {
            if (w->color == WHITE) {
                w->pred = v;
                std::vector<Vertex*>* l = DFS_Visit(w);
                L->insert(L->end(), l->begin(), l->end());
            }
        }
        v->color = BLACK;
        L->push_back(v);
        v->finish = ++time;
        return L;
    }

    bool DFS_Visit_Judge_Cycle(Vertex* v) {
        v->color = GRAY;
        v->discover = ++time;
        for (auto & w : v->adj) {
            if (w->color == GRAY) {
                return true;
            }
            if (w->color == WHITE) {
                w->pred = v;
                if (DFS_Visit_Judge_Cycle(w)) {
                    return true;
                }
            }
        }
        v->color = BLACK;
        v->discover = ++time;
        return false;
    }

    void initialize_Topological_Sort_BFS() {
        for (auto & vertex : vertexes) {
            vertex->inDegree = vertex->adj.size();
        }
    }

public:
    explicit Graph(bool directed) {
        this->directed = directed;
        this->time = 0;
    }

    void addVertex(int id) {
        this->vertexes.push_back(new Vertex(id));
    }

    Vertex* getVertex(int id) {
        for (auto & vertex : vertexes) {
            if (vertex->id == id) {
                return vertex;
            }
        }
        exit(-1);
    }

    void addEdge(int v1, int v2) {
        Vertex* V1 = getVertex(v1);
        Vertex* V2 = getVertex(v2);
        this->edges.push_back(new Edge(V1, V2, directed));
    }

    void BFS(int s) {
        std::queue<Vertex *> Q;
        initialize_BFS();
        Vertex* S = getVertex(s);
        S->color = GRAY;
        S->dist = 0;
        Q.push(S);
        while(!Q.empty()) {
            Vertex* u = Q.front();
            Q.pop();
            for (auto & v : S->adj) {
                if (v->color == WHITE) {
                    v->color = GRAY;
                    v->dist = u->dist + 1;
                    v->pred = u;
                    Q.push(v);
                }
            }
            u->color = BLACK;
        }
    }

    std::vector<Vertex*>* DFS() {
        initialize_DFS();
        auto* L = new std::vector<Vertex*>();
        for (auto & v : vertexes) {
            if (v->color == WHITE) {
                std::vector<Vertex*>* l = DFS_Visit(v);
                L->insert(L->end(), l->begin(), l->end());
            }
        }
        return L;
    }

    bool DFS_Judge_Cycle() {
        initialize_DFS();
        for (auto & v : vertexes) {
            if (v->color == WHITE) {
                if (DFS_Visit_Judge_Cycle(v)) {
                    return true;
                }
            }
        }
        return false;
    }

   std::vector<Vertex*>* Topological_Sort_BFS() {
        initialize_Topological_Sort_BFS();
        std::queue<Vertex*> Q;
        auto* P = new std::vector<Vertex*>();
        for (auto & v : vertexes) {
            if (v->inDegree == 0) {
                Q.push(v);
            }
        }
        while (!Q.empty()) {
            Vertex* u = Q.front();
            Q.pop();
            P->push_back(u);
            for (auto & v : u->adj) {
                v->inDegree--;
                if (v->inDegree == 0) {
                    Q.push(v);
                }
            }
        }
        return P;
    }

    std::vector<Vertex*>* Topological_Sort_DFS() {
        std::vector<Vertex*>* L = DFS();
        reverse(L->begin(), L->end());
        return L;
    }
};