#include "GeoUtils.h"

#include <cmath>

namespace
{
    constexpr double EARTH_RADIUS_METERS =
        6371000.0;

    constexpr double PI =
    3.14159265358979323846;

    double toRadians(double degree)
    {
        return degree * PI / 180.0;
    }
}

double GeoUtils::haversineDistance(
    double lat1,
    double lon1,
    double lat2,
    double lon2)
{
    double dLat =
        toRadians(lat2 - lat1);

    double dLon =
        toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a =
        std::pow(std::sin(dLat / 2.0), 2) +
        std::cos(lat1) *
        std::cos(lat2) *
        std::pow(std::sin(dLon / 2.0), 2);

    double c =
        2.0 * std::asin(std::sqrt(a));

    return EARTH_RADIUS_METERS * c;
}