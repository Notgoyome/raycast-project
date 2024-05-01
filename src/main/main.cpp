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
#include "../cameras/Camera.hpp"
#include "../scenes/Scene.hpp"

std::shared_ptr<ray::INode> getScene(std::vector<std::shared_ptr<ray::INode>> nodes)
{
    for (auto node : nodes) {
        if (node->getType() == ray::type::SCENE) {
            return node;
        }
    }
    return nullptr;
}

RGB getHitColor(PosShapePair hit, ray::Ray ray, const std::shared_ptr<ray::IScene>& scene)
{
    std::shared_ptr<ray::IMaterial> material = ray::Scene::getMaterial(hit.second);

    return material->getColor(0, hit.first, hit.second->getNormale(hit.first), ray.origin, scene);
}

Image render(int width, int height, std::shared_ptr<ray::IScene> scene, ray::Camera cam)
{
    Image img;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double u = double(i) / width;
            double v = double(j) / height;
            ray::Ray r = cam.ray(u, v);
            Maybe<PosShapePair> hit = scene->hit(r);

            if (hit.has_value() == false) {
                img.addPixel({static_cast<double>(i), static_cast<double>(j)}, {0, 0, 0});
            } else {
                img.addPixel({static_cast<double>(i), static_cast<double>(j)}, getHitColor(hit.value(), r, scene));
            }
        }
    }

    return img;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Invalid number of arguments." << std::endl;
        std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        return 84;
    }

    try {
        ray::NodeBuilder builder(argv[1]);
        auto nodes = builder.getRootNodes();

        if (nodes.empty()) {
            throw ray::CoreException("No root nodes found in the scene file.");
        }

        int width = 1920; // TEMPORARY: store in scene file?
        int height = 1080;
        ray::Camera cam(width, height);
        std::shared_ptr<ray::IScene> scene = std::dynamic_pointer_cast<ray::IScene>(getScene(nodes));
        Image img = render(width, height, scene, cam);

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
