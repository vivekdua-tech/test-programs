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


class graph {

public:
    
    std::list<int> vertices;
    std::map<int, std::list<int>> adj;
    
};

// Create a list of the vertices with zero-in-degree
// Add vertices which have zero in-degree to the list.
// If there are none, it is a cycle.


// return the ID of the vertices
std::map<int, int> getIndegree(graph g) {
    std::map<int, int> id;
    
    // Build the indegree of the vertices
    for (auto &i : g.adj) {
        if (id.find(i.first) != id.end()) {
            id.insert(std::pair<int, int>(i.first, i.second.size()));
        }
    }
    return id;
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
    while (v < size) {
        list<int> order;
        
        order = buildListWithZeroIndegree(g);
        
        if (!order) {
            // cycle detected here. no nodes with ZID
            return list();
        }
        
        orderedList += order;
        
        for (auto &v : order) {
            // Remove these dependencies from the graph
            for (auto &list : g.adj) {
                if (list.find(v) != list.end()) {
                    // decrement the dependencies;
                    list.erase(v);
                }
                if (!list.size()) {
                    // remove the entry.
                    g.adj.remove(v);
                }
            }
        }
        
        v += order.size();
    }
}


