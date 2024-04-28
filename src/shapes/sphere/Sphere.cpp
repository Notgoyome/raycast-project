//
// Created by Guillaume Tran on 25/04/2024.
//

#include "Sphere.hpp"

RayTracer::Sphere::Sphere(float radius, Math::Point3D center) : radius(radius), center(center)
{

}

Maybe<Math::Point3D> closestPoint(const Raytracer::Ray &ray, float discriminant, float a, float b)
{
    float t = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t < 0 && t2 < 0)
        return Maybe<Math::Point3D>();
    if (t < 0)
        return Maybe{Math::Point3D(ray.origin + ray.direction * t2)};
    if (t2 < 0)
        return Maybe{Math::Point3D(ray.origin + ray.direction * t)};
    if (t < t2)
        return Maybe{Math::Point3D(ray.origin + ray.direction * t)};
    return Maybe{Math::Point3D(ray.origin + ray.direction * t2)};
}

Maybe<Math::Point3D> RayTracer::Sphere::hit(const Raytracer::Ray &ray)
{
    Math::Point3D center = getPosition();
    Math::Point3D oc = ray.origin - center;

    float a = (ray.direction.X * ray.direction.X +
            ray.direction.Y * ray.direction.Y +
            ray.direction.Z * ray.direction.Z);
    float b = 2.0 * (oc.X * ray.direction.X +
                    oc.Y * ray.direction.Y +
                    oc.Z * ray.direction.Z);
    float c = oc.X * oc.X + oc.Y * oc.Y + oc.Z * oc.Z - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return Maybe<Math::Point3D>();
    return closestPoint(ray, discriminant, a, b);
}

Math::Vector3D RayTracer::Sphere::getNormale(const Math::Point3D point)
{
    Math::Vector3D normale = {point.X - center.X,
                              point.Y - center.Y,
                              point.Z - center.Z};
    return normale / normale.length();
}