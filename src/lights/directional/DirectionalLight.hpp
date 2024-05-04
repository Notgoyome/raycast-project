/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** DirectionalLight.hpp
*/

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include <map>

#include "../ALight.hpp"

namespace ray {

    class DirectionalLight : public ALight {
        RGB _color;
        Math::Vector3D _direction;

    public:
        DirectionalLight(RGB color, Math::Vector3D direction);

        Math::Vector3D getIncidentVector(Math::Point3D pos) override;
        Math::Point3D getPos() override;
    };

} // ray

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //DIRECTIONALLIGHT_HPP
