/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** ALight.cpp
*/

#include "ALight.hpp"

void ray::ALight::setColor(RGB color)
{
    _color = color;
}

RGB ray::ALight::getColor() const
{
    return _color;
}
