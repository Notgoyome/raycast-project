/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PointLight.hpp
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <map>
#include <Maybe.hpp>

#include "../ALight.hpp"

namespace ray {

    class PointLight : public ray::ALight {
    public:
        explicit PointLight(RGB color);
        ~PointLight() override = default;

        [[nodiscard]] Math::Vector3D getIncidentVector(Math::Point3D pos) const override;
    };

}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //POINTLIGHT_HPP
