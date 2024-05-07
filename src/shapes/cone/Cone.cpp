//
// Created by Guillaume Tran on 02/05/2024.
//

#include "Cone.hpp"

float toRadians(float angle)
{
    return angle;
}

void ray::Cone::transform()
{
    if (_transform == false) {
        _transform = true;
    }
}

void ray::Cone::initValues()
{
    applyMatrix();
    setPosition();
}

Maybe<Math::Point3D> ray::Cone::hit(const ray::Ray& ray) const
{
    Math::Vector3D rayDir = ray.direction;
    Math::Point3D rayOrigin = ray.origin;
    float A = rayOrigin.X - center.X;
    float B = rayOrigin.Z - center.Z;
    float D = _height - rayOrigin.Y + center.Y;
    float tanTheta = pow(tan(toRadians(_radius/_height)), 2);
    float a = pow(rayDir.X, 2) + pow(rayDir.Z, 2) - tanTheta * pow(rayDir.Y, 2);
    float b = 2 * (rayDir.X * A + rayDir.Z * B - tanTheta * rayDir.Y * D);
    float c = pow(A, 2) + pow(B, 2) - tanTheta * pow(D, 2);
    float delta = b * b - 4 * a * c;

    if (delta < 0) {
        return Maybe<Math::Point3D>{};
    }
    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);
    float t = -1;
    if (t1 > t2) {
        t = t2;
    } else {
        t = t1;
    }

    float r = (rayOrigin.Y + t * rayDir.Y);
    if (_finite && (r < center.Y - _height || r > center.Y + _height)) {
        return Maybe<Math::Point3D>{};
    }
    return Maybe<Math::Point3D>{rayOrigin + rayDir * t};
}

Math::Vector3D ray::Cone::getNormale(const Math::Point3D& point, __attribute__((unused))const ray::Ray& camRay) const
{
    float r = sqrt(pow(point.X - center.X, 2) + pow(point.Z - center.Z, 2));
    Math::Vector3D normal = {point.X - center.X, r * tan(toRadians(_radius/_height)), point.Z - center.Z};
    return normal / normal.length();
}

void ray::Cone::setPosition()
{
    center = Scene::getPosition(*this);
}

void ray::Cone::setRadius(float radius)
{
    _radius = radius;
}

void ray::Cone::setHeight(float height)
{
    _height = height;
}

extern "C" ray::INode *create(std::map<std::string, std::string>& properties)
{
    ray::Cone* cone = new ray::Cone();
    if (properties.find("height") != properties.end()) {
        cone->setHeight(std::stof(properties["height"]));
    } else {
        throw std::invalid_argument("Cone must have a height");
    }
    if (properties.find("radius") != properties.end()) {
        cone->setRadius(std::stof(properties["radius"]));
    } else {
        throw std::invalid_argument("Cone must have a radius");
    }
    if (properties.find("finite") != properties.end()) {
        if (properties["finite"] == "true") {
            cone->setFinite(true);
        } else if (properties["finite"] == "false") {
            cone->setFinite(false);
        } else {
            throw std::invalid_argument("Cone finite must be true or false");
        }
    } else {
        cone->setFinite(false);
    }
    return cone;
}
