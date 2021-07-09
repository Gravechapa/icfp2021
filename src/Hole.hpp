#pragma once

#include <Vector.hpp>
#include <vector>

class Hole
{
public:
    Hole(std::vector<Point> &holeArray);

private:
    std::vector<Point> _holeArray{};
};
