#include "Plot.hpp"
#include <matplot/matplot.h>

void plot(Figure &figure, Hole &hole, std::vector<Point> &pose)
{
    auto f1 = matplot::figure(false);
    auto f2 = matplot::figure(false);
    auto ax1 = f1->current_axes();
    auto ax2 = f2->current_axes();
    ax1->y_axis().reverse(true);
    ax2->y_axis().reverse(true);


    matplot::hold({ax1, ax2}, matplot::on);

    auto holePoints = hole.getPoints();
    for (size_t i = 0; i < holePoints.size(); ++i)
    {
        ax1->plot(std::vector({holePoints[i].x, holePoints[(i + 1) % holePoints.size()].x}),
                  std::vector({holePoints[i].y, holePoints[(i + 1) % holePoints.size()].y}))->color("blue");
    }

    ax1->graph(figure.getEdges())->x_data(figure.getVerticesX()).y_data(figure.getVerticesY()).color("red");

    for (size_t i = 0; i < holePoints.size(); ++i)
    {
        ax2->plot(std::vector({holePoints[i].x, holePoints[(i + 1) % holePoints.size()].x}),
                  std::vector({holePoints[i].y, holePoints[(i + 1) % holePoints.size()].y}))->color("blue");
    }

    std::vector<double> verX;
    std::vector<double> verY;
    for (auto &el : pose)
    {
        verX.push_back(el.x);
        verY.push_back(el.y);
    }
    ax2->graph(figure.getEdges())->x_data(verX).y_data(verY).color("red");
    matplot::hold({ax1, ax2}, matplot::off);

    f1->draw();
    f2->draw();
}
