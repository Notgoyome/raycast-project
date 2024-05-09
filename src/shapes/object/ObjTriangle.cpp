/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjTriangle.cpp
*/

#include "ObjTriangle.hpp"

namespace ray {

    void ray::ObjTriangle::initValues()
    {
        AShape::initValues();
        _direction = Math::Vector3D(0, 1, 0);
        initNormale();
    }

    Maybe<PosShapePair> ray::ObjTriangle::hit(const ray::Ray &ray) const
    {
        Math::Vector3D v0v1 = {_p2.X - _p1.X, _p2.Y - _p1.Y, _p2.Z - _p1.Z};
        Math::Vector3D v0v2 = {_p3.X - _p1.X, _p3.Y - _p1.Y, _p3.Z - _p1.Z};

        double nDotRayDirection = _normal.dot(ray.direction);
        if (std::abs(nDotRayDirection) < 0.0000001)
            return Maybe<PosShapePair>{};
        double D = -_normal.dot({_p1.X, _p1.Y, _p1.Z});
        double t = -(_normal.dot({ray.origin.X, ray.origin.Y, ray.origin.Z}) + D) / _normal.dot(ray.direction);

        if (t < 0)
            return Maybe<PosShapePair>{};
        Math::Point3D P = ray.origin + ray.direction * t;
        Math::Vector3D C;
        Math::Vector3D vp0 = {P.X - _p1.X, P.Y - _p1.Y, P.Z - _p1.Z};
        C = v0v1.product(vp0);

        if (_normal.dot(C) < 0)
            return Maybe<PosShapePair>{};

        Math::Vector3D v1v2 = {_p3.X - _p2.X, _p3.Y - _p2.Y, _p3.Z - _p2.Z};
        Math::Vector3D vp1 = {P.X - _p2.X, P.Y - _p2.Y, P.Z - _p2.Z};
        C = v1v2.product(vp1);

        if (_normal.dot(C) < 0)
            return Maybe<PosShapePair>{};

        Math::Vector3D v2v0 = {_p1.X - _p3.X, _p1.Y - _p3.Y, _p1.Z - _p3.Z};
        Math::Vector3D vp2 = {P.X - _p3.X, P.Y - _p3.Y, P.Z - _p3.Z};
        C = v2v0.product(vp2);

        if (_normal.dot(C) < 0)
            return Maybe<PosShapePair>{};
        return Maybe<PosShapePair>{std::make_pair(P, std::make_shared<ObjTriangle>(*this))};
    }

    Math::Vector3D ray::ObjTriangle::getNormale(const Math::Point3D& point, const ray::Ray& camRay) const
    {
        (void)point;
        Math::Vector3D camDir = camRay.direction;
        if (_normal.dot(camDir) > 0)
            return _normal * -1;
        return _normal;
    }

    ray::Ray ray::ObjTriangle::getRefraction(
        const std::shared_ptr<ray::IScene>& scene,
        Math::Point3D pos,
        Math::Vector3D dir) const
    {
        // WARNING: this only works when the Object is not a plane
        Math::Vector3D refracted = dir.refract(_normal, 1, _material->getRefractionIndex());
        Ray refractedRay = {pos + refracted * 0.0001, refracted};
        Maybe<PosShapePair> hit = scene->hit(refractedRay);

        if (hit.has_value() == false)
            return {pos + dir * 0.0001, dir};
        Math::Vector3D hitNormale = hit.value().second->getNormale(hit.value().first, refractedRay);
        Math::Vector3D refracted2 = refracted.refract(hitNormale, _material->getRefractionIndex(), 1);
        return {hit.value().first + refracted2 * 0.0001, refracted2};
    }

    void ray::ObjTriangle::initNormale()
    {
        Math::Vector3D edge1 = {_p2.X - _p1.X, _p2.Y - _p1.Y, _p2.Z - _p1.Z};
        Math::Vector3D edge2 = {_p3.X - _p1.X, _p3.Y - _p1.Y, _p3.Z - _p1.Z};
        _normal = edge1.product(edge2);
        _normal = _normal / _normal.length();
    }

    void ray::ObjTriangle::setPoint(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3)
    {
        _p1 = p1;
        _p2 = p2;
        _p3 = p3;
    }

    void ray::ObjTriangle::setp1(Math::Point3D p1)
    {
        _p1 = p1;
    }

    void ray::ObjTriangle::setp2(Math::Point3D p2)
    {
        _p2 = p2;
    }

    void ray::ObjTriangle::setp3(Math::Point3D p3)
    {
        _p3 = p3;
    }

    void ray::ObjTriangle::setMaterial(std::shared_ptr<ray::IMaterial> material)
    {
        _material = material;
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

} // ray
