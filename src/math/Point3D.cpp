/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3D.cpp
*/

#include "../../include/Point3D.hpp"

namespace Math {
    Point3D Point3D::operator+(const Vector3D &vect) const
    {
        return Point3D(X + vect.X, Y + vect.Y, Z + vect.Z);
    }

    Point3D Point3D::operator-(const Vector3D &vect) const
    {
        return Point3D(X - vect.X, Y - vect.Y, Z - vect.Z);
    }
} // Math
