//aseelzatmy3@gmail.com 324885417

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
using namespace std;
namespace ariel{
class Graph{
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        size_t numOfVertices;
        int numOfEdges;
    public:
        Graph();
        bool hasEdge(int from, int to) const; // Method to check if there is an edge between two vertices
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        std::string printGraph();
        size_t getNumVertices();
        int getNumEdges();
        vector<vector<int>> getGraph();

        // Overload the addition operator (+)
        Graph operator+(const Graph& other) const;

        // Overload the addition assignment operator (+=)
        Graph& operator+=(const Graph& other);

        // Overload the unary plus operator (+)
        Graph operator+() const;

        // Overload the subtraction operator (-)
        Graph operator-(const Graph& other) const;

        // Overload the subtraction assignment operator (-=)
        Graph& operator-=(const Graph& other);

        // Overload the unary negation operator (-)
        Graph operator-() const;

        // Overload the equality operator (==)
        bool operator==(const Graph& other) const;

       // Overload the inequality operator (!=)
        bool operator!=(const Graph& other) const;

        // Overload the greater than operator (>)
        bool operator>(const Graph& other) const;

        // Overload the less than operator (<)
        bool operator<(const Graph& other) const;

        // Overload the greater than or equal to operator (>=)
        bool operator>=(const Graph& other) const;

        // Overload the less than or equal to operator (<=)
        bool operator<=(const Graph& other) const;

        // Helper function to determine if one graph is contained in another
        bool isContainedIn(const Graph& other) const;

        // Prefix increment operator
        Graph& operator++(); 

        // Postfix increment operator
        Graph operator++(int); 

        // Prefix decrement operator
        Graph& operator--(); 

        // Postfix decrement operator
        Graph operator--(int);

         // Multiply the graph by an integer scalar
        Graph operator*(int scalar) const;

        // Multiply two graphs together
        Graph operator*(const Graph& other) const;

        Graph& operator*=(int scalar);
        Graph& operator/=(int scalar);

        // Define the output operator outside the class declaration
        friend std::ostream& operator<<(std::ostream& os, Graph& graph);

};
}
#endif //GRAPH_H