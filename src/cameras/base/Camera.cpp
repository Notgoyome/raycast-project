/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

namespace ray {
    Camera::Camera(double width, double height) : screen(
        Math::Point3D{
            0, 0, 0
        }, Math::Vector3D{width, 0, 0},
        Math::Vector3D{0, height, 0}
        )
    {
        origin = {0, 0, -2000};
    }

    Ray Camera::ray(double u, double v) const
    {
        Math::Point3D pointAt = screen.pointAt(u, v);

        return {origin, Math::Vector3D{pointAt.X - origin.X, pointAt.Y - origin.Y, pointAt.Z - origin.Z}};
    }
} // Raytracer
