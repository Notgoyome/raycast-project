/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** main
*/

#include <iostream>
#include "../../include/Configuration.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        return 84;
    }
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
        return 0;
    }
    if (argc == 2) {
        ray::Configuration config(argv[1]);
        if (config.getNodes().empty()) {
            std::cerr << "Error: No nodes found in the configuration file" << std::endl;
            return 84;
        }
    }
    return 0;
}
