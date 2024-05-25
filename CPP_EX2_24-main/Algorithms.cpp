//aseelzatmy3@gmail.com 324885417
#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <limits>
#include <sstream>

namespace ariel {
//==============================================================================================================================================
bool Algorithms::hasPathDFS( Graph graph, int src, int dest, std::unordered_set<int>& visited) {
        // Base case: If source and destination are the same
        if (src == dest) {
            return true;
        }

        // Mark the current node as visited
        visited.insert(src);

        // Recursively check if there is a path from the current node to the destination
        size_t s=graph.getNumVertices();
        for (std::vector<int>::size_type i = 0; i < s; ++i) {
            if (graph.hasEdge(src, i) && visited.find(i) == visited.end()) {
                if (hasPathDFS(graph, i, dest, visited)) {
                    return true;
                }
            }
        }

        // If no path found
        return false;
    }

    bool Algorithms::hasPath(Graph graph, int src, int dest) { // Definition
        std::unordered_set<int> visited;
        return hasPathDFS(graph, src, dest, visited);
    }
 bool Algorithms::isConnected(Graph g) {
        int numVertices = g.getNumVertices();
        // Check if there is a path between every pair of vertices
        for (int src = 0; src < numVertices; ++src) {
            for (int dest = 0; dest < numVertices; ++dest) {
                if (src != dest && !hasPath(g, src, dest)) {
                    return false; // If there is no path between any pair of vertices, graph is not connected
                }
            }
        }
        return true; // If there is a path between every pair of vertices, graph is connected
    }
//==============================================================================================================================================
bool Algorithms::dfs(Graph graph, unsigned long node, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cycle_path) {
    visited[node] = true;

    for (size_t neighbor = 0; neighbor < graph.getNumVertices(); ++neighbor) {
        if (graph.hasEdge(node, neighbor)) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                if (dfs(graph, neighbor, visited, parent, cycle_path))
                    return true;
            } else if (neighbor != static_cast<size_t>(parent[node]) && parent[node] != -1) { // Found a cycle
                cycle_path.push_back(static_cast<int>(neighbor));
                unsigned long current = node;
                while (current != neighbor) {
                    cycle_path.push_back(current);
                    current = static_cast<unsigned long>(parent[current]); // Backtrack to find the cycle
                }
                cycle_path.push_back(static_cast<int>(neighbor)); // Closing the cycle
                return true;
            }
        }
    }
    return false;
}
//with printing the cycle
//  bool Algorithms::isContainsCycle(Graph graph) {
//     size_t num_vertices = graph.getNumVertices();
//     std::vector<bool> visited(num_vertices, false);
//     std::vector<int> parent(num_vertices, -1);
//     std::vector<int> cycle_path;

//     for (unsigned int node = 0; node < num_vertices; ++node) {
//         if (!visited[node] && dfs(graph, node, visited, parent, cycle_path)) {
//             // Print the cycle path
//             std::cout << "Cycle found ~1~ : ";
//             std::reverse(cycle_path.begin(), cycle_path.end()); // Reverse the cycle path
//             for (int node : cycle_path) {
//                 std::cout << node << " ";
//             }
//             std::cout << std::endl;
//             return true; // Cycle found
//         }
//     }
//     std::cout << "No cycle found ~0~ ." << std::endl;
//     return false; // No cycle found
// }
bool Algorithms::isContainsCycle(Graph graph) {
    size_t num_vertices = graph.getNumVertices();
    std::vector<bool> visited(num_vertices, false);
    std::vector<int> parent(num_vertices, -1);
    std::vector<int> cycle_path;

    for (unsigned int node = 0; node < num_vertices; ++node) {
        if (!visited[node] && dfs(graph, node, visited, parent, cycle_path)) {
            std::reverse(cycle_path.begin(), cycle_path.end()); // Reverse the cycle path
            return true; // Cycle found
        }
    }
    return false; // No cycle found
}
//==============================================================================================================================================
std::string Algorithms::shortestPath(Graph g, int start, int end) {
    // Get the adjacency matrix of the graph
    std::vector<std::vector<int>> adjacencyMatrix = g.getGraph();
    
    // Number of vertices in the graph
    size_t n = g.getNumVertices(); // Convert to size_t

    // Initialize distances array with infinity and parents array with -1
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);

    // Distance from source to itself is 0
    dist[static_cast<size_t>(start)] = 0; // Convert to size_t

    // Priority queue to store vertices based on distance
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    // Push source vertex into the priority queue
    pq.push(std::make_pair(0, start));

    // Dijkstra's algorithm
    while (!pq.empty()) {
        // Extract the vertex with minimum distance
        int u = pq.top().second;
        pq.pop();

        visited[static_cast<size_t>(u)] = true; // Convert to size_t
        if (u == end) {
            std::string path = std::to_string(end);
            while (parent[static_cast<size_t>(end)] != -1) { // Convert to size_t
                path = std::to_string(parent[static_cast<size_t>(end)]) + " -> " + path; // Convert to size_t
                end = parent[static_cast<size_t>(end)]; // Convert to size_t
            }
            return path;
        }
        
        // Iterate over all adjacent vertices of u
        for (size_t v = 0; v < n; ++v) {
            // If there is an edge from u to v and v is not visited
            if (adjacencyMatrix[static_cast<size_t>(u)][v] != 0 && !visited[v]) {
                // Update distance of v
                int newdes = dist[static_cast<size_t>(u)] + adjacencyMatrix[static_cast<size_t>(u)][v];
                if (newdes < dist[v]) {
                    dist[v] = newdes;
                    // Set u as parent of v
                    parent[v] = u;
                    // Push v into the priority queue
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }

    return "-1";
}


//==============================================================================================================================================
std::string Algorithms::isBipartite(Graph g) {
    std::vector<std::vector<int>> adjacencyMatrix = g.getGraph();
    size_t n = g.getNumVertices();

    std::vector<int> color(n, -1);
    std::queue<int> q;
    
    for (size_t i = 0; i < n; ++i) {
        if (color[i] == -1) {
            q.push(static_cast<int>(i)); 
            color[i] = 0;
            
            while (!q.empty()) {
                size_t u = static_cast<size_t>(q.front());
                q.pop();
                
                for (size_t v = 0; v < n; ++v) {
                    if (adjacencyMatrix[u][v] != 0) { 
                        if (color[v] == -1) { 
                            color[v] = 1 - color[u]; 
                            q.push(static_cast<int>(v)); 
                        } else if (color[v] == color[u]) { 
                            return "0"; // Not bipartite
                        }
                    }
                }
            }
        }
    }

    // Separate vertices into sets based on their color
    std::vector<int> setU, setV;
    for (size_t i = 0; i < n; ++i) {
        if (color[i] == 0) {
            setU.push_back(static_cast<int>(i)); // Convert to int
        } else {
            setV.push_back(static_cast<int>(i)); // Convert to int
        }
    }

    // Convert the sets to string representations
    std::string groupA = "{";
    for (int vertex : setU) {
        groupA += std::to_string(vertex) + ", ";
    }
    if (!groupA.empty()) {
        groupA.pop_back(); // Remove the extra comma
        groupA.pop_back(); // Remove the extra space
    }
    groupA += "}";

    std::string groupB = "{";
    for (int vertex : setV) {
        groupB += std::to_string(vertex) + ", ";
    }
    if (!groupB.empty()) {
        groupB.pop_back(); // Remove the extra comma
        groupB.pop_back(); // Remove the extra space
    }
    groupB += "}";

    return "The graph is bipartite: A=" + groupA + ", B=" + groupB;
}

//==============================================================================================================================================
    bool Algorithms::negativeCycle(Graph g) {
        std::vector<std::vector<int>> adjacencyMatrix = g.getGraph();
            size_t n = g.getNumVertices();

            // Initialize distances to all vertices as infinite
            std::vector<int> dist(n, std::numeric_limits<int>::max());

            // Set distance to source vertex as 0
            dist[0] = 0;

            // Relax all edges |V| - 1 times
            for (size_t i = 0; i < n - 1; ++i) {
                for (size_t u = 0; u < n; ++u) {
                    for (size_t v = 0; v < n; ++v) {
                        if (adjacencyMatrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                            dist[v] = dist[u] + adjacencyMatrix[u][v];
                        }
                    }
                }
            }

            // Check for negative cycles
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (adjacencyMatrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                        return true; // Negative cycle detected
                    }
                }
            }

            return false; // No negative cycle found
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}