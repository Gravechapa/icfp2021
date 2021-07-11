#pragma once

#include <cstdint>
#include <Vector.hpp>
#include <vector>
#include <utility>
#include <map>
#include "Hole.hpp"

using VertexNumber = std::pair<size_t, size_t>;

struct EdgeInfo
{
    int64_t length;
    size_t pointedFirst;
    size_t pointedSecond;
};

class Figure
{
public:
    Figure(std::vector<VertexNumber> &edges, std::vector<Point> &vertices, int64_t epsilone);
    std::vector<Point> getSolution(Hole &hole);

    std::vector<VertexNumber> getEdges();
    std::vector<double> getVerticesX();
    std::vector<double> getVerticesY();

    std::vector<Point>& getConnectedPoints();

    EdgeInfo& getEdgeOtherEnd(size_t edgeIndex);

    using ConnectedEdgesIterator = std::multimap<size_t, size_t>::const_iterator;

    std::pair<ConnectedEdgesIterator, ConnectedEdgesIterator> getEdgesOfPoint(size_t pointIndex);

private:
    int64_t _epsilone;
    std::vector<VertexNumber> _edges;
    std::vector<Point> _vertices;

    std::vector<EdgeInfo> _edgesInfo;

    std::multimap<size_t, size_t> _edgesOfPoint;
};
