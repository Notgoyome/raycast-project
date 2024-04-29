/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Renderer
*/

#include "Renderer.hpp"

ray::Renderer::Renderer()
{
    _width = 0;
    _height = 0;
}

ray::Renderer::~Renderer()
{
}

void ray::Renderer::getSize(const std::map<Math::Vector2D, RGB> &image)
{
    for (const auto& pair : image) {
        _width = std::max(_width, (int)pair.first.first);
        _height = std::max(_height, (int)pair.first.second);
    }
}

void ray::Renderer::renderPpmImage(Image image, std::string filename)
{
    auto color = RGB(0, 0, 0);
    std::ofstream file(filename);
    this->getSize(image.getMap());
    file << "P3\n";
    file << _width << " " << _height << "\n";
    file << "255\n";
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            color = image.getPixel(Math::Vector2D(j, i));
            file << color.R << " " << color.G << " " << color.B;
            if (j != _width - 1)
                file << "\t";
        }
        file << "\n";
    }
    file.close();
}
