/**
 * Title: Network Broadcasting
 * Author: Michael Femi-Lawal
 *
 * This function takes in an input from a user, which will
 * contain the number of connections as well as directed
 * connections on each line following that. These are placed
 * onto a map, with computers ending with "_server" being put
 * on a map for future reference. A graph is then initialized,
 * with each connection being put in. Afterwards, the graph
 * will used dijkstra's method on any server found within the
 * graph. If none is found, there will be no server found with
 * minimum delay time. Otherwise, the program will display
 * the minimum total delay time alongside the server.
 *
 */

#include <iostream>
#include <map>
#include "graph.h"

const int INFINITE_COST = 1000000000;

using namespace std;

int main() {

    int edges, inputDelays, counter = 0;
    string inputFrom, inputTo;

    cin >> edges;
    map<pair<string, string>, int> connectionMap;
    map<int, string> locationMap;
    bool found = false;

    for (int i = 0; i < edges; i ++) {
        cin >> inputFrom >> inputTo >> inputDelays;

        connectionMap.insert(make_pair(make_pair(inputFrom, inputTo), inputDelays));

        for (auto k = locationMap.begin(); k != locationMap.end(); k ++) {
            if (k->second == inputFrom) {
                found = true;
            }
        }
        if (!found) {
            locationMap.insert(make_pair(counter, inputFrom));
            counter ++;
        }
        found = false;
        for (auto k = locationMap.begin(); k != locationMap.end(); k ++) {
            if (k->second == inputTo) {
                found = true;
            }
        }
        if (!found) {
            locationMap.insert(make_pair(counter, inputTo));
            counter ++;
        }
        found = false;
    }

    Graph network(counter);

    for(auto i = locationMap.begin(); i != locationMap.end(); i ++) {
        for (auto  j = locationMap.begin(); j != locationMap.end(); j++) {

            auto key = make_pair(i->second, j->second);
            auto it = connectionMap.find(key);
            int cost;

            if (it != connectionMap.end()) {
                cost = it->second;
                network.addEdge(i->first, j->first, cost);
            }
        }
    }

    vector<int> serverList;

    for (auto &location : locationMap) {
        if (location.second.find("_server") != string::npos) {
            serverList.push_back(location.first);
        }
    }

    vector<vector<int>> serverDelays;
    vector<string> bestServers;
    int lowestCost = INFINITE_COST;

    for (int server : serverList) {
        vector<int> delays = network.dijkstra(server);
        int totalCost = 0;
        bool canServeAll = true;

        for (int delay : delays) {
            if (delay == INFINITE_COST) {
                canServeAll = false;
                break;
            }
            totalCost += delay;
        }

        if (!canServeAll) {
            continue;
        }

        if (bestServers.empty() || totalCost < lowestCost) {
            lowestCost = totalCost;
            bestServers.clear();
            bestServers.push_back(locationMap[server]);
        } else if (totalCost == lowestCost) {
            bestServers.push_back(locationMap[server]);
        }
    }

    if (bestServers.empty()) {
        cout << "no server can serve the whole network" << endl;
    }
    else {
        cout << "total delay: " << lowestCost << endl;
        sort(bestServers.begin(), bestServers.end());
        for (const string& serverName : bestServers) {
            cout << serverName << endl;
        }
    }

    return 0;
}