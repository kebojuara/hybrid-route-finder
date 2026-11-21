#include "Graph.h"

#include <stdexcept>

Graph::Graph()
{
}

int Graph::addNode(
    long long osmId,
    double lat,
    double lon)
{
    auto it = osmIdToIndex.find(osmId);

    if (it != osmIdToIndex.end())
    {
        return it->second;
    }

    int index = static_cast<int>(nodes.size());

    nodes.emplace_back(
        osmId,
        lat,
        lon);

    adjacencyList.emplace_back();

    osmIdToIndex[osmId] = index;

    return index;
}

void Graph::addEdge(
    int from,
    int to,
    double distance)
{
    adjacencyList[from].emplace_back(
        to,
        distance);
}

bool Graph::containsNode(
    long long osmId) const
{
    return osmIdToIndex.find(osmId)
        != osmIdToIndex.end();
}

int Graph::getNodeIndex(
    long long osmId) const
{
    auto it = osmIdToIndex.find(osmId);

    if (it == osmIdToIndex.end())
    {
        throw std::runtime_error(
            "Node not found");
    }

    return it->second;
}

const Node& Graph::getNode(
    int index) const
{
    return nodes[index];
}

const std::vector<Edge>& Graph::getNeighbors(
    int index) const
{
    return adjacencyList[index];
}

size_t Graph::nodeCount() const
{
    return nodes.size();
}

size_t Graph::edgeCount() const
{
    size_t count = 0;

    for (const auto& list : adjacencyList)
    {
        count += list.size();
    }

    return count;
}

const std::vector<Node>&
Graph::getNodes() const
{
    return nodes;
}