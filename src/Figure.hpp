#pragma once

#include <cstdint>
#include <Vector.hpp>
#include <vector>
#include <utility>

using VertexNumber = std::pair<size_t, size_t>;

class Figure
{
public:
    Figure(std::vector<VertexNumber> &edges, std::vector<Point> &vertices, int64_t epsilone);
    std::vector<Point>& getSolution();

    std::vector<VertexNumber> getEdges();
    std::vector<double> getVerticesX();
    std::vector<double> getVerticesY();

    std::vector<Point> getConnectedPoints();

private:
    int64_t _epsilone;
    std::vector<VertexNumber> _edges;
    std::vector<Point> _vertices;
};
