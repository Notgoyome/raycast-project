/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RedBasicMaterial.cpp
*/

#include "BasicMaterial.hpp"

ray::BasicMaterial::BasicMaterial(RGB color,
    double shadowQuality,
    double ambiantOccQuality,
    double roughness) : _color(color),
    _phong({},
        0.05,
        50,
        shadowQuality,
        ambiantOccQuality,
        Math::Matrix<1, 3>({{1, 1, 1}}),
        Math::Matrix<1, 3>{{{0, 0, 0}}},
        Math::Matrix<1, 3>{{{roughness, roughness, roughness}}})
{
    _phong.setKd(Math::Matrix<1, 3>({{color.R / 255.f, color.G / 255.f, color.B / 255.f}}));
}

RGB ray::BasicMaterial::getColor(int recursive, Math::Point3D collisionPoint,
                                 Math::Vector3D normale, Math::Point3D camPos,
                                 __attribute__((unused))const std::shared_ptr<ray::IShape>& shape,
                                 const std::shared_ptr<ray::IScene> &scene) const
{
    Math::Vector3D view = {camPos.X - collisionPoint.X, camPos.Y - collisionPoint.Y, camPos.Z - collisionPoint.Z};
    view /= view.length();

    if (recursive > REFLECTION_RECURSION_LIMIT)
        return _color;
    return _phong.calculateColor(scene, view, collisionPoint, normale, recursive);
}
