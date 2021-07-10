#include "Figure.hpp"
#include <algorithm>
#include "Annealing.hpp"
#include <cmath>

Figure::Figure(std::vector<VertexNumber>&edges, std::vector<Point> &vertices, int64_t epsilone)
    :_epsilone(epsilone), _edges(edges), _vertices(vertices)
{
    std::transform(
        _edges.cbegin(),
        _edges.cend(),
        std::back_inserter(_edgesInfo),
        [this](VertexNumber v)
    {
        auto diff = this->_vertices[v.first] - this->_vertices[v.second];
        double length = std::sqrt(diff * diff);

        return EdgeInfo{ length, v.first, v.second };
    });

    for (auto i = 0; i < _edgesInfo.size(); i++)
    {
        _edgesOfPoint.insert({ _edgesInfo[i].pointedFirst, i });
        _edgesOfPoint.insert({ _edgesInfo[i].pointedSecond, i });
    }
}

std::vector<Point> Figure::getSolution(Hole& hole)
{
    Annealing annealing;
    return annealing.getPose(*this, hole, _epsilone);
}

std::vector<VertexNumber> Figure::getEdges()
{
    return _edges;
}

std::vector<double> Figure::getVerticesX()
{
    std::vector<double> result;
    for (auto point : _vertices)
    {
        result.push_back(point.x);
    }
    return result;
}
std::vector<double> Figure::getVerticesY()
{
    std::vector<double> result;
    for (auto point : _vertices)
    {
        result.push_back(point.y);
    }
    return result;
}

std::vector<Point>& Figure::getConnectedPoints()
{
    return _vertices;
}

EdgeInfo& Figure::getEdgeOtherEnd(size_t edgeIndex)
{
    return _edgesInfo[edgeIndex];
}

std::pair<Figure::ConnectedEdgesIterator, Figure::ConnectedEdgesIterator> Figure::getEdgesOfPoint(size_t pointIndex)
{
    return _edgesOfPoint.equal_range(pointIndex);
}
