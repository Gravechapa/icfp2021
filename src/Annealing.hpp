#pragma once

#include <vector>
#include "Vector.hpp"
#include "Figure.hpp"
#include "Hole.hpp"

class Annealing
{
public:

    std::vector<Vector> getPose(Figure& figure, Hole& hole, uint16_t epsilon);
};