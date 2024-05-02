/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RedBasicMaterial.cpp
*/

#include "BasicMaterial.hpp"

ray::Ray getReflectionRay(Math::Vector3D normale, ray::Ray ray)
{
    Math::Vector3D reflection = ray.direction - (normale * 2 * ray.direction.dot(normale));
    Math::Point3D origin = {normale.X, normale.Y, normale.Z};

    return {origin, reflection};
}

double getVectorAngle(Math::Vector3D vec1, Math::Vector3D vec2)
{
    return acos(vec1.dot(vec2) / (vec1.length() * vec2.length()));
}

ray::BasicMaterial::BasicMaterial(RGB color) : _color(color),
                                               _phong({},
                                                   0.05,
                                                   50,
                                                   Math::Matrix<1, 3>({{1, 1, 1}}),
                                                   Math::Matrix<1, 3>{{{0, 0, 0}}},
                                                   Math::Matrix<1, 3>{{{0.1, 0.5, 0.5}}},
                                                   {0, 0, 0},
                                                   {0, 0, 0},
                                                   {0, 0, 0})
{
    _phong.setKd(Math::Matrix<1, 3>({{color.R / 255.f, color.G / 255.f, color.B / 255.f}}));
}

RGB ray::BasicMaterial::getColor(__attribute__((unused))int recursive, Math::Point3D collisionPoint,
    Math::Vector3D normale, Math::Point3D camPos,
    const std::shared_ptr<ray::IScene> &scene)
{
    Math::Vector3D view = {camPos.X - collisionPoint.X, camPos.Y - collisionPoint.Y, camPos.Z - collisionPoint.Z};
    view /= view.length();

    _phong.setLights(scene->getLights());
    _phong.setView(view);
    _phong.setNormale(normale);
    _phong.setPos(collisionPoint);
    return _phong.calculateColor(scene->getShapes());
}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes)
{
    if (attributes.find("color") == attributes.end())
        throw ray::NodeError("IMaterial: missing color attribute", "BasicMaterial.cpp");
    Maybe<RGB> color = RGB::fromStr(attributes.at("color"));
    if (!color.has_value())
        throw ray::NodeError("IMaterial: invalid color attribute", "BasicMaterial.cpp");
    return new ray::BasicMaterial(color.value());
}
