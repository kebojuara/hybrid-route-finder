#pragma once

#include <vector>

#include "../graph/Graph.h"
#include "KDNode.h"

class KDTree
{
private:

    KDNode* root;

    KDNode* buildRecursive(
        std::vector<int>& indices,
        const Graph& graph,
        int depth);

    void nearestRecursive(
        KDNode* current,
        double targetLat,
        double targetLon,
        int depth,
        int& bestIndex,
        double& bestDistance,
        const Graph& graph);

public:

    KDTree();

    void build(
        const Graph& graph);

    int nearestNode(
        double lat,
        double lon,
        const Graph& graph);
};