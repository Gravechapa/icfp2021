#include "Hole.hpp"


Hole::Hole(std::vector<Point> &holeArray): _holeArray(holeArray)
{

}


std::vector<Point>& Hole::getPoints()
{
    return _holeArray;
}
