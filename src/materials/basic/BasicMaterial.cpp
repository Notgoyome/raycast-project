/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RedBasicMaterial.cpp
*/

#include "BasicMaterial.hpp"

ray::BasicMaterial::BasicMaterial(RGB color,
    double shadowQuality,
    double ambiantOccQuality,
    double roughness) : _color(color),
    _phong({},
        0.05,
        50,
        shadowQuality,
        ambiantOccQuality,
        Math::Matrix<1, 3>({{1, 1, 1}}),
        Math::Matrix<1, 3>{{{0, 0, 0}}},
        Math::Matrix<1, 3>{{{roughness, roughness, roughness}}})
{
    _phong.setKd(Math::Matrix<1, 3>({{color.R / 255.f, color.G / 255.f, color.B / 255.f}}));
}

RGB ray::BasicMaterial::getColor(int recursive, Math::Point3D collisionPoint,
                                 Math::Vector3D normale, Math::Point3D camPos,
                                 const std::shared_ptr<ray::IScene> &scene) const
{
    Math::Vector3D view = {camPos.X - collisionPoint.X, camPos.Y - collisionPoint.Y, camPos.Z - collisionPoint.Z};
    view /= view.length();

    if (recursive > REFLECTION_RECURSION_LIMIT)
        return _color;
    return _phong.calculateColor(scene, view, collisionPoint, normale, recursive);
}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes)
{
    if (attributes.find("color") == attributes.end())
        throw ray::NodeError("IMaterial: missing color attribute", "BasicMaterial.cpp");
    if (attributes.find("shadow_quality") == attributes.end())
        throw ray::NodeError("IMaterial: missing shadow_quality attribute (number between 0 and 100 for render time)", "BasicMaterial.cpp");
    if (attributes.find("ambiant_occlusion") == attributes.end())
        throw ray::NodeError("IMaterial: missing ambiant_occlusion attribute (number between 0 and 100 for render time)", "BasicMaterial.cpp");
    if (attributes.find("roughness") == attributes.end())
        throw ray::NodeError("IMaterial: missing roughness attribute (number between 0 and 1 for material roughness)", "BasicMaterial.cpp");

    Maybe<RGB> color = RGB::fromStr(attributes.at("color"));
    double shadowQuality = std::stod(attributes.at("shadow_quality"));
    double ambiantOcclusion = std::stod(attributes.at("ambiant_occlusion"));
    double roughness = std::stod(attributes.at("roughness"));

    if (!color.has_value())
        throw ray::NodeError("IMaterial: invalid color attribute", "BasicMaterial.cpp");
    if (shadowQuality < 1 || shadowQuality > 100)
        throw ray::NodeError("IMaterial: shadow_quality must be a number between 1 and 100", "BasicMaterial.cpp");
    if (ambiantOcclusion < 0 || ambiantOcclusion > 100)
        throw ray::NodeError("IMaterial: ambiant_occlusion must be a number between 0 and 100", "BasicMaterial.cpp");
    if (roughness < 0 || roughness > 1)
        throw ray::NodeError("IMaterial: roughness must be a number between 0 and 1", "BasicMaterial.cpp");

    return new ray::BasicMaterial(color.value(), shadowQuality, ambiantOcclusion, roughness);
}
