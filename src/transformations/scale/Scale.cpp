/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scale.cpp
*/

#include "Scale.hpp"
#include <cmath>


namespace ray {

    Scale::Scale(Math::Vector3D scale)
    {
        _matrix = Math::Matrix<4, 4>{{{scale.X, 0, 0, 0}, {0, scale.Y, 0, 0}, {0, 0, scale.Z, 0}, {0, 0, 0, 1}}};
    }

} // ray
