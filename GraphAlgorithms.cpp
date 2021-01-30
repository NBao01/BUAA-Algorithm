//
// Created by NBao on 2021/01/29.
//

#include <iostream>
#include <vector>
#include <queue>

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

    void DFS_Visit(Vertex* v) {
        v->color = GRAY;
        v->discover = ++time;
        for (auto & w : v->adj) {
            if (w->color == WHITE) {
                w->pred = v;
                DFS_Visit(w);
            }
        }
        v->color = BLACK;
        v->finish = ++time;
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

    void DFS() {
        initialize_DFS();
        for (auto & v : vertexes) {
            if (v->color == WHITE) {
                DFS_Visit(v);
            }
        }
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
};