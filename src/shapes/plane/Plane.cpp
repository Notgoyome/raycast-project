//
// Created by Guillaume Tran on 26/04/2024.
//

#include "Plane.hpp"

ray::Plane::Plane()
{

}

Maybe<Math::Point3D> ray::Plane::hit(const ray::Ray& ray) {
    Math::Vector3D vectorNormale = getNormale(Math::Point3D{0,0,0});
    Math::Point3D point = getPosition();
    double t = 0;
    double denom = (vectorNormale.X * ray.direction.X +
                vectorNormale.Y * ray.direction.Y +
                vectorNormale.Z * ray.direction.Z);
    if (denom < 1e-6) {
        return Maybe<Math::Point3D>{};
    }
    t = ((point.X - ray.origin.X) * vectorNormale.X +
            (point.Y - ray.origin.Y) * vectorNormale.Y +
            (point.Z - ray.origin.Z) * vectorNormale.Z) / denom;
    if (t < 0) {
        return Maybe<Math::Point3D>{};
    }
    return Maybe<Math::Point3D>{ray.origin + ray.direction * t};
}

Math::Vector3D ray::Plane::getNormale(__attribute__((unused))const Math::Point3D& point)
{
    Math::Matrix<4,1> normale;
    normale(0,0) = 0;
    normale(1,0) = 1;
    normale(2,0) = 0;
    normale(3,0) = 0;
    Math::Vector3D vectorNormale;

    normale = _transformMatrix * normale;
    vectorNormale.X = normale(0,0);
    vectorNormale.Y = normale(1,0);
    vectorNormale.Z = normale(2,0);
    return vectorNormale;
}

extern "C" ray::Plane *create(__attribute__((unused))std::map<std::string, std::string>& properties)
{
    return new ray::Plane();
}

extern "C" ray::type getType()
{
    return ray::type::SHAPE;
}