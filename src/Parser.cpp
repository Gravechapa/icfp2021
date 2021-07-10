#include "Parser.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

BonusType getBonusType(const std::string &bTString)
{
    if (bTString == "GLOBALIST"){return BonusType::GLOBALIST;}
    if (bTString == "BREAK_A_LEG"){return BonusType::BREAK_A_LEG;}
    throw std::runtime_error("Bad json: unknown bonus type");
}

std::tuple<Hole, Figure, Bonuses> parseTask(std::string &task)
{
    nlohmann::json json;
    json = json.parse(task);
    auto it = json.find("hole");
    if (it == json.end())
    {
        throw std::runtime_error("Bad json: there is no \"hole\"");
    }
    if (!it.value().is_array())
    {
        throw std::runtime_error("Bad json: field \"hole\" is not an array");
    }
    std::vector<Point> holeArray;
    for (auto& element : *it)
    {
        holeArray.push_back({element[0], element[1]});
    }
    Hole hole(holeArray);

    auto figureIt = json.find("figure");
    if (figureIt == json.end())
    {
        throw std::runtime_error("Bad json: there is no \"figure\"");
    }
    if (!figureIt.value().is_object())
    {
        throw std::runtime_error("Bad json: field \"figure\" is not an object");
    }
    it = figureIt->find("edges");
    if (it == figureIt->end())
    {
        throw std::runtime_error("Bad json: there is no \"edges\"");
    }
    if (!it.value().is_array())
    {
        throw std::runtime_error("Bad json: field \"edges\" is not an array");
    }
    std::vector<VertexNumber> edges;
    for (auto& element : *it)
    {
        edges.push_back({element[0], element[1]});
    }
    it = figureIt.value().find("vertices");
    if (it == figureIt->end())
    {
        throw std::runtime_error("Bad json: there is no \"vertices\"");
    }
    if (!it.value().is_array())
    {
        throw std::runtime_error("Bad json: field \"vertices\" is not an array");
    }
    std::vector<Point> vertices;
    for (auto& element : *it)
    {
        vertices.push_back({element[0], element[1]});
    }

    it = json.find("epsilon");
    if (it == json.end())
    {
        throw std::runtime_error("Bad json: there is no \"epsilon\"");
    }
    if (!it.value().is_number_integer())
    {
        throw std::runtime_error("Bad json: field \"epsilon\" is not an array");
    }
    Figure figure(edges, vertices, it.value().get<int64_t>());

    Bonuses bonuses;
    auto bonusesIt = json.find("bonuses");
    if (bonusesIt != json.end())
    {
        if (!bonusesIt.value().is_array())
        {
            throw std::runtime_error("Bad json: field \"bonuses\" is not an array");
        }
        for (auto& element : *bonusesIt)
        {
            if (!element.is_object())
            {
                throw std::runtime_error("Bad json: \"bonuses\" array contain elements which is not objects");
            }

            it = element.find("position");
            if (it == element.end())
            {
                throw std::runtime_error("Bad json: there is no \"position\" in \"bonuses\" object");
            }
            if (!it.value().is_array())
            {
                throw std::runtime_error("Bad json: field \"bonuses[]::position\" is not an array");
            }
            Point position{it.value()[0], it.value()[1]};

            it = element.find("bonus");
            if (it == element.end())
            {
                throw std::runtime_error("Bad json: there is no \"bonus\" in \"bonuses\" object");
            }
            if (!it.value().is_string())
            {
                throw std::runtime_error("Bad json: field \"bonuses[]::bonus\" is not a string");
            }
            auto bonus = getBonusType(it.value().get<std::string>());

            it = element.find("problem");
            if (it == element.end())
            {
                throw std::runtime_error("Bad json: there is no \"problem\" in \"bonuses\" object");
            }
            if (!it.value().is_number_integer())
            {
                throw std::runtime_error("Bad json: field \"bonuses[]::problem\" is not an integer");
            }
            bonuses.emplace_back(Bonus(position, bonus, it.value().get<int64_t>()));
        }
    }

    return {hole, figure, bonuses};
}

std::string generateSolution(Figure &figure, Hole &hole)
{
    nlohmann::json solution;
    auto& solVert = solution["vertices"];
    for (auto &vertex : figure.getSolution(hole))
    {
        solVert.push_back({vertex.x, vertex.y});
    }

    auto json = solution.dump();
    std::cout << json << std::endl;

    return json;
}
