#include <httplib.h>
#include <cxxopts.hpp>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "Plot.hpp"

void responseCheck(const httplib::Result &response)
{
    if (!response)
    {
        throw std::runtime_error("Unexpected server response:\nNo response from server");
    }
    if (response->status != 200)
    {
        throw std::runtime_error("Unexpected server response:\nHTTP code: " + std::to_string(response->status)
                                 + "\nResponse body: " + response->body);
    }
    std::cout << response->body << std::endl;
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("ICFPC2021", "Program for solving tasks");

    options.add_options()
        ("t,task", "Task id", cxxopts::value<int>())
        ("token", "Access token", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
    }

    httplib::Client cli("https://poses.live");

    httplib::Headers header = {
        {"Authorization", "Bearer " + result["token"].as<std::string>()}
    };

    std::string requestPath = "/api/problems/" + std::to_string(result["task"].as<int>());

    auto response = cli.Get(requestPath.c_str(), header);
    responseCheck(response);

    nlohmann::json json;
    json = json.parse(response->body);
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


    plot(figure, hole);


    char key;
    std::cout << "Submit? y/n" << std::endl;
    do
    {
        std::cin >> key;
    }while (key != 'y' && key != 'n');
    if (key == 'n')
    {
        return 0;
    }

    nlohmann::json solution;
    auto& solVert = solution["vertices"];
    ///TODO send real solution
    for (auto &vertex : vertices)
    {
        solVert.push_back({vertex.x, vertex.y});
    }
    std::stringstream jsonSer;
    jsonSer << solution;
    std::string replayPath = "/api/problems/" + std::to_string(result["task"].as<int>()) + "/solutions" ;
    responseCheck(cli.Post(replayPath.c_str(), header, jsonSer.str().c_str(), "application/json"));

    return 0;
}
