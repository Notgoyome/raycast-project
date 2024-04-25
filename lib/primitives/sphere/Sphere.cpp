//
// Created by Guillaume Tran on 25/04/2024.
//

#include "Sphere.hpp"

bool Sphere::hit(const Raytracer::Ray &ray) {
    Math::Point3D oc = ray.origin - center;
    float a = (ray.direction.X * ray.direction.X +
                ray.direction.Y * ray.direction.Y +
                ray.direction.Z * ray.direction.Z);
    float b = 2.0 * (oc.X * ray.direction.X +
                     oc.Y * ray.direction.Y +
                     oc.Z * ray.direction.Z);
    float c = oc.X * oc.X +
                oc.Y * oc.Y +
                oc.Z * oc.Z -
                radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}