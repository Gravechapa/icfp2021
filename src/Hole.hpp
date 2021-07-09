#pragma once

#include <Vector.hpp>
#include <vector>

class Hole
{
public:
    Hole(std::vector<Point> &holeArray);
    std::vector<Point>& getPoints();

private:
    std::vector<Point> _holeArray{};
};
