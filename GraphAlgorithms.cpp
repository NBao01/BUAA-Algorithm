//
// Created by NBao on 2021/01/29.
//

#include <iostream>
#include <vector>

class Graph {
private:
    class Edge;

    class Vertex {
    private:
        int id;
        std::vector<Edge *> adj;
        friend class Graph;
    public:
        explicit Vertex(int id) {
            this->id = id;
        }
    };

    class Edge {
    private:
        Vertex* from;
        Vertex* to;
        friend class Graph;
    public:
        Edge(Vertex* v1, Vertex* v2) {
            from = v1;
            to = v2;
            v1->adj.push_back(this);
        }
    };

    std::vector<Vertex *> vertexes;
    std::vector<Edge *> edges;
    bool directed;
public:
    explicit Graph(bool directed) {
        this->directed = directed;
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
        this->edges.push_back(new Edge(V1, V2));
        if (!directed) {
            this->edges.push_back(new Edge(V2, V1));
        }
    }
};