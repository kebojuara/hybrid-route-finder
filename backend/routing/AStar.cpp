#include "AStar.h"

#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

#include "../utils/GeoUtils.h"

struct AStarNode
{
    int node;

    double fScore;

    bool operator>(
        const AStarNode& other) const
    {
        return fScore > other.fScore;
    }
};

double AStar::heuristic(
    const Graph& graph,
    int current,
    int target)
{
    const Node& a =
        graph.getNode(current);

    const Node& b =
        graph.getNode(target);

    return GeoUtils::haversineDistance(
        a.lat,
        a.lon,
        b.lat,
        b.lon);
}

PathResult AStar::shortestPath(
    const Graph& graph,
    int start,
    int goal)
{
    using Clock =
        std::chrono::high_resolution_clock;

    auto begin =
        Clock::now();

    const int n =
        static_cast<int>(
            graph.nodeCount());

    std::vector<double> gScore(
        n,
        std::numeric_limits<double>::infinity());

    std::vector<double> fScore(
        n,
        std::numeric_limits<double>::infinity());

    std::vector<int> parent(
        n,
        -1);

    std::vector<bool> closed(
        n,
        false);

    std::priority_queue<
        AStarNode,
        std::vector<AStarNode>,
        std::greater<AStarNode>>
        openSet;

    gScore[start] = 0.0;

    fScore[start] =
        heuristic(
            graph,
            start,
            goal);

    openSet.push(
        {
            start,
            fScore[start]
        });

    int visitedCount = 0;

    while (!openSet.empty())
    {
        int current =
            openSet.top().node;

        openSet.pop();

        if (closed[current])
        {
            continue;
        }

        closed[current] = true;

        visitedCount++;

        if (current == goal)
        {
            break;
        }

        const auto& neighbors =
            graph.getNeighbors(current);

        for (const auto& edge : neighbors)
        {
            int next =
                edge.to;

            double tentative =
                gScore[current]
                + edge.distance;

            if (tentative < gScore[next])
            {
                parent[next] = current;

                gScore[next] = tentative;

                fScore[next] =
                    tentative +
                    heuristic(
                        graph,
                        next,
                        goal);

                openSet.push(
                    {
                        next,
                        fScore[next]
                    });
            }
        }
    }

    auto end =
        Clock::now();

    PathResult result;

    result.executionMs =
        std::chrono::duration<double,std::milli>(
            end - begin).count();

    result.visitedNodes =
        visitedCount;

    if (!closed[goal])
    {
        result.found = false;
        return result;
    }

    result.found = true;

    result.distance =
        gScore[goal];

    std::vector<int> path;

    int current = goal;

    while (current != -1)
    {
        path.push_back(current);

        current =
            parent[current];
    }

    std::reverse(
        path.begin(),
        path.end());

    result.path =
        std::move(path);

    return result;
}