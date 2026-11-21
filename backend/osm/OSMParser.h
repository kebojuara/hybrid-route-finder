#pragma once

#include <string>

#include "../graph/Graph.h"

class OSMParser
{
public:
    bool parse(
        const std::string& filename,
        Graph& graph);
};