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
    
    std::list<int> vertices;
    std::map<int, std::list<int>> adj;
    
};

// Create a list of the vertices with zero-in-degree
// Add vertices which have zero in-degree to the list.
// If there are none, it is a cycle.


// return the ID of the vertices
void getIndegree(graph g,
                 std::map<int, int> id) {
    
    // Init the ID to zero for all nodes.
    for (auto &element : g.vertices) {
        id.insert(pair<int, int>(element, 0));
    }
    
    // Build the indegree of the vertices
    for (auto &adj : g.adj) {
        list<int> adjList = adj.second;
        
        for (auto &listElement : adjList) {
            id[listElement]++;
        }
     }
    return;
}




std::list<int> buildListWithZeroIndegree(graph g) {
    std::list<int> zigList;
    
    for (auto &v : g.vertices) {
        // If the vertices does not exist in the map; it is ZID
        if (g.adj.find(v) == g.adj.end()) {
            zigList.push_front(v);
        }
    }
    return zigList;
}
                      
std::list<int> orderVertices (graph g) {
    // Iterate through the vertices
    // Add the ZID nodes to the ordered vector
    // Remove the dependencies of the ZID nodes from the map
    // Add the ZID nodes again
    
    list<int> orderedList;
    int v = 0;
    size_t size = g.vertices.size();
    orderedList = buildListWithZeroIndegree(g);
    list<int> order = orderedList;
    map<int, int> idegMap;
    getIndegree(g, idegMap);
    
    
    while (v < size) {
        
        if (!orderedList.size()) {
            // cycle detected here. no nodes with ZID
            return list<int>();
        }
        
        for (auto &zidnode : orderedList) {
            // Remove these dependencies from the graph
            for (auto &adj : g.adj) {
                int node = adj.first;
                list<int> adjList = adj.second;
                for (auto &dep : adjList) {
                    if (dep == zidnode) {
                        if (idegMap[dep] == 1) {
                            // add this node to the orderedList
                            orderedList.push_back(node);
                            order.push_back(node);
                        } else {
                            idegMap[dep]--;
                        }
                    }
                }
            }
            orderedList.remove(zidnode);
            v++;
         }
    }
    return order;
}