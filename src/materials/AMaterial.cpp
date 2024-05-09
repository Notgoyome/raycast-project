/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AMaterial.cpp
*/

#include "AMaterial.hpp"

namespace ray {

    ray::AMaterial::AMaterial(double refractionIndex) : ANode(ray::type::MATERIAL), _refractionIndex(refractionIndex)
    {
    }

    double AMaterial::getRefractionIndex() const
    {
        return _refractionIndex;
    }

}
