#include <iostream>

#include "graph/Graph.h"
#include "osm/OSMParser.h"
#include "spatial/KDTree.h"
#include "routing/AStar.h"

int main()
{
    Graph graph;

    OSMParser parser;

    if (!parser.parse(
            "../data/surabaya.osm",
            graph))
    {
        std::cout
            << "Failed to load OSM\n";

        return 1;
    }

    KDTree tree;

    tree.build(graph);

    //------------------------------------
    // Input Coordinates
    //------------------------------------

    double startLat =
        -7.27950;

    double startLon =
        112.79000;

    double endLat =
        -7.28250;

    double endLon =
        112.78650;

    //------------------------------------
    // Snap To Road
    //------------------------------------

    int startNode =
        tree.nearestNode(
            startLat,
            startLon,
            graph);

    int endNode =
        tree.nearestNode(
            endLat,
            endLon,
            graph);

    const Node& startRoad =
        graph.getNode(startNode);

    const Node& endRoad =
        graph.getNode(endNode);

    std::cout
        << "\n=== SNAP TO ROAD ===\n";

    std::cout
        << "Start Graph Node : "
        << startNode
        << "\n";

    std::cout
        << "Start OSM ID     : "
        << startRoad.osmId
        << "\n";

    std::cout
        << "Start Lat        : "
        << startRoad.lat
        << "\n";

    std::cout
        << "Start Lon        : "
        << startRoad.lon
        << "\n\n";

    std::cout
        << "End Graph Node   : "
        << endNode
        << "\n";

    std::cout
        << "End OSM ID       : "
        << endRoad.osmId
        << "\n";

    std::cout
        << "End Lat          : "
        << endRoad.lat
        << "\n";

    std::cout
        << "End Lon          : "
        << endRoad.lon
        << "\n";

    //------------------------------------
    // Routing
    //------------------------------------

    AStar astar;

    PathResult result =
        astar.shortestPath(
            graph,
            startNode,
            endNode);

    std::cout
        << "\n=== ROUTE RESULT ===\n";

    if (!result.found)
    {
        std::cout
            << "No route found\n";

        return 1;
    }

    std::cout
        << "Distance : "
        << result.distance
        << " meters\n";

    std::cout
        << "Visited  : "
        << result.visitedNodes
        << "\n";

    std::cout
        << "Time     : "
        << result.executionMs
        << " ms\n";

    std::cout
        << "Path Size: "
        << result.path.size()
        << "\n";

    //------------------------------------
    // Print Route
    //------------------------------------

    std::cout
        << "\n=== ROUTE NODES ===\n";

    for (size_t i = 0;
         i < result.path.size();
         i++)
    {
        const Node& n =
            graph.getNode(
                result.path[i]);

        std::cout
            << i
            << " : "
            << n.lat
            << ", "
            << n.lon
            << "\n";
    }

    return 0;
}