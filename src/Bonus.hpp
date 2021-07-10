#pragma once

#include <vector>
#include <Vector.hpp>

enum class BonusType
{
    GLOBALIST,
    BREAK_A_LEG
};

class Bonus
{
public:
    Bonus(Point position, BonusType bonus, int64_t problem);
    Point getPosition() const;
    BonusType getBonusType() const;
    int64_t getProblemID() const;

private:
    Point _position;
    BonusType _bonus;
    int64_t _problem;
};

using Bonuses = std::vector<Bonus>;
