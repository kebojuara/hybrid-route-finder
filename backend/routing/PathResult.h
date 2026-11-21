#pragma once

#include <vector>

struct PathResult
{
    bool found = false;

    double distance = 0.0;

    double executionMs = 0.0;

    int visitedNodes = 0;

    std::vector<int> path;
};