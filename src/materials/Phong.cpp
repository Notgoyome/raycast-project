/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PhongModel.cpp
*/

#include "Phong.hpp"
#include "../scenes/base/Scene.hpp"
#include "utils/getClosest.h"

Math::Point3D roundPoint(Math::Point3D point)
{
    return {round(point.X * 10000) / 10000, round(point.Y * 10000) / 10000, round(point.Z * 10000) / 10000};
}

Math::Vector3D vectorProduct(Math::Vector3D a, Math::Vector3D b)
{
    return {a.Y * b.Z - a.Z * b.Y,
        a.Z * b.X - a.X * b.Z,
        a.X * b.Y - a.Y * b.X};
}

Math::Vector3D rotateVectorAlong(Math::Vector3D toRotate, Math::Vector3D axis, double angle)
{
    return toRotate * std::cos(angle) +
        vectorProduct(axis, toRotate) * std::sin(angle) +
            axis * axis.dot(toRotate) * (1 - std::cos(angle));
}

Math::Vector3D getPerpendicularVector(Math::Vector3D vec)
{
    Math::Vector3D res = vectorProduct(vec, {0, 0, 1});
    if (res != Math::Vector3D{0, 0, 0})
        return res;
    res = vectorProduct(vec, {0, 1, 0});
    if (res != Math::Vector3D{0, 0, 0})
        return res;
    return vectorProduct(vec, {1, 0, 0});
}

bool isBehind(Math::Point3D pos, Math::Point3D lightPos, Math::Vector3D lightDir)
{
    Math::Vector3D lightToPos = {pos.X - lightPos.X, pos.Y - lightPos.Y, pos.Z - lightPos.Z};
    double angle = lightToPos.dot(lightDir);

    return angle > 0;
}

bool hitsBefore(std::vector<std::shared_ptr<ray::IShape>> objects, Math::Point3D pos, ray::Ray ray)
{
    std::vector hits = {pos};

    for (const std::shared_ptr<ray::IShape>& object : objects) {
        Maybe<Math::Point3D> maybePos = object->hit(ray);

        if (maybePos.has_value() && isBehind(maybePos.value(), ray.origin, ray.direction) == false)
            hits.push_back(maybePos.value());
    }
    Math::Point3D closest = roundPoint(getClosest(hits, ray.origin));
    Math::Point3D actual = roundPoint(pos);

    if (closest == actual)
        return false;
    isBehind(closest, ray.origin, ray.direction);
    return true;
}

RGB getLightColor(std::shared_ptr<ray::ILight> light,
    std::vector<std::shared_ptr<ray::IShape>> scene, Math::Point3D pos,
    double quality)
{
    Math::Vector3D lightDir = light->getIncidentVector(pos);
    Math::Vector3D perpendicular = getPerpendicularVector(lightDir);
    Math::Vector3D actualRotation;
    Math::Point3D lightPos = light->getPos();
    ray::Ray ray = {lightPos, lightDir};

    int nbHits = 0;
    int nbAngles = quality < 10 ? static_cast<int>(quality) : 10;
    int nbScales = quality > 10 ? static_cast<int>(quality) / 10 : 1;
    perpendicular /= perpendicular.length();

    for (int angle = 0; angle < nbAngles; angle++) {
        actualRotation = rotateVectorAlong(perpendicular, lightDir, 2 * M_PI * angle / nbAngles);
        for (int scale = 1; scale <= nbScales; scale++) {
            ray.origin = lightPos + actualRotation * scale;
            ray.direction = {ray.origin.X - pos.X, ray.origin.Y - pos.Y, ray.origin.Z - pos.Z};
            if (hitsBefore(scene, pos, ray) == false)
                nbHits++;
        }
    }
    return light->getColor() * (static_cast<float>(nbHits) / static_cast<float>(nbScales * nbAngles));
}

Math::Matrix<1, 3> getLightDiffuseIntensity(RGB lightColor)
{
    Math::Matrix<1, 3> res{{
        {
            lightColor.R / 255.f / 2.f,
            lightColor.G / 255.f / 2.f,
            lightColor.B / 255.f / 2.f
        }}};

    return res;
}

Math::Matrix<1, 3> getLightSpecularIntensity(RGB lightColor)
{
    Math::Matrix<1, 3> res{{
        {
            lightColor.R / 255.f / 2,
            lightColor.G / 255.f / 2,
            lightColor.B / 255.f / 2
        }}};

    return res;
}

Math::Vector3D getLightReflection(Math::Vector3D lightDir, Math::Vector3D normale)
{
    Math::Vector3D res = lightDir - normale * 2 * lightDir.dot(normale);
    return res / res.length();
}

RGB Phong::Model::calculateColor(std::vector<std::shared_ptr<ray::IShape>> objects)
{
    double sumR = 0;
    double sumG = 0;
    double sumB = 0;

    unsigned int RRes;
    unsigned int GRes;
    unsigned int BRes;

    for (const std::shared_ptr<ray::ILight>& light : _lights) {
        Math::Vector3D lightDir = light->getIncidentVector(_pos);
        Math::Vector3D reflection = getLightReflection(lightDir, _normale);
        RGB lightColor = getLightColor(light, objects, _pos, _shadowQuality);

        double diff = std::max(lightDir.dot(_normale), 0.0);
        double ref = std::max(pow(reflection.dot(_view), _alpha), 0.0);

        sumR += _kd(0, 0) * diff * getLightDiffuseIntensity(lightColor)(0, 0);
        if (diff > 0.2)
            sumR += _ks(0, 0) * ref * getLightSpecularIntensity(lightColor)(0, 0);
        sumG += _kd(0, 1) * diff * getLightDiffuseIntensity(lightColor)(0, 1);
        if (diff > 0.2)
            sumG += _ks(0, 1) * ref * getLightSpecularIntensity(lightColor)(0, 1);
        sumB += _kd(0, 2) * diff * getLightDiffuseIntensity(lightColor)(0, 2);
        if (diff > 0.2)
            sumB += _ks(0, 2) * ref * getLightSpecularIntensity(lightColor)(0, 2);
    }
    RRes = static_cast<unsigned int>(std::min(static_cast<float>(_ka(0, 0) * _ia + sumR) * 255.F, 255.F));
    GRes = static_cast<unsigned int>(std::min(static_cast<float>(_ka(0, 1) * _ia + sumG) * 255.F, 255.F));
    BRes = static_cast<unsigned int>(std::min(static_cast<float>(_ka(0, 2) * _ia + sumB) * 255.F, 255.F));
    return RGB{RRes, GRes, BRes};
}
