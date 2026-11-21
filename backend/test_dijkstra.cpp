#include <iostream>

#include "graph/Graph.h"
#include "routing/Dijkstra.h"

int main()
{
    Graph graph;

    int a =
        graph.addNode(
            1,
            -7.2900,
            112.7500);

    int b =
        graph.addNode(
            2,
            -7.2910,
            112.7510);

    int c =
        graph.addNode(
            3,
            -7.2920,
            112.7520);

    graph.addEdge(
        a,
        b,
        10);

    graph.addEdge(
        b,
        c,
        15);

    graph.addEdge(
        a,
        c,
        40);

    Dijkstra dijkstra;

    PathResult result =
        dijkstra.shortestPath(
            graph,
            a,
            c);

    if (!result.found)
    {
        std::cout
            << "No path\n";

        return 0;
    }

    std::cout
        << "Distance : "
        << result.distance
        << "\n";

    std::cout
        << "Visited : "
        << result.visitedNodes
        << "\n";

    std::cout
        << "Execution : "
        << result.executionMs
        << " ms\n";

    std::cout
        << "Path : ";

    for (int node : result.path)
    {
        std::cout
            << node
            << " ";
    }

    std::cout
        << "\n";
}