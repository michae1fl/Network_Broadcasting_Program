#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <cassert>

using namespace std;

struct Edge {
public:
    Edge(int aTo = 0, int aCost = 0) : to(aTo), cost(aCost) {}
    int to;
    int cost;
};

class Graph {
public:
    enum { INFINITE_COST = 1000000000 };

    Graph(unsigned int numVertices) : adjacencyList(numVertices) {}

    void addEdge(int from, int to, int cost);

    vector<int> dijkstra(int source) const;

    bool inVertexRange(unsigned int ndx) const {
        return (0 <= ndx) && (ndx < adjacencyList.size());
    }

private:
    Graph(const Graph &) { assert(false); }
    const Graph &operator=(const Graph &) { assert(false); return *this; }

    vector<list<Edge> > adjacencyList;
};

#endif
