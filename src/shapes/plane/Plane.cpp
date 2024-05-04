//
// Created by Guillaume Tran on 26/04/2024.
//

#include "Plane.hpp"

ray::Plane::Plane()
{
    _transform = false;
}

Maybe<Math::Point3D> ray::Plane::hit(const ray::Ray& ray) {
    Math::Vector3D vectorNormale = getNormale(Math::Point3D{0,0,0}, ray);

    if (vectorNormale.dot(ray.direction) == 0) // perpendicular
        return Maybe<Math::Point3D>{};
    Math::Point3D point = getPosition();
    double t = 0;
    double denom = vectorNormale.dot({point.X, point.Y, point.Z});
    t = (denom - (vectorNormale.X * ray.origin.X + vectorNormale.Y * ray.origin.Y + vectorNormale.Z * ray.origin.Z)) / vectorNormale.dot(ray.direction);
    if (t < 0) {
        return Maybe<Math::Point3D>{};
    }
    return Maybe{ray.origin + ray.direction * t};
}

void ray::Plane::setPosition()
{
    center = Scene::getPosition(*this);
}

Math::Vector3D ray::Plane::getNormale(__attribute__((unused))const Math::Point3D& point, const ray::Ray& camRay)
{
    if (_transform == false) {
        applyMatrix();
        setPosition();
        _transform = true;
    }
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

    if (vectorNormale.dot(camRay.direction) > 0)
        vectorNormale = vectorNormale * -1;
    return vectorNormale / vectorNormale.length();
}

extern "C" ray::INode *create(__attribute__((unused))std::map<std::string, std::string>& properties)
{
    return new ray::Plane();
}