#include <iostream>

#include "crow/app.h"
#include "crow/json.h"

#include "graph/Graph.h"
#include "osm/OSMParser.h"
#include "spatial/KDTree.h"
#include "api/RouteController.h"
#include "crow/middlewares/cors.h"

int main()
{
    Graph graph;

    OSMParser parser;

    if (
        !parser.parse(
            "../data/surabaya.osm",
            graph))
    {
        std::cout
            << "Failed to load OSM\n";

        return 1;
    }

    KDTree tree;

    tree.build(graph);

    std::cout
        << "KDTree built\n";

    crow::App<
        crow::CORSHandler
    > app;

    auto& cors =
        app.get_middleware<
            crow::CORSHandler>();

    cors
        .global()
        .origin("*")
        .headers("Content-Type")
        .methods(
            crow::HTTPMethod::POST,
            crow::HTTPMethod::OPTIONS);

    RouteController controller(
        graph,
        tree);

    CROW_ROUTE(
        app,
        "/route")
    .methods("POST"_method)
    (
        [&](const crow::request& req)
        {
            return controller.route(
                req);
        });

    std::cout
        << "Server running on port 8080\n";

    app.port(8080)
       .multithreaded()
       .run();
}