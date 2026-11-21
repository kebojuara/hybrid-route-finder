#include <iostream>

#include "osm/OSMParser.h"
#include "spatial/KDTree.h"

int main()
{
    Graph graph;

    OSMParser parser;

    if (
        !parser.parse(
            "../data/surabaya.osm",
            graph))
    {
        return 1;
    }

    KDTree tree;

    tree.build(graph);

    double lat =
        -7.27950;

    double lon =
        112.79000;

    int nearest =
        tree.nearestNode(
            lat,
            lon,
            graph);

    const Node& node =
        graph.getNode(nearest);

    std::cout
        << "\nInput Coordinate\n";

    std::cout
        << lat
        << ", "
        << lon
        << "\n";

    std::cout
        << "\nNearest Node\n";

    std::cout
        << "Graph Index : "
        << nearest
        << "\n";

    std::cout
        << "OSM ID      : "
        << node.osmId
        << "\n";

    std::cout
        << "Lat         : "
        << node.lat
        << "\n";

    std::cout
        << "Lon         : "
        << node.lon
        << "\n";
}