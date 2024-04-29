//
// Created by Guillaume Tran on 26/04/2024.
//

#include "Plane.hpp"

Plane::Plane()
{

}

Maybe<Math::Point3D> Plane::hit(const Raytracer::Ray ray) {
    Math::Point3D center = getPosition();
    Math::Vector3D normal = getNormale(center);
//    Math::Vector3D d = ray.origin - center;
//    double product = d * normal;
//
//    if (fabs(product) < 0.0001)
//        return Maybe<Math::Point3D>();
//    double t = -product / (ray.direction * normal);
}

Math::Vector3D Plane::getNormale(const Math::Point3D point)
{
    Math::Matrix<3,1> normale;
    normale(0,0) = 0;
    normale(0,1) = 1;
    normale(0,2) = 0;
    Math::Vector3D vectorNormale;
    Math::Matrix<3,3> rotation = getRotation();

    normale = rotation * normale;
    vectorNormale.X = normale(0,0);
    vectorNormale.Y = normale(0,1);
    vectorNormale.Z = normale(0,2);
    return vectorNormale;
}