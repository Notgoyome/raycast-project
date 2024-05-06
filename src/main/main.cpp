/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** main
*/

#include <iostream>

#include "Image.hpp"
#include "parsing.hpp"
#include "Ray.hpp"
#include "../cameras/base/Camera.hpp"
#include "../scenes/base/Scene.hpp"
#include "Renderer.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "utils/mainMethods.hpp"

Image render(unsigned int width, unsigned int height,
    const std::shared_ptr<ray::IScene>& scene,
    const std::shared_ptr<ray::ICamera>& cam, RGB backgroundColor)
{
    Image img;
    auto biggest = static_cast<unsigned int>(std::max(width, height));
    unsigned int startI = biggest == width ? 0 : static_cast<unsigned int>(static_cast<float>(biggest - width) / 2.f);
    unsigned int startJ = biggest == height ? 0 : static_cast<unsigned int>(static_cast<float>(biggest - height) / 2.f);

    for (unsigned int i = startI; i < biggest - startI; i++) {
        for (unsigned int j = startJ; j < biggest - startJ; j++) {
            double u = double(i) / biggest;
            double v = double(j) / biggest;
            RGB color = ray::RayTracerUtils::renderPixel(scene, cam, u, v, backgroundColor);
            img.addPixel(Math::Vector2D{static_cast<double>(i - startI), static_cast<double>(j - startJ)}, color);
        }
        std::cout << "Rendering: " << i - startI << "/" << width << std::endl;
    }

    return img;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Invalid number of arguments." << std::endl;
        std::cerr << "USAGE: ./raytracer <SCENE_FILE> | <SCENE_FILE> -s <port> <nb clients> | -c <ip> <port>" << std::endl;
        return 84;
    }

    try {
        if (argc == 2) {
            ray::NodeBuilder builder(argv[1]);
            const auto& nodes = builder.getRootNodes();
            RGB backgroundColor = builder.getBackgroundColor();
            image_data_t imageData = builder.getImageData();

            if (nodes.empty()) {
                throw ray::CoreException("No root nodes found in the scene file.");
            }

            std::shared_ptr<ray::IScene> scene = std::dynamic_pointer_cast<ray::IScene>(ray::RayTracerUtils::getScene(nodes));
            std::shared_ptr<ray::ICamera> camera = ray::RayTracerUtils::getCamera(scene);
            Image img = render(imageData.width, imageData.height, scene, camera, backgroundColor);
            ray::Renderer renderer;
            renderer.renderPpmImage(img, imageData.filename);
            renderer.renderSfmlImage(img);

        } else if (argc == 5 && std::string(argv[2]) == "-s") {
            int port = std::stoi(argv[3]);
            int nb_clients = std::stoi(argv[4]);
            ray::Server server(port, argv[1]);
            server.accept_connections(nb_clients);

            ray::NodeBuilder builder(argv[1]);
            const auto& nodes = builder.getRootNodes();
            RGB backgroundColor = builder.getBackgroundColor();
            image_data_t imageData = builder.getImageData();

            if (nodes.empty()) {
                throw ray::CoreException("No root nodes found in the scene file.");
            }

            std::shared_ptr<ray::IScene> scene = std::dynamic_pointer_cast<ray::IScene>(ray::RayTracerUtils::getScene(nodes));
            std::shared_ptr<ray::ICamera> camera = ray::RayTracerUtils::getCamera(scene);
            Image img = server.orchestrate_rendering(imageData.width, imageData.height, scene, camera, backgroundColor);
            ray::Renderer renderer;
            renderer.renderPpmImage(img, imageData.filename);
            renderer.renderSfmlImage(img);

        } else if (argc == 4 && std::string(argv[1]) == "-c") {
            std::string ip = argv[2];
            int port = std::stoi(argv[3]);

            ray::Client client(ip, port);

            client.render();

        } else {
            std::cerr << "Invalid arguments. Please check the usage." << std::endl;
            return 84;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
