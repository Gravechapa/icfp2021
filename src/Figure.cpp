#include "Figure.hpp"

Figure::Figure(std::vector<VertexNumber>&edges, std::vector<Point> &vertices, int64_t epsilone)
    :_epsilone(epsilone), _edges(edges), _vertices(vertices)
{}

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
