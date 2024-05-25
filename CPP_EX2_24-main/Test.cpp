#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
//aseelzatmy3@gmail.com 324885417
using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    CHECK(ariel::Algorithms::shortestPath(g3, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g3)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g3)==true);
    CHECK(ariel::Algorithms::negativeCycle(g3)==false);
    CHECK(ariel::Algorithms::isBipartite(g3) == "0");

     // Test addition operator (+) with different sizes
        ariel::Graph g4;
        vector<vector<int>> graph4 = {
            {0, 1},
            {1, 0}
        };
        g4.loadGraph(graph4);

        ariel::Graph g5;
        vector<vector<int>> graph5 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g5.loadGraph(graph5);

        CHECK_THROWS_AS(g4 + g5, std::invalid_argument);

}

TEST_CASE("Test graph += ")
{
// Test addition assignment operator (+=) with different sizes
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1},
            {1, 0}
        };
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g2.loadGraph(graph2);

        CHECK_THROWS_AS(g1 += g2, std::invalid_argument);
        ariel::Graph g3;
        vector<vector<int>> graph3 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
        };
        g3.loadGraph(graph3);

        ariel::Graph g4;
        vector<vector<int>> graph4 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g4.loadGraph(graph4);

        g3 += g4;

        CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
        CHECK(ariel::Algorithms::shortestPath(g3, 0, 2) == "0 -> 2");
        CHECK(ariel::Algorithms::isConnected(g3)==true);
        CHECK(ariel::Algorithms::isContainsCycle(g3)==true);
        CHECK(ariel::Algorithms::negativeCycle(g3)==false);
        CHECK(ariel::Algorithms::isBipartite(g3) == "0");
}

TEST_CASE(" Test subtraction operator (-)")
{
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}
        };
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g2.loadGraph(graph2);

        ariel::Graph g3 = g1 - g2;
        CHECK(g3.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

        // Test subtraction assignment operator (-=)
        ariel::Graph g4;
        vector<vector<int>> graph4 = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}
        };
        g4.loadGraph(graph4);

        ariel::Graph g5;
        vector<vector<int>> graph5 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g5.loadGraph(graph5);

        g4 -= g5;

        CHECK(g4.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
        CHECK(ariel::Algorithms::shortestPath(g4, 0, 2) == "0 -> 1 -> 2");
        CHECK(ariel::Algorithms::isConnected(g4)==true);
        CHECK(ariel::Algorithms::isContainsCycle(g4)==false);
        CHECK(ariel::Algorithms::negativeCycle(g4)==false);
        CHECK(ariel::Algorithms::isBipartite(g4) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test equality operator (==)")
{
    ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
        };
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}
        };
        g2.loadGraph(graph2);

        CHECK(g1 == g2);

        vector<vector<int>> graph3 = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}
        };
        g2.loadGraph(graph3);

        CHECK_FALSE(g1 == g2);

        // Test addition assignment operator (==) with different sizes
        ariel::Graph g4;
        vector<vector<int>> graph4 = {
            {0, 1},
            {1, 0}
        };
        g4.loadGraph(graph4);

        ariel::Graph g5;
        vector<vector<int>> graph5 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g5.loadGraph(graph5);

        CHECK_FALSE(g4 == g5);
}

TEST_CASE("Test unary negation operator (-)")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, -1},
        {-2, 0, 3},
        {1, -3, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2 = -g1; // Use the unary negation operator
    CHECK(g2.printGraph() == "[0, -2, 1]\n[2, 0, -3]\n[-1, 3, 0]");
    CHECK(ariel::Algorithms::shortestPath(g2, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isConnected(g2)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g2)==true);
    CHECK(ariel::Algorithms::negativeCycle(g2)==true);
    CHECK(ariel::Algorithms::isBipartite(g2) == "0");
    

    //Test unary negation operator (-) with zero matrix
     ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g3.loadGraph(graph3);

    ariel::Graph g4 = -g3; // Use the unary negation operator
    CHECK(g4.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");

    //Test unary negation operator (-) with positive matrix
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    g5.loadGraph(graph5);

    ariel::Graph g6 = -g5; // Use the unary negation operator
    CHECK(g6.printGraph() == "[-1, -2, -3]\n[-4, -5, -6]\n[-7, -8, -9]");

    //Test unary negation operator (-) with negative matrix
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {-1, -2, -3},
        {-4, -5, -6},
        {-7, -8, -9}
    };
    g7.loadGraph(graph7);

    ariel::Graph g8 = -g7; // Use the unary negation operator
    CHECK(g8.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");

}

TEST_CASE("Not equal graphs") {
    ariel::Graph g1;
    ariel::Graph g2;
    ariel::Graph g3;

    // Load graphs
    std::vector<std::vector<int>> graph1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph1);

    std::vector<std::vector<int>> graph2 = {{0, 1, 1}, {1, 0, 0}, {1, 0, 0}};
    g2.loadGraph(graph2);

    std::vector<std::vector<int>> graph3 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g3.loadGraph(graph3);

        CHECK(g1 != g2);
        CHECK(g2 != g1);
        CHECK_FALSE(g1 == g2);
        CHECK_FALSE(g2 == g1);
        CHECK_FALSE(g1 != g3);
        CHECK_FALSE(g3 != g1);
        CHECK(g1 == g3);
        CHECK(g3 == g1);
}

TEST_CASE("Graph isContainedIn function") {
    ariel::Graph g1;
    std::vector<std::vector<int>> matrix1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(matrix1);

    ariel::Graph g2;
    std::vector<std::vector<int>> matrix2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g2.loadGraph(matrix2);

    ariel::Graph g3;
    std::vector<std::vector<int>> matrix3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(matrix3);

    SUBCASE("g1 is contained in g2") {
        CHECK(g1.isContainedIn(g2) == true);
    }

    SUBCASE("g2 is not contained in g1") {
        CHECK(g2.isContainedIn(g1) == false);
    }

    SUBCASE("g3 is contained in g1") {
        CHECK(g3.isContainedIn(g1) == true);
    }

    SUBCASE("g1 is not contained in g3") {
        CHECK(g1.isContainedIn(g3) == false);
    }

    SUBCASE("g3 is  contained in g2 ") {
        CHECK(g3.isContainedIn(g2) == true);
    }

    SUBCASE("g3 is not contained in g4 ") {
        ariel::Graph g4;
        std::vector<std::vector<int>> matrix4 = {
            {0, 0, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}
        };
        g4.loadGraph(matrix4);
        CHECK(g3.isContainedIn(g4) == false);
    }
}
TEST_CASE("Test greater than operator (>)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g4.loadGraph(graph4);

    // Test > operator
    CHECK(g2 > g1); // g2 has more edges than g1
    CHECK_FALSE(g1 > g2); // g1 does not have more edges than g2
    CHECK(g1 > g3); // g1 has more edges and vertices than g3
    CHECK_FALSE(g3 > g1); // g3 does not have more edges and vertices than g1
    CHECK(g1 > g4); // g1 has more edges than an empty graph
    CHECK_FALSE(g4 > g1); // an empty graph does not have more edges than g1
}
TEST_CASE("Test greater-than-or-equal operator (>=)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g4.loadGraph(graph4);

    // Test >= operator
    CHECK(g2 >= g1); // g2 has more edges than g1
    CHECK(g1 >= g1); // g1 is equal to g1
    CHECK_FALSE(g1 >= g2); // g1 does not have more edges than g2
    CHECK(g1 >= g3); // g1 has more edges and vertices than g3
    CHECK_FALSE(g3 >= g1); // g3 does not have more edges and vertices than g1
    CHECK(g1 >= g4); // g1 has more edges than an empty graph
    CHECK_FALSE(g4 >= g1); // an empty graph does not have more edges than g1
}

TEST_CASE("Test less-than-or-equal operator (<=)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g4.loadGraph(graph4);

    // Test <= operator
    CHECK(g1 <= g2); // g1 has fewer edges than g2
    CHECK(g1 <= g1); // g1 is equal to g1
    CHECK_FALSE(g2 <= g1); // g2 does not have fewer edges than g1
    CHECK(g3 <= g1); // g3 has fewer edges and vertices than g1
    CHECK_FALSE(g1 <= g3); // g1 does not have fewer edges and vertices than g3
    CHECK(g4 <= g1); // an empty graph has fewer edges than g1
    CHECK_FALSE(g1 <= g4); // g1 does not have fewer edges than an empty graph
}
TEST_CASE("Test less-than operator (<)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(graph2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g4.loadGraph(graph4);

    // Test < operator
    CHECK(g1 < g2); // g1 has fewer vertices and edges than g2
    CHECK_FALSE(g2 < g1); // g2 does not have fewer vertices and edges than g1
    CHECK(g3 < g1); // g3 has fewer vertices and edges than g1
    CHECK_FALSE(g1 < g3); // g1 does not have fewer vertices and edges than g3
    CHECK(g4 < g1); // an empty graph has fewer vertices and edges than g1
    CHECK_FALSE(g1 < g4); // g1 does not have fewer vertices and edges than an empty graph
}
TEST_CASE("Test prefix increment operator (++)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ++g1;

    vector<vector<int>> expected = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };

    CHECK(g1.getGraph() == expected);
    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==true);
    CHECK(ariel::Algorithms::negativeCycle(g1)==false);
    CHECK(ariel::Algorithms::isBipartite(g1) == "0");
}

TEST_CASE("Test postfix increment operator (++)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2 = g1++;

    vector<vector<int>> expected1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    vector<vector<int>> expected2 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };

    CHECK(g2.getGraph() == expected1); // g2 should have the original graph
    CHECK(g1.getGraph() == expected2); // g1 should have the incremented graph

    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==true);
    CHECK(ariel::Algorithms::negativeCycle(g1)==false);
    CHECK(ariel::Algorithms::isBipartite(g1) == "0");
}
TEST_CASE("Test prefix decrement operator (--)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };
    g1.loadGraph(graph1);

    --g1;

    vector<vector<int>> expected = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    CHECK(g1.getGraph() == expected);
    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==false);
    CHECK(ariel::Algorithms::negativeCycle(g1)==false);
    CHECK(ariel::Algorithms::isBipartite(g1) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test postfix decrement operator (--)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2 = g1--;

    vector<vector<int>> expected1 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}
    };

    vector<vector<int>> expected2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    CHECK(g2.getGraph() == expected1); // g2 should have the original graph
    CHECK(g1.getGraph() == expected2); // g1 should have the decremented graph
    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==false);
    CHECK(ariel::Algorithms::negativeCycle(g1)==false);
    CHECK(ariel::Algorithms::isBipartite(g1) == "The graph is bipartite: A={0, 2}, B={1}");
}
TEST_CASE("Test multiplication by integer scalar (*)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2 = g1 * 2;

    vector<vector<int>> expected = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}
    };

    CHECK(g2.getGraph() == expected);
    CHECK(ariel::Algorithms::shortestPath(g2, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isConnected(g2)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g2)==false);
    CHECK(ariel::Algorithms::negativeCycle(g2)==false);
    CHECK(ariel::Algorithms::isBipartite(g2) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test graph multiplication (*)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2 = g1 * g1;

    vector<vector<int>> expected = {
        {1, 0, 1},
        {0, 2, 0},
        {1, 0, 1}
    };

    CHECK(g2.getGraph() == expected);

    CHECK(ariel::Algorithms::shortestPath(g2, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g2)==false);
    CHECK(ariel::Algorithms::isContainsCycle(g2)==true);
    CHECK(ariel::Algorithms::negativeCycle(g2)==false);
    CHECK(ariel::Algorithms::isBipartite(g2) == "0");
}

TEST_CASE("Test graph multiplication with different sizes (*)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 0}
    };
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 * g2);
}
TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");

    CHECK(ariel::Algorithms::shortestPath(g2, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g2)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g2)==true);
    CHECK(ariel::Algorithms::negativeCycle(g2)==false);
    CHECK(ariel::Algorithms::isBipartite(g2) == "0");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Graph scalar multiplication") {
    ariel::Graph g1;
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    g1.loadGraph(graph1);

    g1 *= -2; // Multiply the graph by -2

    std::vector<std::vector<int>> expectedGraph = {
        {0, -2, -4},
        {-2, 0, -6},
        {-4, -6, 0}
    };

    CHECK(g1.getGraph() == expectedGraph);

    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==true);
    CHECK(ariel::Algorithms::negativeCycle(g1)==true);
    CHECK(ariel::Algorithms::isBipartite(g1) == "0");
}
TEST_CASE("Graph scalar division") {
    ariel::Graph g1;
    std::vector<std::vector<int>> graph1 = {
        {0, 2, 4},
        {2, 0, 6},
        {4, 6, 0}
    };
    g1.loadGraph(graph1);

    g1 /= 2; // Divide the graph by 2

    std::vector<std::vector<int>> expectedGraph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };

    CHECK(g1.getGraph() == expectedGraph);

    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isConnected(g1)==true);
    CHECK(ariel::Algorithms::isContainsCycle(g1)==true);
    CHECK(ariel::Algorithms::negativeCycle(g1)==false);
    CHECK(ariel::Algorithms::isBipartite(g1) == "0");

    // Test division by zero
    CHECK_THROWS_AS(g1 /= 0, std::invalid_argument);
}