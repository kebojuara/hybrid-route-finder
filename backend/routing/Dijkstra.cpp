#include "Dijkstra.h"

#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>

struct PQNode
{
    int node;
    double distance;

    bool operator>(
        const PQNode& other) const
    {
        return distance > other.distance;
    }
};

PathResult Dijkstra::shortestPath(
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

    std::vector<double> dist(
        n,
        std::numeric_limits<double>::infinity());

    std::vector<int> parent(
        n,
        -1);

    std::vector<bool> visited(
        n,
        false);

    std::priority_queue<
        PQNode,
        std::vector<PQNode>,
        std::greater<PQNode>>
        pq;

    dist[start] = 0.0;

    pq.push(
        {
            start,
            0.0
        });

    int visitedCount = 0;

    while (!pq.empty())
    {
        PQNode current =
            pq.top();

        pq.pop();

        int u =
            current.node;

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;

        visitedCount++;

        if (u == goal)
        {
            break;
        }

        const auto& neighbors =
            graph.getNeighbors(u);

        for (const auto& edge : neighbors)
        {
            int v =
                edge.to;

            double newDist =
                dist[u] +
                edge.distance;

            if (newDist < dist[v])
            {
                dist[v] = newDist;

                parent[v] = u;

                pq.push(
                    {
                        v,
                        newDist
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

    if (!visited[goal])
    {
        result.found = false;
        return result;
    }

    result.found = true;

    result.distance =
        dist[goal];

    std::vector<int> path;

    int current =
        goal;

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