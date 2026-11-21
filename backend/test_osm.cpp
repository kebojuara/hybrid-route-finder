#include <iostream>

#include "graph/Graph.h"
#include "osm/OSMParser.h"

int main()
{
    Graph graph;

    OSMParser parser;

    bool success =
        parser.parse(
            "../data/surabaya.osm",
            graph);

    if (!success)
    {
        std::cout
            << "Parse failed\n";

        return 1;
    }

    std::cout
        << "\n=== GRAPH SUMMARY ===\n";

    std::cout
        << "Nodes : "
        << graph.nodeCount()
        << "\n";

    std::cout
        << "Edges : "
        << graph.edgeCount()
        << "\n";

    return 0;
}