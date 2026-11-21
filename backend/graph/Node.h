#pragma once

#include <cstdint>

struct Node
{
    int64_t osmId;
    double lat;
    double lon;

    Node()
        : osmId(0), lat(0.0), lon(0.0)
    {
    }

    Node(
        int64_t id,
        double latitude,
        double longitude)
        : osmId(id),
          lat(latitude),
          lon(longitude)
    {
    }
};