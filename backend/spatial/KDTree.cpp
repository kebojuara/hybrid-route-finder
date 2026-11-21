#include "KDTree.h"

#include <algorithm>
#include <limits>

#include "../utils/GeoUtils.h"

KDTree::KDTree()
    :
    root(nullptr)
{
}

KDNode* KDTree::buildRecursive(
    std::vector<int>& indices,
    const Graph& graph,
    int depth)
{
    if (indices.empty())
    {
        return nullptr;
    }

    int axis =
        depth % 2;

    std::sort(
        indices.begin(),
        indices.end(),
        [&](int a, int b)
        {
            if (axis == 0)
            {
                return graph.getNode(a).lat
                    <
                    graph.getNode(b).lat;
            }

            return graph.getNode(a).lon
                <
                graph.getNode(b).lon;
        });

    int median =
        static_cast<int>(
            indices.size() / 2);

    int graphIndex =
        indices[median];

    const Node& node =
        graph.getNode(graphIndex);

    KDNode* current =
        new KDNode(
            graphIndex,
            node.lat,
            node.lon);

    std::vector<int> left(
        indices.begin(),
        indices.begin() + median);

    std::vector<int> right(
        indices.begin() + median + 1,
        indices.end());

    current->left =
        buildRecursive(
            left,
            graph,
            depth + 1);

    current->right =
        buildRecursive(
            right,
            graph,
            depth + 1);

    return current;
}

void KDTree::build(
    const Graph& graph)
{
    std::vector<int> indices;

    for (
        int i = 0;
        i < graph.nodeCount();
        i++)
    {
        indices.push_back(i);
    }

    root =
        buildRecursive(
            indices,
            graph,
            0);
}

void KDTree::nearestRecursive(
    KDNode* current,
    double targetLat,
    double targetLon,
    int depth,
    int& bestIndex,
    double& bestDistance,
    const Graph& graph)
{
    if (!current)
    {
        return;
    }

    double distance =
        GeoUtils::haversineDistance(
            targetLat,
            targetLon,
            current->lat,
            current->lon);

    if (distance < bestDistance)
    {
        bestDistance = distance;
        bestIndex = current->graphIndex;
    }

    int axis =
        depth % 2;

    double delta;

    if (axis == 0)
    {
        delta =
            targetLat -
            current->lat;
    }
    else
    {
        delta =
            targetLon -
            current->lon;
    }

    KDNode* nearChild =
        delta < 0
        ? current->left
        : current->right;

    KDNode* farChild =
        delta < 0
        ? current->right
        : current->left;

    nearestRecursive(
        nearChild,
        targetLat,
        targetLon,
        depth + 1,
        bestIndex,
        bestDistance,
        graph);

    if (
        delta * delta <
        bestDistance)
    {
        nearestRecursive(
            farChild,
            targetLat,
            targetLon,
            depth + 1,
            bestIndex,
            bestDistance,
            graph);
    }
}

int KDTree::nearestNode(
    double lat,
    double lon,
    const Graph& graph)
{
    int bestIndex = -1;

    double bestDistance =
        std::numeric_limits<double>::max();

    nearestRecursive(
        root,
        lat,
        lon,
        0,
        bestIndex,
        bestDistance,
        graph);

    return bestIndex;
}