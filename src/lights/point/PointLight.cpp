/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"
#include "../../scenes/base/Scene.hpp"

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

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes)
{
    if (attributes.find("color") == attributes.end())
        throw ray::NodeError("ILight: missing color attribute", "PointLight.cpp");
    Maybe<RGB> color = RGB::fromStr(attributes.at("color"));
    if (!color.has_value())
        throw ray::NodeError("ILight: invalid color attribute", "PointLight.cpp");
    return new ray::PointLight(color.value());
}
