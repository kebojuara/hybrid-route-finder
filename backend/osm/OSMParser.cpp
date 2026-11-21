#include "OSMParser.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tinyxml2.h>

#include "../utils/GeoUtils.h"

using namespace tinyxml2;

bool OSMParser::parse(
    const std::string& filename,
    Graph& graph)
{
    XMLDocument doc;

    std::cout
        << "\n=== LOADING FILE ===\n"
        << filename
        << "\n";

    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS)
    {
        std::cerr
            << "Failed to load OSM file\n";

        return false;
    }

    XMLElement* root =
        doc.FirstChildElement("osm");

    if (!root)
    {
        std::cerr
            << "No osm root found\n";

        return false;
    }

    //--------------------------------------------------
    // PASS 1
    // Collect all road nodes
    //--------------------------------------------------

    std::cout
        << "\n=== PASS 1 : COLLECT ROAD NODES ===\n";

    std::unordered_set<long long>
        usedRoadNodes;

    int totalWays = 0;
    int roadWays = 0;

    for (
        XMLElement* way =
            root->FirstChildElement("way");
        way;
        way =
            way->NextSiblingElement("way"))
    {
        totalWays++;

        bool isRoad = false;

        for (
            XMLElement* tag =
                way->FirstChildElement("tag");
            tag;
            tag =
                tag->NextSiblingElement("tag"))
        {
            const char* k =
                tag->Attribute("k");

            if (!k)
            {
                continue;
            }

            if (std::string(k) == "highway")
            {
                isRoad = true;
                break;
            }
        }

        if (!isRoad)
        {
            continue;
        }

        roadWays++;

        for (
            XMLElement* nd =
                way->FirstChildElement("nd");
            nd;
            nd =
                nd->NextSiblingElement("nd"))
        {
            long long ref =
                nd->Int64Attribute("ref");

            usedRoadNodes.insert(ref);
        }
    }

    std::cout
        << "Total ways      : "
        << totalWays
        << "\n";

    std::cout
        << "Road ways       : "
        << roadWays
        << "\n";

    std::cout
        << "Road node refs  : "
        << usedRoadNodes.size()
        << "\n";

    //--------------------------------------------------
    // PASS 2
    // Load only road nodes
    //--------------------------------------------------

    std::cout
        << "\n=== PASS 2 : LOAD ROAD NODES ===\n";

    std::unordered_map<long long, int>
        nodeMap;

    int loadedNodes = 0;

    for (
        XMLElement* node =
            root->FirstChildElement("node");
        node;
        node =
            node->NextSiblingElement("node"))
    {
        long long id =
            node->Int64Attribute("id");

        if (
            usedRoadNodes.find(id)
            ==
            usedRoadNodes.end())
        {
            continue;
        }

        double lat =
            node->DoubleAttribute("lat");

        double lon =
            node->DoubleAttribute("lon");

        int index =
            graph.addNode(
                id,
                lat,
                lon);

        nodeMap[id] = index;

        loadedNodes++;
    }

    std::cout
        << "Loaded nodes    : "
        << loadedNodes
        << "\n";

    //--------------------------------------------------
    // PASS 3
    // Build graph
    //--------------------------------------------------

    std::cout
        << "\n=== PASS 3 : BUILD GRAPH ===\n";

    int createdEdges = 0;
    int missingRefs = 0;

    for (
        XMLElement* way =
            root->FirstChildElement("way");
        way;
        way =
            way->NextSiblingElement("way"))
    {
        bool isRoad = false;
        bool oneWay = false;

        for (
            XMLElement* tag =
                way->FirstChildElement("tag");
            tag;
            tag =
                tag->NextSiblingElement("tag"))
        {
            const char* k =
                tag->Attribute("k");

            const char* v =
                tag->Attribute("v");

            if (!k)
            {
                continue;
            }

            std::string key(k);

            if (key == "highway")
            {
                isRoad = true;
            }

            if (
                key == "oneway" &&
                v &&
                std::string(v) == "yes")
            {
                oneWay = true;
            }
        }

        if (!isRoad)
        {
            continue;
        }

        std::vector<long long> refs;

        for (
            XMLElement* nd =
                way->FirstChildElement("nd");
            nd;
            nd =
                nd->NextSiblingElement("nd"))
        {
            refs.push_back(
                nd->Int64Attribute("ref"));
        }

        for (
            size_t i = 0;
            i + 1 < refs.size();
            i++)
        {
            auto itA =
                nodeMap.find(refs[i]);

            auto itB =
                nodeMap.find(refs[i + 1]);

            if (
                itA == nodeMap.end() ||
                itB == nodeMap.end())
            {
                missingRefs++;
                continue;
            }

            int from =
                itA->second;

            int to =
                itB->second;

            const Node& n1 =
                graph.getNode(from);

            const Node& n2 =
                graph.getNode(to);

            double distance =
                GeoUtils::haversineDistance(
                    n1.lat,
                    n1.lon,
                    n2.lat,
                    n2.lon);

            graph.addEdge(
                from,
                to,
                distance);

            createdEdges++;

            if (!oneWay)
            {
                graph.addEdge(
                    to,
                    from,
                    distance);

                createdEdges++;
            }
        }
    }

    //--------------------------------------------------
    // STATISTICS
    //--------------------------------------------------

    int isolatedNodes = 0;

    for (
        size_t i = 0;
        i < graph.nodeCount();
        i++)
    {
        if (
            graph.getNeighbors(
                static_cast<int>(i))
                .empty())
        {
            isolatedNodes++;
        }
    }

    std::cout
        << "\n=== GRAPH SUMMARY ===\n";

    std::cout
        << "Nodes           : "
        << graph.nodeCount()
        << "\n";

    std::cout
        << "Edges           : "
        << graph.edgeCount()
        << "\n";

    std::cout
        << "Created Edges   : "
        << createdEdges
        << "\n";

    std::cout
        << "Missing Refs    : "
        << missingRefs
        << "\n";

    std::cout
        << "Isolated Nodes  : "
        << isolatedNodes
        << "\n";

    return true;
}