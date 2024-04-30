/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rotation.cpp
*/

#include "Rotation.hpp"

namespace ray {

    Math::Matrix<4, 4> getRotationMatrixX(double angle)
    {
        return Math::Matrix<4, 4>{{{1, 0, 0, 0}, {0, cos(angle), sin(angle), 0}, {0, -sin(angle), cos(angle), 0}, {0, 0, 0, 1}}};
    }

    Math::Matrix<4, 4> getRotationMatrixY(double angle)
    {
        return Math::Matrix<4, 4>{{{cos(angle), 0, -sin(angle), 0}, {0, 1, 0, 0}, {sin(angle), 0, cos(angle), 0}, {0, 0, 0, 1}}};
    }

    Math::Matrix<4, 4> getRotationMatrixZ(double angle)
    {
        return Math::Matrix<4, 4>{{{cos(angle), -sin(angle), 0, 0}, {sin(angle), cos(angle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
    }

    Rotation::Rotation(Math::Vector3D rotation)
    {
        Math::Matrix<4, 4> res = getIdentityMatrix();
        Math::Matrix<4, 4> temp;

        if (rotation.X != 0)
            res = getRotationMatrixX(rotation.X) * res;
        if (rotation.Y != 0)
            res = getRotationMatrixY(rotation.Y) * res;
        if (rotation.Z != 0)
            res = getRotationMatrixZ(rotation.Z) * res;

        _matrix = res;
    }
} // ray
