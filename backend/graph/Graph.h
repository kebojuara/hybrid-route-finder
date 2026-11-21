#pragma once

#include <vector>
#include <unordered_map>

#include "Node.h"
#include "Edge.h"

class Graph
{
private:

    std::unordered_map<long long, int> osmIdToIndex;

public:

    std::vector<Node> nodes;

    std::vector<std::vector<Edge>> adjacencyList;

    Graph();

    int addNode(
        long long osmId,
        double lat,
        double lon);

    void addEdge(
        int from,
        int to,
        double distance);

    bool containsNode(
        long long osmId) const;

    int getNodeIndex(
        long long osmId) const;

    const Node& getNode(
        int index) const;

    const std::vector<Node>& getNodes() const;

    const std::vector<Edge>& getNeighbors(
        int index) const;

    size_t nodeCount() const;

    size_t edgeCount() const;
};