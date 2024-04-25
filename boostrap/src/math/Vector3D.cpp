/*
** EPITECH PROJECT, 2024
** bootstrap-raytracer
** File description:
** Vector3D.cpp
*/

#include "../../include/Vector3D.hpp"
#include <cmath>

namespace Math {
    Vector3D Vector3D::operator+(const Vector3D &other) const
    {
        return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D & Vector3D::operator+=(const Vector3D &other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D &other) const
    {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3D & Vector3D::operator-=(const Vector3D &other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D Vector3D::operator*(const Vector3D &other) const
    {
        return Vector3D(X * other.X, Y * other.Y, Z * other.Z);
    }

    Vector3D & Vector3D::operator*=(const Vector3D &other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D &other) const
    {
        return Vector3D(X / other.X, Y / other.Y, Z / other.Z);
    }

    Vector3D & Vector3D::operator/=(const Vector3D &other)
    {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    double Vector3D::dot(const Vector3D &other) const
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    double Vector3D::length() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }
} // Math
