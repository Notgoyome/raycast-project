/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"
#include "../../transformations/Transform.hpp"

Maybe<Math::Point3D> ray::PointLight::getPos() const
{
    std::shared_ptr<ray::INode> parent = getParent();

    while (parent) {
        if (parent->getType() == ray::type::TRANSFORM) {
            std::shared_ptr<ray::Transform> transform = std::dynamic_pointer_cast<ray::Transform>(parent);
            Math::Point3D pos = transform->getPosition();
            return Maybe{pos};
        }
        parent = parent->getParent();
    }
    return Maybe<Math::Point3D>{};
}

ray::PointLight::PointLight(RGB color) : ALight(color)
{
}

Math::Vector3D ray::PointLight::getIncidentVector(Math::Point3D pos) const
{
    Maybe<Math::Point3D> maybePos = getPos();
    Math::Point3D myPos;
    if (maybePos.has_value())
        myPos = maybePos.value();
    else
        myPos = {0, 0, 0};
    Math::Vector3D res = {myPos.X - pos.X, myPos.Y - pos.Y, myPos.Z - pos.Z};

    res /= res.length();
    return res;
}
