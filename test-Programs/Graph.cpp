//
//  Graph.cpp
//  test-Programs
//
//  Created by Vivek Dua on 4/11/18.
//  Copyright © 2018 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>

// Implement Topo Sort - Order the project/process dependencies and launch accordingly

using namespace std;

class graph {

public:
    
    std::list<int> _vertices;
    std::map<int, std::list<int>> _adj;
    
};

// Create a list of the vertices with zero-in-degree
// Add vertices which have zero in-degree to the list.
// If there are none, it is a cycle.


// return the ID of the vertices
void getIndegree(graph g,
                 std::map<int, int> &id) {
    
    // Build the indegree of the vertices
    for (auto &adj : g._adj) {
        list<int> adjList = adj.second;
        if (id.find(adj.first) == id.end()) {
            id.insert(pair<int, int>(adj.first, 0));
        }
        id[adj.first] += adjList.size();
     }
    return;
}



std::list<int> buildListWithZeroIndegree(graph g) {
    std::list<int> zigList;
    
    for (auto &v : g._vertices) {
        // If the vertices does not exist in the map; it is ZID
        if (g._adj.find(v) == g._adj.end()) {
            zigList.push_back(v);
        }
    }
    return zigList;
}
                      
std::list<int> orderVertices (graph g) {
    // Iterate through all the vertices
    // Add the ZID vertices to the ordered vector
    // Remove the dependencies of the ZID vertices from the map
    // Add the ZID vertices again
    // Anytime if the ZID vertices return no more nodes but still vertices left to be traversed - cyclcic graph.
    
    list<int> orderedList;
    int v = 0;
    size_t size = g._vertices.size();
    orderedList = buildListWithZeroIndegree(g);
    list<int> order = orderedList;
    map<int, int> idegMap;
    getIndegree(g, idegMap);
    
    
    while (v < size) {
        
        if (!orderedList.size()) {
            // cycle detected here. no nodes with ZID
            cout << "Cycle detected " << endl;
            return order;
        }
        int prevZidnode = 0;
        for (auto zidnode : orderedList) {
            // Remove the visited node.
            orderedList.remove(prevZidnode);
            for (auto &adj : g._adj) {
                int node = adj.first;
                list<int> adjList = adj.second;
                for (auto dep : adjList) {
                    if (dep == zidnode) {
                        idegMap[node]--;
                        if (idegMap[node] == 0) {
                            // add this node to the orderedList
                            orderedList.push_back(node);
                            order.push_back(node);
                        }
                    }
                }
            }
            prevZidnode = zidnode;
            v++;
        }
        orderedList.remove(prevZidnode);
    }
    return order;
}


int main() {
    
    list<int> vertices = {5, 7, 3, 12, 56, 13, 9, 4};
    list<int> node5List = {13, 56};
    list<int> node12List = {13, 9};
    list<int> node56List = {7, 3, 4};
    list<int> node4List = {56};
    list<int> node3List = {4};
    
    
    map<int, list<int>> adj;
    adj.insert(pair<int, list<int>>(5, node5List));
    adj.insert(pair<int, list<int>>(12, node12List));
    adj.insert(pair<int, list<int>>(56, node56List));
    adj.insert(pair<int, list<int>>(4, node4List));
    adj.insert(pair<int, list<int>>(3, node3List));
    
    graph g;
    g._vertices = vertices;
    g._adj = adj;
    // Order the vertices
    list<int> orderedVert = orderVertices(g);
    cout << "Order is " << endl;
    for (auto &v : orderedVert) {
        cout << v << " ";
    }
    
}
