#pragma once

#include "../graph/Graph.h"
#include "PathResult.h"

class AStar
{
public:

    PathResult shortestPath(
        const Graph& graph,
        int start,
        int goal);

private:

    double heuristic(
        const Graph& graph,
        int current,
        int target);
};