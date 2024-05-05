/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RedBasicMaterial.hpp
*/

#ifndef REDBASICMATERIAL_HPP
#define REDBASICMATERIAL_HPP

#include "../IMaterial.hpp"
#include "INode.hpp"
#include "RGB.hpp"
#include "../AMaterial.hpp"
#include "../Phong.hpp"
#include "../../lights/ILight.hpp"
#include "../../scenes/base/Scene.hpp"

namespace ray {

    class BasicMaterial : public ray::AMaterial {
        RGB _color;
        Phong::Model _phong;
    public:
        BasicMaterial(RGB color, double shadowQuality, double ambiantOccQuality);
        ~BasicMaterial() override = default;

        [[nodiscard]] RGB getColor(int recursive, Math::Point3D collisionPoint,
            Math::Vector3D normale, Math::Point3D camPos,
            const std::shared_ptr<ray::IScene>& scene) override;
    };

}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //REDBASICMATERIAL_HPP
