#include <httplib.h>
#include <cxxopts.hpp>
#include <iostream>
#include <sstream>

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

    std::stringstream requestPathBuilder;
    requestPathBuilder << "/api/problems/" << result["task"].as<int>();

    auto response = cli.Get(requestPathBuilder.str().c_str(), header);

    if (response->status == 200)
    {
        std::cout << response->body << std::endl;
    }

    return 0;
}
