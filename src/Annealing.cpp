#include <random>
#include <functional>

#include "helper.hpp"
#include "Annealing.hpp"

std::vector<Vector> Annealing::getPose(Figure& figure, Hole& hole, uint64_t epsilon)
{
    auto& points = figure.getConnectedPoints();
    std::vector<Vector> pose(points);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(0, points.size() - 1);

    auto dislikes = hole.countDislikes(pose);

    double T = 10000;

    for (auto t = T; t > 0; t -= 0.01)
    {
        size_t availPointsSize = 0;
        std::vector<Vector> availablePoints;
        size_t movePoint;

        while (availPointsSize == 0)
        {
            movePoint = dist(gen);

            auto edgesIndices = figure.getEdgesOfPoint(movePoint);

            std::vector<double> lengths;

            std::vector<Vector> connectedPoints;

            std::transform(
                edgesIndices.first,
                edgesIndices.second,
                std::back_inserter(lengths),
                [&figure](Figure::ConnectedEdgesIterator::value_type e)
            {
                return figure.getEdgeOtherEnd(e.second).length;
            });

            std::transform(
                edgesIndices.first,
                edgesIndices.second,
                std::back_inserter(connectedPoints),
                [&pose, &figure](Figure::ConnectedEdgesIterator::value_type e)
            {
                auto edge = figure.getEdgeOtherEnd(e.second);

                if (edge.pointedFirst == e.first)
                {
                    return pose[edge.pointedSecond];
                }

                return pose[edge.pointedFirst];
            });

            availablePoints = getPositions(lengths, connectedPoints, epsilon);

            availPointsSize = availablePoints.size();
        }


        std::uniform_int_distribution<> dist(0, availablePoints.size() - 1);

        auto newPosition = dist(gen);

        auto newDislikes = hole.countDislikes(pose, movePoint, availablePoints[newPosition]);

        if (!isInsideFigure(hole.getPoints(), availablePoints[newPosition]))
        {
            newDislikes = newDislikes * 1000;
        }

        if (newDislikes <= dislikes)
        {
            pose[movePoint] = availablePoints[newPosition];
            dislikes = newDislikes;
        }
        else
        {
            auto probabilityToMove = std::exp(-(newDislikes - dislikes) / t);

            std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);

            if (uniform_zero_to_one(gen) < probabilityToMove)
            {
                pose[movePoint] = availablePoints[newPosition];
                dislikes = newDislikes;
            }
        }
    }

    return pose;
}
