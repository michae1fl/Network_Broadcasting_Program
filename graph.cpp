#include "graph.h"
#include "arrayHeap.h"

void Graph::addEdge(int from, int to, int cost) {
    assert(inVertexRange(from));
    assert(inVertexRange(to));

    Edge newEdge(to, cost);
    adjacencyList[from].push_back(newEdge);
}

vector<int> Graph::dijkstra(int source) const {
    assert(inVertexRange(source));

    vector<int> distance (this->adjacencyList.size(), INFINITE_COST);
    vector<int> key (this->adjacencyList.size(), -1);
    ArrayHeap<pair<int, int>>  heap;

    distance[source] = 0;
    key[source] = heap.insert(make_pair(0, source));

    while(heap.getNumItems() > 0){
        int cost = heap.getMinItem().first;
        int vertex = heap.getMinItem().second;

        heap.removeMinItem();

        //relax
        for(auto i : adjacencyList[vertex]){
            int newDistance = i.cost + distance[vertex];
            int neighbor = i.to;

            if(newDistance < distance[neighbor]){
                distance[neighbor] = newDistance;

                if(!heap.isOnHeap(key[neighbor])){
                    key[neighbor] = heap.insert(make_pair(distance[neighbor], i.to));
                }
                else{
                    heap.changeItemAtKey(key[neighbor],
                            make_pair(distance[neighbor], i.to));
                }
            }
        }
    }

    return distance;
}
