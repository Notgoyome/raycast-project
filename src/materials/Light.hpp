/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Light.hpp
*/

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "math/MatrixN.hpp"
#include "math/Point3D.hpp"

class Light {
    Math::Matrix<1, 3> _specularIntensity;
    Math::Matrix<1, 3> _diffuseIntensity;
    Math::Point3D _position;

public:
    Light(Math::Matrix<1, 3> specularIntensity, Math::Matrix<1, 3> diffuseIntensity, Math::Point3D position)
        : _specularIntensity(specularIntensity), _diffuseIntensity(diffuseIntensity), _position(position) {}
    ~Light() = default;

    void setSpecularIntensity(Math::Matrix<1, 3> specularIntensity) { _specularIntensity = specularIntensity; }
    void setDiffuseIntensity(Math::Matrix<1, 3> diffuseIntensity) { _diffuseIntensity = diffuseIntensity; }
    void setPosition(Math::Point3D position) { _position = position; }

    [[nodiscard]] Math::Matrix<1, 3> getSpecularIntensity() const { return _specularIntensity; }
    [[nodiscard]] Math::Matrix<1, 3> getDiffuseIntensity() const { return _diffuseIntensity; }
    [[nodiscard]] Math::Point3D getPosition() const { return _position; }
};



#endif //LIGHT_HPP
