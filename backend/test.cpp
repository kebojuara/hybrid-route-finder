#include <iostream>

#include "graph/Graph.h"
#include "utils/GeoUtils.h"

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
            -7.2950,
            112.7550);

    double dist =
        GeoUtils::haversineDistance(
            -7.2900,
            112.7500,
            -7.2950,
            112.7550);

    graph.addEdge(
        a,
        b,
        dist);

    std::cout
        << "Nodes : "
        << graph.nodeCount()
        << std::endl;

    std::cout
        << "Edges : "
        << graph.edgeCount()
        << std::endl;

    std::cout
        << "Distance : "
        << dist
        << " meters"
        << std::endl;
}