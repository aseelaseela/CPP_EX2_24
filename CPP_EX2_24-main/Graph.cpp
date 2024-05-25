//aseelzatmy3@gmail.com 324885417

#include <iostream>
#include <vector>
#include <sstream> 
#include <string> 

#include "Graph.hpp"

namespace ariel {

    Graph::Graph() : numOfEdges(0), numOfVertices(0), adjacencyMatrix() {}

    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix) {
        //check if the matrix is square
        size_t size_row= matrix.size(); //get the number of rows in the graph
        for (const auto& row : matrix) { // Iterate over each row in the graph
        if (row.size() != size_row) { // Check if the row size is not equal to the number of rows
            throw std::invalid_argument("Input graph is not a square matrix."); // Throw an exception if the graph is not square
        }
    } 
        numOfVertices = size_row;
        adjacencyMatrix = matrix;
        int numEdges = 0; // Initialize the number of edges to 0
        for (std::vector<std::vector<int>>::size_type i = 0; i < numOfVertices; ++i) { // Iterate over each row (or vertex)
        for (std::vector<int>::size_type j = 0; j < numOfVertices; ++j) { // Iterate over each column (or vertex)
            if (adjacencyMatrix[i][j] != 0) { // If there is an edge between vertex i and j
                ++numEdges; // Increment the number of edges
            }
        }      
    }
    numOfEdges=numEdges;
    }

    size_t Graph::getNumVertices(){
        return numOfVertices;
    }
    int Graph::getNumEdges(){
        return numOfEdges;
    }
    std::vector<std::vector<int>> Graph::getGraph() {
    return adjacencyMatrix;
    }
std::string Graph::printGraph() {
    std::stringstream ss;
    for (size_t i = 0; i < numOfVertices; ++i) {
        ss << "[";
        for (size_t j = 0; j < numOfVertices; ++j) {
            ss << adjacencyMatrix[i][j];
            if (j < numOfVertices - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        if (i < numOfVertices - 1) {
            ss << "\n";
        }
    }
    return ss.str();
}

bool Graph::hasEdge(int from, int to) const {
    if (from < 0 || from >= static_cast<int>(adjacencyMatrix.size()) || to < 0 || to >= static_cast<int>(adjacencyMatrix.size())) {
        // Invalid vertex indices
        return false;
    }
    return adjacencyMatrix[static_cast<std::vector<std::vector<int>>::size_type>(from)][static_cast<std::vector<std::vector<int>>::size_type>(to)] != 0;
}

// Overload the addition operator (+)
    Graph Graph::operator+(const Graph& other) const {
        if (numOfVertices != other.numOfVertices) {
            throw std::invalid_argument("Matrices must be of the same size for addition.");
        }

        Graph result;
        result.numOfVertices = numOfVertices;
        result.adjacencyMatrix.resize(numOfVertices, std::vector<int>(numOfVertices, 0)); // Initialize result matrix with zeros

        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }

        return result;
    }

// Overload the addition assignment operator (+=)
    Graph& Graph::operator+=(const Graph& other) {
        if (numOfVertices != other.numOfVertices) {
            throw std::invalid_argument("Matrices must be of the same size for addition.");
        }

        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

     // Overload the unary plus operator (+)
    Graph Graph::operator+() const {
        Graph result(*this); // Create a copy of the current graph
        return result;
    }

    // Overload the subtraction operator (-)
    Graph Graph::operator-(const Graph& other) const {
        if (numOfVertices != other.numOfVertices) {
            throw std::invalid_argument("Matrices must be of the same size for subtraction.");
        }
          Graph result;
        result.numOfVertices = numOfVertices;
        result.adjacencyMatrix.resize(numOfVertices, std::vector<int>(numOfVertices, 0)); // Initialize result matrix with zeros

        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }

        return result;
    }

    // Overload the subtraction assignment operator (-=)
    Graph& Graph::operator-=(const Graph& other) {
        if (numOfVertices != other.numOfVertices) {
            throw std::invalid_argument("Matrices must be of the same size for subtraction.");
        }

        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

     // Overload the unary negation operator (-)
    Graph Graph::operator-() const {
        Graph result;
        result.numOfVertices = numOfVertices;
        result.adjacencyMatrix.resize(numOfVertices, std::vector<int>(numOfVertices, 0));

        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                result.adjacencyMatrix[i][j] = -adjacencyMatrix[i][j];
            }
        }

        return result;
    }

    // Overload the equality operator (==)
    bool Graph::operator==(const Graph& other) const {
    // Check if the number of vertices is the same
    if (numOfVertices != other.numOfVertices) {
        return false;
    }

    // Check each element of the adjacency matrices
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            if (adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]) {
                return false; // If any element is different, matrices are not equal
            }
        }
    }

    // If all elements are the same, matrices are equal
    return true;
}

// Overload the inequality operator (!=)
bool Graph::operator!=(const Graph& other) const {
    return !(*this == other);
}

bool Graph::isContainedIn(const Graph& other) const {
    // If the current graph has more vertices than the other graph, it cannot be contained within it
    if (numOfVertices > other.numOfVertices) {
        return false;
    }

    // Check if all edges in the current graph are present in the other graph
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            // If there is an edge in the current graph that is not present in the other graph, return false
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]) {
                return false;
            }
        }
    }

    // If all edges are present, return true
    return true;
}
// Overload the greater-than operator (>) to compare two graphs
    bool Graph::operator>(const Graph& other) const {
        if (this->isContainedIn(other)) {
            return false; // Current graph is contained in the other, so it's not greater
        }

        if (other.isContainedIn(*this)) {
            return true; // Other graph is contained in the current, so it's greater
        }

        if (numOfEdges != other.numOfEdges) {
            return numOfEdges > other.numOfEdges; // Compare the number of edges
        }

        if (numOfEdges == other.numOfEdges && numOfVertices != other.numOfVertices) {
            return numOfVertices > other.numOfVertices; // Compare the number of edges
        }

        return false;
    }

    // Overload the less-than operator (<) to compare two graphs
    bool Graph::operator<(const Graph& other) const {
        return !(*this >= other); // Use the greater-than-or-equal operator
    }

    // Overload the greater-than-or-equal operator (>=)
    bool Graph::operator>=(const Graph& other) const {
        return *this > other || *this == other; // Check if greater or equal
    }

    // Overload the less-than-or-equal operator (<=)
    bool Graph::operator<=(const Graph& other) const {
        return *this < other || *this == other; // Check if less or equal
    }

    // Prefix increment operator
    Graph& Graph::operator++() {
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            ++adjacencyMatrix[i][j];
        }
    }
        return *this;
    }

    // Postfix increment operator
    Graph Graph::operator++(int) {
    Graph temp(*this); // Copy the current state
    ++(*this); // Use the prefix increment operator
    return temp; // Return the previous state
    }

    // Prefix decrement operator
    Graph& Graph::operator--() {
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            --adjacencyMatrix[i][j];
        }
    }
    return *this;
    }

    // Postfix decrement operator
    Graph Graph::operator--(int) {
    Graph temp(*this); // Copy the current state
    --(*this); // Use the prefix decrement operator
    return temp; // Return the previous state
    }

    // Multiply the graph by an integer scalar
    Graph Graph::operator*(int scalar) const {
    Graph result(*this); // Create a copy of the current graph

    // Multiply each edge weight by the scalar
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            result.adjacencyMatrix[i][j] *= scalar;
        }
    }

    return result;
}
    // Multiply two graphs together
    Graph Graph::operator*(const Graph& other) const {
        // Check if the graphs have the same size
        if (numOfVertices != other.numOfVertices) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        // Initialize the result graph
        Graph result(*this);
        // Perform matrix multiplication
        for (size_t i = 0; i < numOfVertices; ++i) {
            for (size_t j = 0; j < numOfVertices; ++j) {
                result.adjacencyMatrix[i][j]=0;
                for (size_t k = 0; k < numOfVertices; ++k) {
                    result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }      
            }
        }
        return result;
    }
     // Define the output operator
    std::ostream& operator<<(std::ostream& os, Graph& graph) {
        os << graph.printGraph(); // Use the printGraph() method to print the graph
        return os;
    }
    Graph& Graph::operator*=(int scalar) {
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            adjacencyMatrix[i][j] *= scalar;
        }
    }
    return *this;
    }
    Graph& Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    for (size_t i = 0; i < numOfVertices; ++i) {
        for (size_t j = 0; j < numOfVertices; ++j) {
            adjacencyMatrix[i][j] /= scalar;
        }
    }
    return *this;
}

   

}