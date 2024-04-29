/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** main
*/

#include <iostream>
#include "NodeBuilder.hpp"
#include "parsing.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        throw ray::CoreException("Invalid number of arguments.");
        return 84;
    }

    try {
        ray::NodeBuilder builder(argv[1]);
        auto nodes = builder.getRootNodes();
        if (nodes.empty()) {
            throw ray::CoreException("No root nodes found in the scene file.");
            return 84;
        }

        // à implémenter
        //
        //

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
