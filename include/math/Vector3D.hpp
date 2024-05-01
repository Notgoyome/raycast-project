/*
** EPITECH PROJECT, 2024
** bootstrap-raytracer
** File description:
** Vector3D.hpp
*/

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <Maybe.hpp>
#include <string>

namespace Math {

    class Vector3D {
    public:
        double X;
        double Y;
        double Z;

        // CONSTR DESTRUCT
        Vector3D() : X(0), Y(0), Z(0) {}
        Vector3D(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {}

        Vector3D(const Vector3D& other) = default;
        Vector3D(Vector3D&& other) = default;

        ~Vector3D() = default;

        // OPERATORS
        Vector3D& operator=(const Vector3D& other) = default;
        Vector3D& operator=(Vector3D&& other) = default;

        Vector3D operator+(const Vector3D& other) const;
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        Vector3D& operator-=(const Vector3D& other);
        Vector3D operator*(const Vector3D& other) const;
        Vector3D operator*(double val) const;
        Vector3D& operator*=(const Vector3D& other);
        Vector3D& operator*=(double val);
        Vector3D operator/(const Vector3D& other) const;
        Vector3D operator/(double val) const;
        Vector3D& operator/=(const Vector3D& other);
        Vector3D& operator/=(double val);

        [[nodiscard]] double dot(const Vector3D& other) const;

        // GETTERS
        [[nodiscard]] double length() const;
        [[nodiscard]] static Maybe<Vector3D> fromStr(std::string str);
    };

} // Math

#endif //VECTOR3D_HPP
