#pragma once

struct Edge
{
    int to;
    double distance;

    Edge()
        : to(-1),
          distance(0.0)
    {
    }

    Edge(
        int destination,
        double dist)
        : to(destination),
          distance(dist)
    {
    }
};