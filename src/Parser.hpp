#pragma once

#include "Hole.hpp"
#include "Figure.hpp"
#include "Bonus.hpp"
#include <string>

std::tuple<Hole, Figure, Bonuses> parseTask(std::string &task);
std::string generateSolution(Figure &figure);
