#pragma once

#include <vector>
#include "Figure.hpp"
#include "Hole.hpp"

class Annealing
{
public:

    std::vector<Vector> getPose(Figure& figure, Hole& hole, uint64_t epsilon);
};
