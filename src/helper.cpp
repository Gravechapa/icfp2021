#include <vector>
#include <cmath>
#include "helper.hpp"

bool isInsideFigure(std::vector<Vector>& vertices, Vector& testVertex)
{
    int i, j = 0;
    bool c = false;

    auto size = vertices.size();

    for (i = 0, j = size - 1; i < size; j = i++)
    {
        if (
            ((vertices[i].y > testVertex.y) != (vertices[j].y > testVertex.y)) &&
            (testVertex.x < (vertices[j].x - vertices[i].x)* (testVertex.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
        {
            c = !c;
        }
    }
    return c;
}

std::vector<Vector> getAvailablePositions(Vector &vertex, int64_t sqLength, uint64_t epsilon)
{
    auto sqMinLength = sqLength * (1.0 - epsilon / 1000000.0); // Const from specifications
    auto sqMaxLength = sqLength * (1.0 + epsilon / 1000000.0); // Const from specifications

    auto maxLength = std::sqrt(sqMaxLength);

    std::vector<Vector> resultPoints;

    auto ceil = (int64_t)std::ceil(maxLength);
    auto floor = (int64_t)std::floor(maxLength);

    for (auto x = vertex.x - floor; x <= vertex.x + floor; x++)
    {
        for (auto y = vertex.y - floor; y <= vertex.y + floor; y++)
        {
            auto sqDist = (x - vertex.x) * (x - vertex.x) + (y - vertex.y) * (y - vertex.y);
            if (sqDist >= sqMinLength && sqDist <= sqMaxLength)
            {
                resultPoints.emplace_back(Vector{ x, y });
            }
        }
    }

    return resultPoints;
}

bool isPositionAllowed(Vector &vertex, Vector &testVertex, int64_t sqEdgeLength, uint64_t epsilon)
{
    auto sqMinLength = sqEdgeLength * (1.0 - epsilon / 1000000.0); // Const from specifications
    auto sqMaxLength = sqEdgeLength * (1.0 + epsilon / 1000000.0); // Const from specifications

    auto dist = (vertex - testVertex) * (vertex - testVertex);

    return dist >= sqMinLength && dist <= sqMaxLength;
}

std::vector<Vector> getPositions(std::vector<double> &originalDistances, std::vector<Vector>& connectedVertices, uint64_t epsilon)
{
    auto potentialPositions = getAvailablePositions(connectedVertices[0], originalDistances[0], epsilon);

    std::vector<Vector> resultPoints;

    for (auto& pos : potentialPositions)
    {
        bool isNormal = true;

        for (auto i = 1; i < connectedVertices.size(); i++)
        {
            isNormal = isNormal && isPositionAllowed(connectedVertices[i], pos, originalDistances[i], epsilon);

            if (!isNormal)
            {
                break;
            }
        }

        if (isNormal)
        {
            resultPoints.push_back(pos);
        }
    }

    return resultPoints;
}
