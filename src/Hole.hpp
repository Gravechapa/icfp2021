#pragma once

#include <Vector.hpp>
#include <vector>

class Hole
{
public:
    Hole(std::vector<Point> &holeArray);
    std::vector<Point>& getPoints();

    double countDislikes(std::vector<Vector>& pose);

    double countDislikes(std::vector<Vector>& pose, size_t testIndex, Vector& testPosition);

private:
    std::vector<Point> _holeArray{};
};
