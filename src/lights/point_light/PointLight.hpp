/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.hpp
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "../ALight.hpp"

namespace ray {

    class PointLight : public ray::ALight {
        Math::Point3D _pos;

    public:
        PointLight(RGB color, Math::Point3D pos);

        [[nodiscard]] Math::Vector3D getIncidentVector(Math::Point3D pos) const override;
    };

}

#endif //POINTLIGHT_HPP
