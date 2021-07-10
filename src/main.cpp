#include <httplib.h>
#include <cxxopts.hpp>
#include <iostream>

#include "Parser.hpp"
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

    auto[hole, figure, bonuses] = parseTask(response->body);

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

    std::string replayPath = "/api/problems/" + std::to_string(result["task"].as<int>()) + "/solutions" ;
    responseCheck(cli.Post(replayPath.c_str(), header, generateSolution(figure).c_str(), "application/json"));

    return 0;
}
