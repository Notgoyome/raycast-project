/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.hpp
*/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"
#include "math/Rectangle3D.hpp"
#include "math/Point3D.hpp"

namespace ray {

    class Camera {
    public:
        Math::Point3D origin{0, 0, 0};
        Math::Rectangle3D screen;

        Camera(double width, double height);

        [[nodiscard]] ray::Ray ray(double u, double v) const;
    };

} // Raytracer

#endif //CAMERA_HPP
