/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rotation.hpp
*/

#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "../ATransform.hpp"
#include "math/Vector3D.hpp"

namespace ray {

    class Rotation : public ATransform {
    public:
        explicit Rotation(Math::Vector3D rotation);
    };

} // ray

#endif //ROTATION_HPP
