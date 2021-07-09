#pragma once

#include <cstdint>
#include <Vector.hpp>
#include <vector>
#include <utility>

class Figure
{
using vertexNumber = std::vector<std::pair<size_t, size_t>>;
public:
    Figure(std::vector<vertexNumber> &edges, std::vector<Point> &vertices, int64_t epsilone);

private:
    int64_t _epsilone;
};
