#pragma once

#include "../graph/Graph.h"
#include "../spatial/KDTree.h"
#include "crow/app.h"
#include "crow/json.h"

class RouteController
{
private:

    Graph& graph;

    KDTree& kdTree;

public:

    RouteController(
        Graph& graph,
        KDTree& kdTree);

    crow::response route(
        const crow::request& req);
};