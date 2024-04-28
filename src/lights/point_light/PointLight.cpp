/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

ray::PointLight::PointLight(RGB color, Math::Point3D pos) : ALight(color), _pos(pos)
{
}

Math::Vector3D ray::PointLight::getIncidentVector(Math::Point3D pos) const
{
    Math::Vector3D res = {_pos.X - pos.X, _pos.Y - pos.Y, _pos.Z - pos.Z};

    res /= res.length();
    return res;
}
