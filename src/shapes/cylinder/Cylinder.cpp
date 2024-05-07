/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"

void ray::Cylinder::initValues()
{
    setPosition();
    setRadius();
    setDirection();
}

void ray::Cylinder::setRadius()
{
    Math::Vector3D scale = getScale();

    _radius = scale.X;
}

void ray::Cylinder::setPosition()
{
    _position = Scene::getPosition(*this);
}

void ray::Cylinder::setDirection()
{
    // Math::Matrix rotation = getRotation();
    // std::vector<std::vector<double>> values = {{0, 1, 0}};
    // Math::Matrix<3, 1> iniDirection(values);
    // Math::Matrix rotation2 = getRotation();
    // Math::Matrix<3, 3> result = rotation * iniDirection;
    _direction = Math::Vector3D(0, 1, 0); 
}

Math::Vector3D pointTimesVector(Math::Point3D P, Math::Vector3D V)
{
    Math::Vector3D result;
    result.X = P.X * V.X;
    result.Y = P.Y * V.Y;
    result.Z = P.Z * V.Z;
    return result;
}

Math::Vector3D pointSubVector(Math::Point3D P, Math::Vector3D V)
{
    Math::Vector3D result;
    result.X = P.X - V.X;
    result.Y = P.Y - V.Y;
    result.Z = P.Z - V.Z;
    return result;
}

double calcA(Math::Vector3D V, Math::Vector3D Va)
{
    Math::Vector3D Vb = V - ((V * Va) * Va);
    Vb = Vb * Vb;
    return Vb.X + Vb.Y + Vb.Z;
}

double calcB(Math::Vector3D V, Math::Vector3D Va, Math::Point3D P, Math::Point3D Pa)
{
    Math::Vector3D Vb = V - ((V * Va) * Va);
    Math::Point3D detP = P - Pa;
    Math::Vector3D Vc = pointTimesVector(detP, Va);
    Vc = Vc * Va;
    Vc = pointSubVector(detP, Vc);
    Math::Vector3D Vd = Vb * Vc;
    Vd.X = 2 * Vd.X;
    Vd.Y = 2 * Vd.Y;
    Vd.Z = 2 * Vd.Z;
    return Vd.X + Vd.Y + Vd.Z;
}

double calcC(Math::Point3D P, Math::Point3D Pa, Math::Vector3D Va, double R)
{
    Math::Point3D detP = P - Pa;
    Math::Vector3D Vb = pointTimesVector(detP, Va);
    Vb = Vb * Va;
    Vb = pointSubVector(detP, Vb);
    Vb = Vb * Vb;
    return Vb.X + Vb.Y + Vb.Z - (R * R);
}

Math::Point3D getClosestRoot(double a, double b, double det, ray::Ray ray)
{
    double root1 = (-b + sqrt(det)) / (2 * a);
    double root2 = (-b - sqrt(det)) / (2 * a);

    Math::Point3D pos1 = {(ray.origin.X + ray.direction.X * root1), (ray.origin.Y + ray.direction.Y * root1), (ray.origin.Z + ray.direction.Z * root1)};
    Math::Point3D pos2 = {(ray.origin.X + ray.direction.X * root2), (ray.origin.Y + ray.direction.Y * root2), (ray.origin.Z + ray.direction.Z * root2)};

    Math::Vector3D vect1 = {pos1.X - ray.origin.X, pos1.Y - ray.origin.Y, pos1.Z - ray.origin.Z};
    Math::Vector3D vect2 = {pos2.X - ray.origin.X, pos2.Y - ray.origin.Y, pos2.Z - ray.origin.Z};

    if (vect1.length() < vect2.length())
        return pos1;
    return pos2;
}

Maybe<Math::Point3D> ray::Cylinder::hit(const ray::Ray &ray) const
{
    double a = calcA(ray.direction, _direction);
    double b = calcB(ray.direction, _direction, ray.origin, _position);
    double c = calcC(ray.origin, _position, _direction, _radius);
    double det = b * b - 4 * (a * c);
    if (det < 0)
        return {};
    return Maybe{getClosestRoot(a, b, det, ray)};
}

Math::Vector3D ray::Cylinder::getNormale(const Math::Point3D& point, __attribute__((unused))const ray::Ray& camRay) const
{
    Math::Vector3D normal = {point.X - _position.X, point.Y - _position.Y, point.Z - _position.Z};
    return normal / normal.length();
}

extern "C" ray::INode *create(__attribute__((unused))const std::map<std::string, std::string> &attributes)
{
    return new ray::Cylinder();
}