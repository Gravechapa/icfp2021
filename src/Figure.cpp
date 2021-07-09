#include "Figure.hpp"

Figure::Figure(std::vector<vertexNumber>&edges, std::vector<Point> &vertices, int64_t epsilone)
    :_epsilone(epsilone), _edges(edges), _vertices(vertices)
{}

std::vector<vertexNumber> Figure::getEdges()
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
