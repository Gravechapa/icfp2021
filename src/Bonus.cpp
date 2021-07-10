#include "Bonus.hpp"

Bonus::Bonus(Point position, BonusType bonus, int64_t problem)
    : _position(position), _bonus(bonus), _problem(problem)
{
}

Point Bonus::getPosition() const
{
    return _position;
}

BonusType Bonus::getBonusType() const
{
    return _bonus;
}

int64_t Bonus::getProblemID() const
{
    return _problem;
}
