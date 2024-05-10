/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SuperMaterial.cpp
*/

#include "SuperMaterial.hpp"

namespace ray {
    SuperMaterial::SuperMaterial(
        double specularExponent,
        Math::Matrix<1, 3> ka,
        Math::Matrix<1, 3> kd,
        Math::Matrix<1, 3> ks,
        __attribute__((unused))Math::Matrix<1, 3> ke,
        double refractionIndex,
        double transparency,
        double shadowQuality,
        double ambiantOccQuality) : AMaterial(refractionIndex),
            _kd(kd),
            _ka(ka),
            _phong(
                {},
                0.05,
                specularExponent,
                shadowQuality,
                ambiantOccQuality,
                transparency,
                ks
            )
    {
    }

    RGB SuperMaterial::getColor(int recursive, Math::Point3D collisionPoint,
        Math::Vector3D normale, Math::Point3D camPos,
        const std::shared_ptr<ray::IShape> &shape,
        const std::shared_ptr<ray::IScene> &scene) const
    {
        Math::Vector3D view = {camPos.X - collisionPoint.X, camPos.Y - collisionPoint.Y, camPos.Z - collisionPoint.Z};
        view /= view.length();

        if (recursive > REFLECTION_RECURSION_LIMIT)
            return RGB{
                static_cast<unsigned int>(_kd(0, 0) * 255),
                static_cast<unsigned int>(_kd(0, 1) * 255),
                static_cast<unsigned int>(_kd(0, 2) * 255)
            };
        return _phong.calculateColor(_kd, _ka, scene, shape, view, collisionPoint, normale, recursive);
    }

    void SuperMaterial::setSkybox()
    {
        _phong.setIa(1);
    }
}
