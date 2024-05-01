/*
** EPITECH PROJECT, 2024
** bootstrap-raytracer
** File description:
** Vector3D.cpp
*/

#include "math/Vector3D.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace Math {
    bool Vector3D::operator==(const Vector3D &other) const
    {
        return X == other.X && Y == other.Y && Z == other.Z;
    }

    bool Vector3D::operator!=(const Vector3D &other) const
    {
        return X != other.X || Y != other.Y || Z != other.Z;
    }

    Vector3D Vector3D::operator+(const Vector3D &other) const
    {
        return Vector3D{X + other.X, Y + other.Y, Z + other.Z};
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
        return Vector3D{X - other.X, Y - other.Y, Z - other.Z};
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
        return Vector3D{X * other.X, Y * other.Y, Z * other.Z};
    }

    Vector3D Vector3D::operator*(double val) const
    {
        return Vector3D{X * val, Y * val, Z * val};
    }

    Vector3D & Vector3D::operator*=(const Vector3D &other)
    {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    Vector3D & Vector3D::operator*=(double val)
    {
        X *= val;
        Y *= val;
        Z *= val;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D &other) const
    {
        return Vector3D{X / other.X, Y / other.Y, Z / other.Z};
    }

    Vector3D Vector3D::operator/(double val) const
    {
        return Vector3D{X / val, Y / val, Z / val};
    }

    Vector3D & Vector3D::operator/=(const Vector3D &other)
    {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    Vector3D & Vector3D::operator/=(double val)
    {
        X /= val;
        Y /= val;
        Z /= val;
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

    Maybe<double> parseSingleAttr(char attrName, std::string str)
    {
        double res;

        if (str[0] != attrName)
            return Maybe<double>{};
        if (str.find(':') == std::string::npos)
            return Maybe<double>{};
        str.erase(0, str.find(':') + 1);

        try {
            res = std::stod(str);
        } catch (std::invalid_argument&) {
            return Maybe<double>{};
        }
        return Maybe{res};
    }

    Maybe<Vector3D> Vector3D::fromStr(std::string str)
    {
        if (str[0] != '{' || str[str.size() - 1] != '}')
            return Maybe<Vector3D>{};
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

        Maybe<double> maybeNum1 = parseSingleAttr('x', str);
        if (!maybeNum1.has_value())
            return Maybe<Vector3D>{};

        str.erase(0, str.find(';') + 1);
        Maybe<double> maybeNum2 = parseSingleAttr('y', str);
        if (!maybeNum2.has_value())
            return Maybe<Vector3D>{};

        str.erase(0, str.find(';') + 1);
        Maybe<double> maybeNum3 = parseSingleAttr('z', str);
        if (!maybeNum3.has_value())
            return Maybe<Vector3D>{};

        return Maybe{Vector3D{maybeNum1.value(), maybeNum2.value(), maybeNum3.value()}};
    }

} // Math
