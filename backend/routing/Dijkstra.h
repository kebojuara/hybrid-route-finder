#pragma once

#include "../graph/Graph.h"
#include "PathResult.h"

class Dijkstra
{
public:

    PathResult shortestPath(
        const Graph& graph,
        int start,
        int goal);
};