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
        Math::Point3D _myPos;
        bool _gotPos = false;
    public:
        explicit PointLight(RGB color);
        ~PointLight() override = default;

        [[nodiscard]] ray::Ray getIncidentVector(Math::Point3D pos) override;
        [[nodiscard]] Math::Point3D getPos() override;
    };

}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //POINTLIGHT_HPP
