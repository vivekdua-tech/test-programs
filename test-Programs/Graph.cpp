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

// Implement Topological Sort - Order the project/process dependencies and launch accordingly

using namespace std;

class graph {

public:
    
    std::list<int> _vertices;
    // Adjacency : {{A : B, C}} B->A and C->A
    std::map<int, std::list<int>> _adj;
    
    graph(std::list<int>& vertices, std::map<int, std::list<int>>& adj) :
    _vertices(vertices), _adj(adj) {}
    
    void getIndegree(std::map<int, int> &id);
    std::list<int> buildListWithZeroIndegree();
    std::list<int> orderVertices1 ();
    std::list<int> orderVertices2 ();
    
};


// Create a list of the vertices with zero-in-degree
// Add vertices which have zero in-degree to the list.
// If there are none, it is a cycle.


// return the ID of the vertices
void graph::getIndegree(std::map<int, int> &id) {
    
    // Build the indegree of the vertices
    for (auto &adj : this->_adj) {
        list<int> adjList = adj.second;
        if (id.find(adj.first) == id.end()) {
            id.insert(pair<int, int>(adj.first, 0));
        }
        id[adj.first] += adjList.size();
     }
    return;
}


std::list<int> graph::buildListWithZeroIndegree() {
    std::list<int> zigList;
    
    for (auto &v : this->_vertices) {
        // If the vertices does not exist in the map; it is ZID
        if (this->_adj.find(v) == this->_adj.end()) {
            zigList.push_back(v);
        }
    }
    return zigList;
}
                      
std::list<int> graph::orderVertices1 () {
    // Iterate through all the vertices
    // Add the ZID vertices to the ordered vector
    // Remove the dependencies of the ZID vertices from the map
    // Add the ZID vertices again
    // Anytime if the ZID vertices return no more nodes but still vertices left to be traversed - cyclcic graph.
    
    list<int> orderedList;
    int v = 0;
    size_t size = this->_vertices.size();
    orderedList = this->buildListWithZeroIndegree();
    list<int> order = orderedList;
    map<int, int> idegMap;
    this->getIndegree(idegMap);
    
    
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
            for (auto &adj : this->_adj) {
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

//    3--->4--->5--->6
//    2--->4--->7---->6
//    1--->6
//    Create a ordered List for ZID vertices - processOrder.
//    Create a ordered List for publishing the order - publishOrder.
//    Get the IDIG map for all vertices
//    1. Get the ZID vertices and publish in processOrder and publishOrder.
//    2. Iterate over the processOrder list till we have empty processOrder list
//           2.a For every ZID, iterate over the graph and reduce the IDIG by one for every vertices
//               which depend on this ZID.
//           2.b If IDIG becomes zero for the current node, add it to processOrder and publishOrder.
//           2.c Remove ths current ZID node from the processOrder List.
//    3. we have a cycle if the publishOrder size is less than the vertices size in the graph.

std::list<int> graph::orderVertices2 () {
    list<int> processOrder = this->buildListWithZeroIndegree();
    list<int> publishOrder = processOrder;
    map<int, int> idegMap;
    size_t size = this->_vertices.size();
    this->getIndegree(idegMap);
    int v = 0;
    while (v < size) {
        if (!processOrder.size()) {
            // cycle
            cout << "cycle detected" << endl;
            return list<int>();
        }
        int prevzid = 0;
        for (auto zid : processOrder) {
            processOrder.remove(prevzid);
            for (auto &adj : this->_adj) {
                int node = adj.first;
                list<int> adjList = adj.second;
                for (auto dep : adjList) {
                    if (dep == zid) {
                        if (--idegMap[node] == 0) {
                            processOrder.push_back(node);
                            publishOrder.push_back(node);
                        }
                    }
                }
            }
            v++;
            prevzid = zid;
        }
    }
    return publishOrder;
}

// BFS on G(V, E) BFS explores edges of G to discover every vertex
//    that is reachable from s. It computes the distance from s
//    to each reachable vertex. Also calculates shortest-distance from s.
//    It also produces a BFS tree with root s that contains all reachable
//    vertexes. G can be directed or undirected - There could be even cycles
//    in the graph G. Time complexity is O(V + E)
//
//    BFS(G, s)
//        for each vertex u in G.V - {s} // for every vertex u in G except s.
//            u.color = WHITE
//            u.d = -1
//            u.pi = NULL
//        s.d = 0
//        s.pi = NULL
//        s.color = GRAY  // all vertezes enqueued are marked gray.
//        Q = 0
//        Enqueue(Q, s)
//        while Q not empty
//            u = dequeue(Q)
//            for each v in G.adj[u]
//                if v.color = WHITE
//                    v.color = GRAY
//                    v.d = u.d + 1
//                    v.pi = u
//                    Enqueue(Q, v)
//            u.color = BLACK // done processing in the Q

// DFS on G(V, E) DFS explores edges of G in depth first fashion - explores the descendants of the
//    current vertex till it last descendant and then get to the next edge of the current vertex.
//    Time complexity is O(V + E).
//
//    DFS (G)
//       for each vertex u in G.V
//           u.color = WHITE // not yet explored in DFS fashion
//           u.pi = NULL
//      time = 0
//      for each vertex u in G.V
//           if u.color = WHITE
//           DFS-VISIT(G, u)    // DFS from this vertex
//
//    DFS-VISIT(G, u)
//        time = time + 1
//        u.d = time  // start time of this node
//        u.color = GRAY
//        for each v in G.Adj[u]
//            if v.color = WHITE
//                v.pi = u           // DFS path from u to v exists.
//                DFS-VISIT(G, v)
//        u.color = BLACK // done processing - u is now part of the DFS forest
//        time = time + 1
//        u.f = time + 1   // finish time of this node


// Topological Sort - Alternative approach
//     Call DFG(G) to compute finish times v.f for each vertex v
//     as each vertex is finished, insert it to the front of the linked list
//     return the linked list of the vertices


// Implement Dijecstra's Algorithm using Priority-Q

vector<pair<int,int> > a[sz]; //Adjacency list
int dis[sz]; //Stores shortest distance
bool vis[sz]={0}; //Determines whether the node has been visited or not

void Dijkstra(int source, int n) //Algorithm for SSSP
{
    for(int i=0;i<sz;i++) //Set initial distances to Infinity
        dis[i]=INF;
    //Custom Comparator for Determining priority for priority queue (shortest edge comes first)
    class prioritize{public: bool operator ()(pair<int, int>&p1 ,pair<int, int>&p2){return p1.second>p2.second;}};
    priority_queue<pair<int,int> ,vector<pair<int,int> >, prioritize> pq; //Priority queue to store vertex,weight pairs
    pq.push(make_pair(source,dis[source]=0)); //Pushing the source with distance from itself as 0
    while(!pq.empty())
    {
        pair<int, int> curr=pq.top(); //Current vertex. The shortest distance for this has been found
        pq.pop();
        int cv=curr.first,cw=curr.second; //'cw' the final shortest distance for this vertex
        if(vis[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
            continue;
        vis[cv]=true;
        for(int i=0;i<a[cv].size();i++) //Iterating through all adjacent vertices
            if(!vis[a[cv][i].first] && a[cv][i].second+cw<dis[a[cv][i].first]) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
                pq.push(make_pair(a[cv][i].first,(dis[a[cv][i].first]=a[cv][i].second+cw))); //Set the new distance and add to priority queue
    }
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
    
    graph g(vertices, adj);
   
    // Order the vertices
    list<int> orderedVert1 = g.orderVertices1();
    cout << "Order is " << endl;
    for (auto &v : orderedVert1) {
        cout << v << " ";
    }
    list<int> orderedVert2 = g.orderVertices1();
    cout << "Order is " << endl;
    for (auto &v : orderedVert2) {
        cout << v << " ";
    }
}
