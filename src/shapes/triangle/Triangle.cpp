//
// Created by Guillaume Tran on 07/05/2024.
//

#include "Triangle.hpp"

void ray::Triangle::initValues()
{
    AShape::initValues();
    _direction = Math::Vector3D(0, 1, 0);
}

Maybe<PosShapePair> ray::Triangle::hit(const ray::Ray &ray) const {
    const double epsilon = 0.0001;
    Math::Vector3D edge1 = {_p2.X - _p1.X, _p2.Y - _p1.Y, _p2.Z - _p1.Z};
    Math::Vector3D edge2 = {_p3.X - _p1.X, _p3.Y - _p1.Y, _p3.Z - _p1.Z};
    Math::Vector3D h = ray.direction.product(edge2);
    if (edge1.dot(h) > -epsilon)
        return {};
    double a = edge1.dot(h);

    if (a > -epsilon && a < epsilon)
        return {};

    double f = 1.0 / a;
    Math::Vector3D s = {ray.origin.X - _p1.X,
                        ray.origin.Y - _p1.Y,
                        ray.origin.Z - _p1.Z};
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return {};

    Math::Vector3D q = s.product(edge1);
    double v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return {};
    double t = f * edge2.dot(q);

    if (t > epsilon)
        return Maybe<PosShapePair>(std::make_pair(ray.origin + ray.direction * t, nullptr));
    return {};
}


Math::Vector3D ray::Triangle::getNormale(const Math::Point3D& point, const ray::Ray& camRay) const
{
    (void)point;
    (void)camRay;
    Math::Vector3D edge1 = {_p2.X - _p1.X, _p2.Y - _p1.Y, _p2.Z - _p1.Z};
    Math::Vector3D edge2 = {_p3.X - _p1.X, _p3.Y - _p1.Y, _p3.Z - _p1.Z};
    Math::Vector3D normal = edge1.product(edge2);
    Math::Vector3D camDir = camRay.direction;
    if (normal.dot(camDir) > 0)
        normal = normal * -1;
    return normal / normal.length();
}

void ray::Triangle::setPoint(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3)
{
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;
}

void ray::Triangle::setp1(Math::Point3D p1)
{
    _p1 = p1;
}

void ray::Triangle::setp2(Math::Point3D p2)
{
    _p2 = p2;
}

void ray::Triangle::setp3(Math::Point3D p3)
{
    _p3 = p3;
}


Math::Point3D StringToPoint3D(std::string str)
{
    Math::Point3D point;
// get the 3 values from the string
    std::vector<std::string> values;
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        values.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    values.push_back(str);
    point.X = std::stod(values[0]);
    point.Y = std::stod(values[1]);
    point.Z = std::stod(values[2]);
    return point;
}