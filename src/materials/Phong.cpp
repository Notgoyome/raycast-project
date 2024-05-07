/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PhongModel.cpp
*/

#include "Phong.hpp"
#include "../scenes/base/Scene.hpp"
#include "utils/getClosest.h"

double pointsDistance(Math::Point3D point1, Math::Point3D point2)
{
    Math::Vector3D vec = {point1.X - point2.X, point1.Y - point2.Y, point1.Z - point2.Z};
    return vec.length();
}

Math::Point3D roundPoint(Math::Point3D point)
{
    return {round(point.X * 10000) / 10000, round(point.Y * 10000) / 10000, round(point.Z * 10000) / 10000};
}

Math::Vector3D rotateVectorAlong(Math::Vector3D toRotate, Math::Vector3D axis, double angle)
{
    return toRotate * std::cos(angle) +
        axis.product(toRotate) * std::sin(angle) +
            axis * axis.dot(toRotate) * (1 - std::cos(angle));
}

Math::Vector3D getPerpendicularVector(Math::Vector3D vec)
{
    Math::Vector3D res = vec.product({0, 0, 1});
    if (res != Math::Vector3D{0, 0, 0})
        return res;
    res = vec.product({0, 1, 0});
    if (res != Math::Vector3D{0, 0, 0})
        return res;
    return vec.product({1, 0, 0});
}

bool isBehind(Math::Point3D pos, Math::Point3D lightPos, Math::Vector3D lightDir)
{
    Math::Vector3D lightToPos = {pos.X - lightPos.X, pos.Y - lightPos.Y, pos.Z - lightPos.Z};
    double angle = lightToPos.dot(lightDir);

    return angle < 0;
}

bool hitsBefore(const std::vector<std::shared_ptr<ray::IShape>>& objects, Math::Point3D pos, ray::Ray ray)
{
    std::vector hits = {pos};

    for (const std::shared_ptr<ray::IShape>& object : objects) {
        Maybe<Math::Point3D> maybePos = object->hit(ray);

        if (maybePos.has_value() && isBehind(maybePos.value(), ray.origin, ray.direction * -1) == false)
            hits.push_back(maybePos.value());
    }
    Math::Point3D closest = roundPoint(getClosest(hits, ray.origin));
    Math::Point3D actual = roundPoint(pos);

    if (closest == actual)
        return false;
    return true;
}

double getAmbientOcclusion(Math::Vector3D normale,
    const std::shared_ptr<ray::IScene>& scene,
    Math::Point3D pos, double quality)
{
    if (quality == 0)
        return 1;

    Math::Vector3D perpendicular = getPerpendicularVector(normale);
    Math::Vector3D actualRotation;
    ray::Ray ray = {pos + normale * 0.0001, normale}; // 0.0001 offset to avoid hitting the same object
    Maybe<PosShapePair> maybeHit;
    double res = 0;
    double distance;
    int nbAngles = quality < 10 ? static_cast<int>(quality) : 10;
    int nbRotates = quality > 10 ? static_cast<int>(quality) / 10 : 4;

    for (int angle = 0; angle < nbAngles; angle++) {
        actualRotation = rotateVectorAlong(perpendicular, normale, 2 * M_PI * angle / (nbAngles * 2));
        for (int rotate = -(nbRotates / 2) + 1; rotate < nbRotates / 2; rotate++) {
            ray.direction = rotateVectorAlong(normale, actualRotation, 2 * M_PI * rotate / (nbRotates * 2));
            maybeHit = scene->hit(ray);
            distance = pointsDistance(pos, maybeHit.value().first);
            if (maybeHit.has_value() && distance < 10)
                res += distance / 10;
            else
                res += 1;
        }
    }
    return res / (nbAngles * (nbRotates - 1));
}

RGB getLightColor(const std::shared_ptr<ray::ILight>& light,
    const std::vector<std::shared_ptr<ray::IShape>>& scene, Math::Point3D pos,
    double quality)
{
    ray::Ray lightRay = light->getIncidentVector(pos);
    Math::Vector3D perpendicular = getPerpendicularVector(lightRay.direction);
    Math::Vector3D actualRotation;
    ray::Ray ray = {lightRay.origin, lightRay.direction};

    int nbHits = 0;
    int nbAngles = quality < 10 ? static_cast<int>(quality) : 10;
    int nbScales = quality > 10 ? static_cast<int>(quality) / 10 : 1;
    perpendicular /= perpendicular.length();

    for (int angle = 0; angle < nbAngles; angle++) {
        actualRotation = rotateVectorAlong(perpendicular, lightRay.direction, 2 * M_PI * angle / nbAngles);
        for (int scale = 1; scale <= nbScales; scale++) {
            ray.origin = lightRay.origin + actualRotation * (scale * 1.5);
            ray.direction = {ray.origin.X - pos.X, ray.origin.Y - pos.Y, ray.origin.Z - pos.Z};
            if (hitsBefore(scene, pos, ray) == false)
                nbHits++;
        }
    }
    return light->getColor() * (static_cast<float>(nbHits) / static_cast<float>(nbScales * nbAngles));
}

Math::Matrix<1, 3> getLightDiffuseIntensity(RGB lightColor)
{
    float coef = 1.5;

    Math::Matrix<1, 3> res{{
        {
            static_cast<float>(lightColor.R) / 255.f / coef,
            static_cast<float>(lightColor.G) / 255.f / coef,
            static_cast<float>(lightColor.B) / 255.f / coef
        }}};

    return res;
}

Math::Matrix<1, 3> getLightSpecularIntensity(RGB lightColor)
{
    float coef = 2;

    Math::Matrix<1, 3> res{{
        {
            static_cast<float>(lightColor.R) / 255.f / coef,
            static_cast<float>(lightColor.G) / 255.f / coef,
            static_cast<float>(lightColor.B) / 255.f / coef
        }}};

    return res;
}

Math::Vector3D getLightReflection(Math::Vector3D lightDir, Math::Vector3D normale)
{
    Math::Vector3D res = lightDir - normale * 2 * lightDir.dot(normale);
    return res / res.length();
}

RGB getReflection(const std::shared_ptr<ray::IScene>& scene,
    Math::Point3D pos, Math::Vector3D normale,
    Math::Vector3D view, int recursive)
{
    Math::Vector3D reflect = view - normale * 2 * view.dot(normale);
    ray::Ray ray = {pos + reflect * 0.001, reflect};
    Maybe<PosShapePair> maybeHit = scene->hit(ray);
    Math::Point3D collision;
    std::shared_ptr<ray::IShape> shape;
    Math::Vector3D reflectNormale;
    Math::Vector3D reflectView;
    double contribution;

    if (maybeHit.has_value()) {
        collision = maybeHit.value().first;
        shape = maybeHit.value().second;
        reflectNormale = shape->getNormale(collision, ray);
        reflectView = {pos.X - collision.X, pos.Y - collision.Y, pos.Z - collision.Z};
        reflectView /= reflectView.length();
        contribution = reflectNormale.dot(reflectView);
        contribution = contribution < 0 ? 0 : contribution;
        contribution = contribution > 1 ? 1 : contribution;

        return shape->getMaterial()->getColor(
            recursive + 1,
            collision,
            reflectNormale,
            pos,
            scene
        ) * contribution;
    }
    return {0, 0, 0};
}

Math::Matrix<1, 3> Phong::Model::getReflectionContribution(
    const std::shared_ptr<ray::IScene> &scene, Math::Point3D pos,
    Math::Vector3D normale, Math::Vector3D view, int recursive) const
{
    if (_ks(0, 0) == 0 && _ks(0, 1) == 0 && _ks(0, 2) == 0)
        return Math::Matrix<1, 3>{{{0, 0, 0}}};
    if (recursive >= REFLECTION_RECURSION_LIMIT)
        return Math::Matrix<1, 3>{{{0, 0, 0}}};
    RGB color = getReflection(scene, pos, normale, view * -1, recursive);

    return Math::Matrix<1, 3>{{
        {
            color.R * _ks(0, 0) / 255,
            color.G * _ks(0, 1) / 255,
            color.B * _ks(0, 2) / 255
        }}};
}

Math::Matrix<1, 3> Phong::Model::getLightsContribution(
    Math::Vector3D normale,
    Math::Point3D pos,
    Math::Vector3D view,
    const std::shared_ptr<ray::IScene>& scene) const
{
    double sumR = 0;
    double sumG = 0;
    double sumB = 0;

    const std::vector<std::shared_ptr<ray::IShape>> objects = scene->getShapes();
    const std::vector<std::shared_ptr<ray::ILight>> lights = scene->getLights();
    double ambiantOcc = getAmbientOcclusion(normale, scene, pos, _ambOccQuality);

    for (const std::shared_ptr<ray::ILight>& light : lights) {
        Math::Vector3D lightDir = light->getIncidentVector(pos).direction;
        Math::Vector3D reflection = getLightReflection(lightDir, normale);
        RGB lightColor = getLightColor(light, objects, pos, _shadowQuality);
        lightColor *= ambiantOcc;

        if (lightColor == RGB{0, 0, 0})
            continue;
        double diff = std::max(lightDir.dot(normale), 0.0);
        double ref = std::max(pow(reflection.dot(view), _alpha), 0.0);

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
    return Math::Matrix<1, 3>{{{sumR, sumG, sumB}}};
}

RGB Phong::Model::calculateColor(
    const std::shared_ptr<ray::IScene>& scene,
    Math::Vector3D view,
    Math::Point3D pos,
    Math::Vector3D normale,
    int recursion) const
{
    unsigned int RRes;
    unsigned int GRes;
    unsigned int BRes;

    Math::Matrix<1, 3> lightsContribution = getLightsContribution(normale, pos, view, scene);
    Math::Matrix<1, 3> reflectionContribution = getReflectionContribution(scene, pos, normale, view, recursion);

    RRes = static_cast<unsigned int>(
        std::min(
            static_cast<float>(_ka(0, 0) * _ia + lightsContribution(0, 0) + reflectionContribution(0, 0)) * 255.F,
            255.F
            )
        );
    GRes = static_cast<unsigned int>(
        std::min(
            static_cast<float>(_ka(0, 1) * _ia + lightsContribution(0, 1) + reflectionContribution(0, 1)) * 255.F,
            255.F
            )
        );
    BRes = static_cast<unsigned int>(
        std::min(
            static_cast<float>(_ka(0, 2) * _ia + lightsContribution(0, 2) + reflectionContribution(0, 2)) * 255.F,
            255.F
            )
        );
    return RGB{RRes, GRes, BRes};
}
