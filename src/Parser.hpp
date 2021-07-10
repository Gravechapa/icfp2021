#pragma once

#include "Hole.hpp"
#include "Figure.hpp"
#include "Bonus.hpp"
#include <string>

std::tuple<Hole, Figure, Bonus> parseTask(std::string &task);
std::string generateSolution(Figure &figure, Hole &hole);
