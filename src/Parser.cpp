#include "Parser.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

std::tuple<Hole, Figure, Bonus> parseTask(std::string &task)
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

    return {hole, figure, Bonus()};
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
