#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#undef CPPHTTPLIB_OPENSSL_SUPPORT
#include <cxxopts.hpp>
#include <iostream>

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

    httplib::Client cli("http://poses.live/api");

    httplib::Headers header = {
        {"Authorization", "Bearer" + result["token"].as<std::string>()}
    };

    auto response = cli.Get("/problems/1", header);

    if (response->status == 200)
    {
        std::cout << response->body << std::endl;
    }

    return 0;
}
