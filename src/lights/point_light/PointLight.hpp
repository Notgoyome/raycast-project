/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.hpp
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <Maybe.hpp>

#include "../ALight.hpp"

namespace ray {

    class PointLight : public ray::ALight {
    private:
        Math::Point3D getPos() const;
    public:
        explicit PointLight(RGB color);
        ~PointLight() override = default;

        [[nodiscard]] Math::Vector3D getIncidentVector(Math::Point3D pos) const override;
    };

}

#endif //POINTLIGHT_HPP
