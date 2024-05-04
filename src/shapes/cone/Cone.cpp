//
// Created by Guillaume Tran on 02/05/2024.
//

#include "Cone.hpp"

ray::Cone::Cone()
{
}

float toRadians(float angle)
{
    return angle;
}

Math::Vector3D ray::Cone::getAxis()
{
    Math::Vector3D axis = {0, 1, 0};
    Math::Matrix<4,4> axisMatrix;
    axisMatrix(0,0) = 0;
    axisMatrix(1,0) = 1;
    axisMatrix(2,0) = 0;
    axisMatrix(3,0) = 0;

    axisMatrix = _transformMatrix * axisMatrix;
    std::cout << _transformMatrix << std::endl;
    axis.X = axisMatrix(0,0);
    axis.Y = axisMatrix(1,0);
    axis.Z = axisMatrix(2,0);

    return axis / axis.length();
}

Maybe<Math::Point3D> ray::Cone::hit(const ray::Ray& ray) {
    if (_transform == false) {
        applyMatrix();
        setPosition();
        _transform = true;
    }
    float A = ray.origin.X - center.X;
    float B = ray.origin.Z - center.Z;
    float D = _height - ray.origin.Y + center.Y;
    float tanTheta = pow(tan(toRadians(_radius/_height)), 2);
    float a = pow(ray.direction.X, 2) + pow(ray.direction.Z, 2) - tanTheta * pow(ray.direction.Y, 2);
    float b = 2 * (ray.direction.X * A + ray.direction.Z * B - tanTheta * ray.direction.Y * D);
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

    float r = ray.origin.Y + t * ray.direction.Y;
    if (r < center.Y || r > center.Y + _height) {
        return Maybe<Math::Point3D>{};
    }
    return Maybe<Math::Point3D>{ray.origin + ray.direction * t};
}

Math::Vector3D ray::Cone::getNormale(const Math::Point3D& point, const ray::Ray& camRay)
{
    (ray::Ray)camRay;
    if (_transform == false) {
        applyMatrix();
        setPosition();
        _transform = true;
    }
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
    }
    if (properties.find("radius") != properties.end()) {
        cone->setRadius(std::stof(properties["radius"]));
    }
    // Continuez pour d'autres propriétés comme la position, l'orientation, etc.
    return cone;
}