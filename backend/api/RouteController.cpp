#include "RouteController.h"
#include "../routing/AStar.h"

RouteController::RouteController(
    Graph& g,
    KDTree& tree)
    :
    graph(g),
    kdTree(tree)
{
}

crow::response
RouteController::route(
    const crow::request& req)
{
    auto body =
        crow::json::load(
            req.body);

    if (!body)
    {
        return crow::response(
            400,
            "Invalid JSON");
    }

    double startLat =
        body["startLat"].d();

    double startLon =
        body["startLon"].d();

    double endLat =
        body["endLat"].d();

    double endLon =
        body["endLon"].d();

    int startNode =
        kdTree.nearestNode(
            startLat,
            startLon,
            graph);

    int endNode =
        kdTree.nearestNode(
            endLat,
            endLon,
            graph);

    AStar astar;

    auto result =
        astar.shortestPath(
            graph,
            startNode,
            endNode);

    if (!result.found)
    {
        crow::json::wvalue error;

        error["success"] = false;

        return crow::response(error);
    }

    crow::json::wvalue response;

    response["success"] = true;

    response["distanceMeters"] =
        result.distance;

    response["visitedNodes"] =
        result.visitedNodes;

    response["executionMs"] =
        result.executionMs;

    crow::json::wvalue::list route;

    for (int index : result.path)
    {
        const Node& node =
            graph.getNode(index);

        crow::json::wvalue point;

        point["lat"] =
            node.lat;

        point["lon"] =
            node.lon;

        route.push_back(
            std::move(point));
    }

    response["route"] =
        std::move(route);

    return crow::response(
        response);
}