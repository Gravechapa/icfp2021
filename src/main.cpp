#include <cxxopts.hpp>
#include <iostream>
#include <httplib.h>

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

    httplib::Client cli("https://poses.live/api");

    httplib::Headers header = {
        {"Authorization", "Bearer" + result["token"].as<std::string>()}
    };

    cli.Get("/hello", header);

    return 0;
}
