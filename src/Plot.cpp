#include "Plot.hpp"
#include <matplot/matplot.h>

void plot(Figure &figure, Hole &hole)
{
    matplot::gca()->y_axis().reverse(true);
    matplot::hold(matplot::on);
    auto holePoints = hole.getPoints();
    for (size_t i = 0; i < holePoints.size(); ++i)
    {
        matplot::plot(std::vector({holePoints[i].x, holePoints[(i + 1) % holePoints.size()].x}),
                      std::vector({holePoints[i].y, holePoints[(i + 1) % holePoints.size()].y}))->color("blue");
    }

    matplot::graph(figure.getEdges())->x_data(figure.getVerticesX()).y_data(figure.getVerticesY()).color("red");
    matplot::hold(matplot::off);
    matplot::show();
}
