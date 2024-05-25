//aseelzatmy3@gmail.com 324885417

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include "Graph.hpp"
#include <unordered_set>

namespace ariel {
    class Algorithms {
        public:
            static bool isConnected(Graph g);
            static bool hasPath(Graph graph, int src, int dest);
            static bool hasPathDFS( Graph graph, int src, int dest, std::unordered_set<int>& visited);

            static bool dfs(Graph graph, unsigned long node, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cycle_path);
            static bool isContainsCycle(Graph g); 

            static std::string shortestPath(Graph g, int start,int end);

            static std::string isBipartite(Graph g);
            static bool negativeCycle(Graph g); 

    };
}

#endif // ALGORITHMS_HPP