/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** main
*/

#include <iostream>
#include "Configuration.hpp"
#include "Image.hpp"
#include "INode.hpp"
#include "../lights/point_light/PointLight.hpp"
#include "../../include/Configuration.hpp"
#include "../transformations/Transform.hpp"

void runTests()
{
    std::cout << "Running tests..." << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::shared_ptr<ray::Transform> transform = std::make_shared<ray::Transform>(Math::Point3D{-50, -50, -50},
                                                                                 Math::Vector3D{0, 0, 0},
                                                                                 Math::Vector3D{0, 0, 0});
    std::shared_ptr<ray::ILight> light = std::make_shared<ray::PointLight>(RGB{255, 255, 255});
    std::shared_ptr<ray::INode> scene = std::make_shared<ray::PointLight>(RGB{255, 255, 255});

    scene->addChild(transform);
    transform->addChild(light);
    Math::Vector3D test = light->getIncidentVector({0, 0, 0});
    std::cout << "Test 1: " << test.X << " " << test.Y << " " << test.Z << std::endl;
}

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
    if (argc == 2 && std::string(argv[1]) == "--tests") {
        runTests();
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
