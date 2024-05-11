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

    Math::Vector2D ObjTriangle::getUVMapping(Math::Point3D coords) const
    {
        // A -> p1
        // B -> p2
        // C -> p3
        // Math::Vector3D AB = Math::Vector3D{_p2 - _p1};
        // Math::Vector3D AC = Math::Vector3D{_p3 - _p1};
        //
        // Math::Vector3D PA = Math::Vector3D{_p1 - coords};
        // Math::Vector3D PB = Math::Vector3D{_p2 - coords};
        // Math::Vector3D PC = Math::Vector3D{_p3 - coords};
        //
        // double area = AB.product(AC).length() * (1.f / 2.f);
        // double delta1 = PB.product(PC).length() / (2 * area);
        // double delta2 = PC.product(PA).length() / (2 * area);
        // double delta3 = PA.product(PB).length() / (2 * area);
        //
        // double sum = delta1 + delta2 + delta3;
        // double finalD1 = delta1 / sum;
        // double finalD2 = delta2 / sum;
        // double finalD3 = delta3 / sum;
        //
        // double u = finalD1 * _uv1.first + finalD2 * _uv2.first + finalD3 * _uv3.first;
        // double v = finalD1 * _uv1.second + finalD2 * _uv2.second + finalD3 * _uv3.second;
        // return {u, v};
        Math::Vector3D v0 = _p2 - _p1, v1 = _p3 - _p1, v2 = coords - _p1;
        double d00 = v0.dot(v0);
        double d01 = v0.dot(v1);
        double d11 = v1.dot(v1);
        double d20 = v2.dot(v0);
        double d21 = v2.dot(v1);
        double denom = d00 * d11 - d01 * d01;
        double v = (d11 * d20 - d01 * d21) / denom;
        double w = (d00 * d21 - d01 * d20) / denom;
        double u = 1.0f - v - w;

        return {
            u * _uv1.first + v * _uv2.first + w * _uv3.first,
            u * _uv1.second + v * _uv2.second + w * _uv3.second
        };
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

    void ObjTriangle::setUvCoords(Math::Vector2D uv1, Math::Vector2D uv2,
        Math::Vector2D uv3)
    {
        _uv1 = uv1;
        _uv2 = uv2;
        _uv3 = uv3;
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
