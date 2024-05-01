/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"
#include "../../scenes/Scene.hpp"

ray::PointLight::PointLight(RGB color) : ALight(color)
{
}

Math::Vector3D ray::PointLight::getIncidentVector(Math::Point3D pos) const
{
    Math::Point3D myPos = Scene::getPosition(*this);
    Math::Vector3D res = {myPos.X - pos.X, myPos.Y - pos.Y, myPos.Z - pos.Z};

    res /= res.length();
    return res;
}
