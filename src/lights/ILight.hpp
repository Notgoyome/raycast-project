/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** ILight.hpp
*/

#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "INode.hpp"
#include "math/Vector3D.hpp"
#include "RGB.hpp"
#include "math/Point3D.hpp"

namespace ray {

    class ILight : virtual public INode {
    public:
        virtual ~ILight() = default;

        virtual void setColor(RGB color) = 0;

        [[nodiscard]] virtual RGB getColor() const = 0;
        [[nodiscard]] virtual Math::Vector3D getIncidentVector(Math::Point3D pos) = 0;
        [[nodiscard]] virtual Math::Point3D getPos() = 0;
    };

}

#endif
