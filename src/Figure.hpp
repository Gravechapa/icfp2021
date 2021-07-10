#pragma once

#include <cstdint>
#include <Vector.hpp>
#include <vector>
#include <utility>

using vertexNumber = std::pair<size_t, size_t>;

class Figure
{
public:
    Figure(std::vector<vertexNumber> &edges, std::vector<Point> &vertices, int64_t epsilone);
    std::vector<Point>& getSolution();

    std::vector<vertexNumber> getEdges();
    std::vector<double> getVerticesX();
    std::vector<double> getVerticesY();

private:
    int64_t _epsilone;
    std::vector<vertexNumber> _edges;
    std::vector<Point> _vertices;
};
