#include <iostream>

#include "osm/OSMParser.h"
#include "routing/Dijkstra.h"
#include "routing/AStar.h"

int main()
{
    Graph graph;

    OSMParser parser;

    parser.parse(
        "../data/surabaya.osm",
        graph);

    int start = -1;
    int goal = -1;

    for (int i = 0; i < graph.nodeCount(); i++)
    {
        if (!graph.getNeighbors(i).empty())
        {
            if (start == -1)
            {
                start = i;
            }

            goal = i;
        }
    }

    std::cout
        << "Start node: "
        << start
        << "\n";

    std::cout
        << "Goal node: "
        << goal
        << "\n";

        if (start == -1 || goal == -1)
        {
            std::cout
                << "No connected nodes found\n";

            return 1;
        }

    Dijkstra dijkstra;
    AStar astar;

    auto d =
        dijkstra.shortestPath(
            graph,
            start,
            goal);

    auto a =
        astar.shortestPath(
            graph,
            start,
            goal);

    std::cout
        << "\n=== DIJKSTRA ===\n";

    std::cout
        << "Distance: "
        << d.distance
        << "\n";

    std::cout
        << "Visited: "
        << d.visitedNodes
        << "\n";

    std::cout
        << "Time: "
        << d.executionMs
        << " ms\n";

    std::cout
        << "\n=== A* ===\n";

    std::cout
        << "Distance: "
        << a.distance
        << "\n";

    std::cout
        << "Visited: "
        << a.visitedNodes
        << "\n";

    std::cout
        << "Time: "
        << a.executionMs
        << " ms\n";

    std::cout
        << "Start neighbors: "
        << graph.getNeighbors(start).size()
        << "\n";

    std::cout
        << "Goal neighbors: "
        << graph.getNeighbors(goal).size()
        << "\n";

    std::cout
        << "Start OSM ID: "
        << graph.getNode(start).osmId
        << "\n";

    std::cout
        << "Goal OSM ID: "
        << graph.getNode(goal).osmId
        << "\n";

    std::cout
        << "Start Lat: "
        << graph.getNode(start).lat
        << "\n";

    std::cout
        << "Start Lon: "
        << graph.getNode(start).lon
        << "\n";

    std::cout
        << "Goal Lat: "
        << graph.getNode(goal).lat
        << "\n";

    std::cout
        << "Goal Lon: "
        << graph.getNode(goal).lon
        << "\n";
}