#include <httplib.h>
#include <cxxopts.hpp>
#include <iostream>
#include <sstream>

#include "Plot.hpp"

int main(int argc, char* argv[])
{

    /*std::vector<vertexNumber> edges = {
        {2, 5},{5, 4},{4, 1}, {1, 0}, {0, 8}, {8, 3}, {3, 7},{7, 11}, {11, 13},
        {13, 12}, {12, 18}, {18, 19}, {19, 14},{14, 15}, {15, 17}, {17, 16}, {16, 10},
        {10, 6}, {6, 2},{8, 12}, {7, 9}, {9, 3}, {8, 9}, {9, 12}, {13, 9}, {9, 11},
        {4, 8}, {12, 14}, {5, 10}, {10, 15}
    };
    std::vector<Point> vertices = {
        {20, 30}, {20, 40}, {30, 95}, {40, 15}, {40, 35}, {40, 65},{40, 95}, {45, 5},
        {45, 25}, {50, 15}, {50, 70}, {55, 5},{55, 25}, {60, 15}, {60, 35}, {60, 65},
        {60, 95}, {70, 95},{80, 30}, {80, 40}
    };
    std::vector<Point> holeArray = {{55, 80}, {65, 95}, {95, 95}, {35, 5}, {5, 5},{35, 50}, {5, 95}, {35, 95}, {45, 80}};
    Figure figure(edges, vertices, 0);
    Hole hole(holeArray);

    plot(figure, hole);*/

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

    std::stringstream requestPathBuilder;
    requestPathBuilder << "/api/problems/" << result["task"].as<int>();

    auto response = cli.Get(requestPathBuilder.str().c_str(), header);

    if (response->status == 200)
    {
        std::cout << response->body << std::endl;
    }

    return 0;
}
