/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AMaterial.cpp
*/

#include "AMaterial.hpp"

#include <math/Vector2D.hpp>

namespace ray {

    ray::AMaterial::AMaterial(double refractionIndex) : ANode(ray::type::MATERIAL), _refractionIndex(refractionIndex)
    {
    }

    AMaterial::AMaterial(double refractionIndex, std::string normalMap) : ANode(ray::type::MATERIAL), _refractionIndex(refractionIndex)
    {
        _hasNormalMap = true;
        if (!_normalMap.loadFromFile(normalMap)) {
            throw ray::NodeError("IMaterial: Error happened while opening image at path [" + normalMap + "].", "AMaterial.cpp");
        }
    }

    Math::Vector3D AMaterial::normalFromMap(Math::Vector2D uv) const
    {
        if (_hasNormalMap == false)
            return {0, 0, 0};
        sf::Color color = _normalMap.getPixel(
            static_cast<unsigned int>(uv.first * _normalMap.getSize().x) % _normalMap.getSize().x,
            _normalMap.getSize().y - static_cast<unsigned int>(uv.second * _normalMap.getSize().y) % _normalMap.getSize().y
        );
        return {
            (static_cast<double>(color.r) / 255.f) * 2 - 1,
            (static_cast<double>(color.g) / 255.f) * 2 - 1,
            (static_cast<double>(color.b) / 255.f) * 2 - 1
        };
    }

    void AMaterial::setNormalMap(std::string normalMap)
    {
        _hasNormalMap = true;
        if (!_normalMap.loadFromFile(normalMap)) {
            throw ray::NodeError("IMaterial: Error happened while opening image at path [" + normalMap + "].", "AMaterial.cpp");
        }
    }

    double AMaterial::getRefractionIndex() const
    {
        return _refractionIndex;
    }

}
