//
// Created by NBao on 2021/01/29.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

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
        Vertex* unionSetParent;
        int unionSetHeight;
        std::vector<Vertex*> adj;
        std::vector<int> weights;
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
            this->unionSetParent = this;
            this->unionSetHeight = 0;
        }
    };

    class Edge {
    private:
        Vertex* from;
        Vertex* to;
        int weight;
        friend class Graph;
    public:
        Edge(Vertex* v1, Vertex* v2, bool directed, int weight = 1) {
            this->from = v1;
            this->to = v2;
            this->weight = weight;
            from->adj.push_back(to);
            from->weights.push_back(weight);
            if (!directed) {
                to->adj.push_back(from);
                to->weights.push_back(weight);
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

    Graph* reverse() {
        auto* R = new Graph(directed);
        for (auto & vertex : vertexes) {
            R->addVertex(vertex->id);
        }
        for (auto & edge : edges) {
            R->addEdge(edge->to->id, edge->from->id);
        }
        return R;
    }

    void initialize_MST_Kruskal_Unionset() {
        for (auto & vertex : vertexes) {
            vertex->unionSetParent = vertex;
            vertex->unionSetHeight = 1;
        }
    }

    static Vertex* MST_Kruskal_Unionset_Findset(Vertex* v) {
        while (v->unionSetParent != v) {
            v = v->unionSetParent;
        }
        return v;
    }

    static void MST_Kruskal_Unionset_Unionset(Vertex* x, Vertex* y) {
        Vertex* a = MST_Kruskal_Unionset_Findset(x);
        Vertex* b = MST_Kruskal_Unionset_Findset(y);
        if (a->unionSetHeight <= b->unionSetHeight) {
            if (a->unionSetHeight == b->unionSetHeight) {
                b->unionSetHeight++;
            }
            a->unionSetParent = b;
        }
        else {
            b->unionSetParent = a;
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

    void addEdge(int v1, int v2, int weight) {
        Vertex* V1 = getVertex(v1);
        Vertex* V2 = getVertex(v2);
        this->edges.push_back(new Edge(V1, V2, directed, weight));
    }

    void BFS(int s) {
        std::queue<Vertex*> Q;
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
        std::reverse(L->begin(), L->end());
        return L;
    }

    std::vector<std::vector<Vertex*>*>* Strongly_Connected_Component() {
        auto* Components = new std::vector<std::vector<Vertex*>*>();
        Graph* R = this->reverse();
        std::vector<Vertex*>* L = R->DFS();

        for (auto & v : vertexes) {
            v->color = WHITE;
        }

        for (int i = (int)L->size() - 1; i >= 0; i--) {
            Vertex* u = L->at(i);
            if (u->color == WHITE) {
                std::vector<Vertex*>* L_SCC = DFS_Visit(u);
                Components->push_back(L_SCC);
            }
        }
        return Components;
    }

    void MST_Prim_Priority_Queue() {
        std::priority_queue<Vertex*> Q;
        std::set<int> visited;
        initialize_BFS();
        vertexes.at(0)->dist = 0;
        Q.push(vertexes.at(0));
        while (!Q.empty()) {
            Vertex *v = Q.top();
            Q.pop();
            if (visited.count(v->id) == 0) {
                visited.insert(v->id);
                for (int i = 0; i < v->adj.size(); i++) {
                    if (visited.count(v->adj.at(i)->id) == 0 && v->weights.at(i) < v->adj.at(i)->dist) {
                        v->adj.at(i)->dist = v->weights.at(i);
                        v->adj.at(i)->pred = v;
                        auto *copy = new Vertex(*v->adj.at(i));
                        Q.push(copy);
                    }
                }
            }
        }
    }

    std::vector<Edge*>* MST_Kruskal() {
        auto* T = new std::vector<Edge*>();
        initialize_MST_Kruskal_Unionset();
        for (auto & edge : edges) {
            if (MST_Kruskal_Unionset_Findset(edge->from) != MST_Kruskal_Unionset_Findset(edge->to)) {
                T->push_back(edge);
                MST_Kruskal_Unionset_Unionset(edge->from, edge->to);
            }
        }
        return T;
    }

    void Single_Source_Shortest_Path_Dijkstra_Priority_Queue() {
        std::priority_queue<Vertex*> Q;
        std::set<int> visited;
        initialize_BFS();
        vertexes.at(0)->dist = 0;
        Q.push(vertexes.at(0));
        while (!Q.empty()) {
            Vertex *v = Q.top();
            Q.pop();
            if (visited.count(v->id) == 0) {
                visited.insert(v->id);
                for (int i = 0; i < v->adj.size(); i++) {
                    if (v->dist + v->weights.at(i) < v->adj.at(i)->dist) {
                        v->adj.at(i)->dist = v->weights.at(i);
                        v->adj.at(i)->pred = v;
                        auto *copy = new Vertex(*v->adj.at(i));
                        Q.push(copy);
                    }
                }
            }
        }
    }
};