//
// Created by Guillaume Tran on 25/04/2024.
//

#include "Sphere.hpp"

#include "../../scenes/base/Scene.hpp"

void ray::Sphere::setRadius()
{
    Math::Vector3D scale = getScale();

    radius = scale.X;
}

void ray::Sphere::setPosition()
{
    center = Scene::getPosition(*this);
}

double calcA(Math::Vector3D D)
{
    return pow(D.X, 2) + pow(D.Y, 2) + pow(D.Z, 2);
}

double calcB(Math::Point3D O, Math::Vector3D D, Math::Point3D origin)
{
    return 2 * (D.X * (-origin.X + O.X) + D.Y * (-origin.Y + O.Y) + D.Z * (-origin.Z + O.Z));
}

double calcC(Math::Point3D O, Math::Point3D origin, double R)
{
    return pow(-origin.X + O.X, 2) + pow(-origin.Y + O.Y, 2) + pow(-origin.Z + O.Z, 2) - pow(R, 2);
}

double calcDet(double a, double b, double c)
{
    return pow(b, 2) - 4 * a * c;
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

Maybe<Math::Point3D> ray::Sphere::hit(const ray::Ray &ray)
{
    if (radius == -1) {
        applyMatrix();
        setPosition();
        setRadius();
    }
    double a = calcA(ray.direction);
    double b = calcB(ray.origin, ray.direction, center);
    double c = calcC(ray.origin, center, radius);
    double det = calcDet(a, b, c);

    if (det < 0) {
        return {};
    }
    return Maybe{getClosestRoot(a, b, det, ray)};
}

Math::Vector3D ray::Sphere::getNormale(const Math::Point3D& point, __attribute__((unused))const ray::Ray& camRay)
{
    Math::Vector3D normale = {point.X - center.X,
                              point.Y - center.Y,
                              point.Z - center.Z};
    return normale / normale.length();
}


extern "C" ray::INode *create(__attribute__((unused))const std::map<std::string, std::string> &attributes)
{
    return new ray::Sphere();
}
