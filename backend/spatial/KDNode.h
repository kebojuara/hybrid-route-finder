#pragma once

struct KDNode
{
    int graphIndex;

    double lat;
    double lon;

    KDNode* left;
    KDNode* right;

    KDNode(
        int index,
        double latitude,
        double longitude)
        :
        graphIndex(index),
        lat(latitude),
        lon(longitude),
        left(nullptr),
        right(nullptr)
    {
    }
};