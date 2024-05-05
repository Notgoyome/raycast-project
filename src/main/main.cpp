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

    return material->getColor(0, hit.first, hit.second->getNormale(hit.first, ray), ray.origin, scene);
}

RGB renderPixel(
    const std::shared_ptr<ray::IScene>& scene,
    const std::shared_ptr<ray::ICamera>& cam, double u, double v,
    RGB backgroundColor)
{
    ray::Ray r = cam->ray(u, v);
    Maybe<PosShapePair> hit = scene->hit(r);

    if (hit.has_value() == false) {
        return backgroundColor;
    } else {
        return getHitColor(hit.value(), r, scene);
    }
}

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
            RGB color = renderPixel(scene, cam, u, v, backgroundColor);
            img.addPixel(Math::Vector2D{static_cast<double>(i - startI), static_cast<double>(j - startJ)}, color);
        }
        std::cout << "Rendering: " << i - startI << "/" << width << std::endl;
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
        image_data_t imageData = builder.getImageData();

        if (nodes.empty()) {
            throw ray::CoreException("No root nodes found in the scene file.");
        }

        std::shared_ptr<ray::IScene> scene = std::dynamic_pointer_cast<ray::IScene>(getScene(nodes));
        std::shared_ptr<ray::ICamera> camera = getCamera(scene);
        Image img = render(imageData.width, imageData.height, scene, camera, backgroundColor);
        ray::Renderer renderer;
        renderer.renderPpmImage(img, imageData.filename);
        renderer.renderSfmlImage(img);

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
