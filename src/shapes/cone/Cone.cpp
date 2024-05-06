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

void ray::Cone::transform()
{
    if (_transform == false) {
        applyMatrix();
        setPosition();
        _transform = true;
    }
}

Math::Vector3D ray::Cone::getAxis()
{
    transform();
    _axis = {0, 1, 0};
    Math::Matrix<4,4> axisMatrix;
    axisMatrix(0,0) = 0;
    axisMatrix(1,0) = 1;
    axisMatrix(2,0) = 0;
    axisMatrix(3,0) = 0;
    axisMatrix = _transformMatrix * axisMatrix;
    _axis.X = axisMatrix(0,0);
    _axis.Y = axisMatrix(1,0);
    _axis.Z = axisMatrix(2,0);
    _axis = _axis / _axis.length();
    std::cout << "axis: " << _axis.X << " " << _axis.Y << " " << _axis.Z << std::endl;
    exit(0);
    return _axis;
}

Math::Vector3D rotateVector(Math::Matrix<3,3> rotationMatrix, Math::Vector3D vector)
{
    Math::Vector3D res;
    res.X = rotationMatrix(0,0) * vector.X +
            rotationMatrix(0,1) * vector.Y +
            rotationMatrix(0,2) * vector.Z;
    res.Y = rotationMatrix(1,0) * vector.X +
            rotationMatrix(1,1) * vector.Y +
            rotationMatrix(1,2) * vector.Z;
    res.Z = rotationMatrix(2,0) * vector.X +
            rotationMatrix(2,1) * vector.Y +
            rotationMatrix(2,2) * vector.Z;
    return res;
}

Math::Point3D MatrixMultiplyPoint(Math::Matrix<4, 4> matrix, Math::Point3D point)
{
    (void)matrix;
    return point;
}

Maybe<Math::Point3D> ray::Cone::hit(const ray::Ray& ray) {
    transform();
    //Math::Vector3D rayDir = rotateVector(getRotation(), ray.direction);
    //Math::Point3D rayOrigin = MatrixMultiplyPoint(_transformMatrix, ray.origin);
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
    if (_finite && (r < center.Y - _height/2 || r > center.Y + _height)) { //|| r < center.Y + _height/2) {
        return Maybe<Math::Point3D>{};
    }
    return Maybe<Math::Point3D>{rayOrigin + rayDir * t};
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