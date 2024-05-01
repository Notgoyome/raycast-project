/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

#include <math/MatrixN.hpp>

#include "../../transformations/ITransform.hpp"

Math::Point3D ray::PointLight::getPos() const
{
    std::shared_ptr<ray::INode> parent = getParent();
    std::vector<Math::Matrix<4, 4>> transformations;
    Math::Matrix<4, 4> finalMatrix = Math::Matrix<4, 4>::identity();
    Math::Matrix<1, 4> pos = Math::Matrix<1, 4>{{{0, 0, 0, 1}}};

    while (parent) {
        if (parent->getType() == ray::type::TRANSFORM) {
            std::shared_ptr<ray::ITransform> transform = std::dynamic_pointer_cast<ray::ITransform>(parent);
            transformations.push_back(transform->getMatrix());
        }
        parent = parent->getParent();
    }
    for (int i = static_cast<int>(transformations.size()) - 1; i >= 0; i--) {
        finalMatrix = transformations[i] * finalMatrix;
    }
    Math::Matrix<4, 1> finalPos = finalMatrix * pos.T();
    return {finalPos(0, 0), finalPos(1, 0), finalPos(2, 0)};
}

ray::PointLight::PointLight(RGB color) : ALight(color)
{
}

Math::Vector3D ray::PointLight::getIncidentVector(Math::Point3D pos) const
{
    Math::Point3D myPos = getPos();
    Math::Vector3D res = {myPos.X - pos.X, myPos.Y - pos.Y, myPos.Z - pos.Z};

    res /= res.length();
    return res;
}
