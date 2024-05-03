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

std::shared_ptr<ray::INode> getScene(const std::vector<std::shared_ptr<ray::INode>>& nodes)
{
    for (auto node : nodes) {
        if (node->getType() == ray::type::SCENE) {
            return node;
        }
    }
    return nullptr;
}

std::shared_ptr<ray::ICamera> getCamera(const std::shared_ptr<ray::IScene>& scene)
{
    auto cameras = scene->getCameras();
    return cameras[0];
}

RGB getHitColor(const PosShapePair& hit, ray::Ray ray, const std::shared_ptr<ray::IScene>& scene)
{
    std::shared_ptr<ray::IMaterial> material = ray::Scene::getMaterial(hit.second);

    return material->getColor(0, hit.first, hit.second->getNormale(hit.first), ray.origin, scene);
}

Image render(unsigned int width, unsigned int height,
    const std::shared_ptr<ray::IScene>& scene,
    const std::shared_ptr<ray::ICamera>& cam, RGB backgroundColor)
{
    Image img;

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            double u = double(i) / width;
            double v = double(j) / height;
            ray::Ray r = cam->ray(u, v);
            Maybe<PosShapePair> hit = scene->hit(r);

            if (hit.has_value() == false) {
                img.addPixel({static_cast<double>(i), static_cast<double>(j)}, backgroundColor);
            } else {
                img.addPixel({static_cast<double>(i), static_cast<double>(j)}, getHitColor(hit.value(), r, scene));
            }
        }
        std::cout << "Progression: " << i * 100 / width << "%" << std::endl;
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
        const auto& nodes = builder.getRootNodes();
        RGB backgroundColor = builder.getBackgroundColor();

        if (nodes.empty()) {
            throw ray::CoreException("No root nodes found in the scene file.");
        }

        std::shared_ptr<ray::IScene> scene = std::dynamic_pointer_cast<ray::IScene>(getScene(nodes));
        std::shared_ptr<ray::ICamera> camera = getCamera(scene);
        std::pair size = camera->getResolution();
        Image img = render(size.first, size.second, scene, camera, backgroundColor);
        ray::Renderer renderer;
        renderer.renderSfmlImage(img);

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
