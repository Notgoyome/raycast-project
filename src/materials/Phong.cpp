/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PhongModel.cpp
*/

#include "Phong.hpp"

Math::Vector3D getLightDirection(Phong::Light light, Math::Point3D position)
{
    Math::Point3D lightPos = light.getPosition();
    Math::Vector3D res = {lightPos.X - position.X, lightPos.Y - position.Y, lightPos.Z - position.Z};

    res /= res.length();
    return res;
}

Math::Vector3D getLightReflection(Math::Vector3D lightDir, Math::Vector3D normale)
{
    Math::Vector3D res = lightDir - normale * 2 * lightDir.dot(normale);
    return res / res.length();
}

unsigned int Phong::Model::getPhongForValues(int idx) const
{
    double sum = 0;

    for (const Light& light : _lights) {
        Math::Vector3D lightDir = getLightDirection(light, _pos);
        Math::Vector3D reflection = getLightReflection(lightDir, _normale);

        double diff = std::max(lightDir.dot(_normale), 0.0);
        sum += _kd(0, idx) * diff * light.getDiffuseIntensity()(0, idx);

        sum += _ks(0, idx) * pow(reflection.dot(_view), _alpha) * light.getSpecularIntensity()(0, idx);
    }
    return static_cast<unsigned int>(std::min(static_cast<float>(_ka(0, idx) * _ia + sum) * 255.F, 255.F));
}

RGB Phong::Model::calculateColor()
{
    unsigned int RRes = getPhongForValues(0);
    unsigned int GRes = getPhongForValues(1);
    unsigned int BRes = getPhongForValues(2);

    return {RRes, GRes, BRes};
}
