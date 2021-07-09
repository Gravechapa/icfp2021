#include "Hole.hpp"
#include <cmath>


Hole::Hole(std::vector<Point> &holeArray): _holeArray(holeArray)
{

}


std::vector<Point>& Hole::getPoints()
{
    return _holeArray;
}

double Hole::countDislikes(std::vector<Vector>& pose)
{
    double dislike = 0.0;

    for (auto& holePoint : _holeArray)
    {
        auto diff = holePoint - pose[0];
        double minDistance = std::sqrt(diff * diff);

        for (size_t i = 1; i < pose.size(); i++)
        {
            diff = holePoint - pose[i];
            auto distance = std::sqrt(diff * diff);

            if (distance < minDistance)
            {
                minDistance = distance;
            }
        }

        dislike += minDistance;
    }
}
