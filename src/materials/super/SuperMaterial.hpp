/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SuperMaterial.hpp
*/

#ifndef SUPERMATERIAL_HPP
#define SUPERMATERIAL_HPP

#include "../IMaterial.hpp"
#include "INode.hpp"
#include "RGB.hpp"
#include "../AMaterial.hpp"
#include "../Phong.hpp"
#include "../../lights/ILight.hpp"
#include "../../scenes/base/Scene.hpp"

namespace ray {

    class SuperMaterial : public ray::AMaterial {
        Math::Matrix<1, 3> _kd;
        Math::Matrix<1, 3> _ka;
        Phong::Model _phong;

    public:
        SuperMaterial(
            double specularExponent,
            Math::Matrix<1, 3> ka,
            Math::Matrix<1, 3> kd,
            Math::Matrix<1, 3> ks,
            Math::Matrix<1, 3> ke,
            double refractionIndex,
            double transparency,
            double shadowQuality,
            double ambiantOccQuality);
        ~SuperMaterial() override = default;

        [[nodiscard]] RGB getColor(int recursive, Math::Point3D collisionPoint,
            Math::Vector3D normale, Math::Point3D camPos,
            const std::shared_ptr<ray::IShape>& shape,
            const std::shared_ptr<ray::IScene>& scene) const override;

        void setSkybox();
    };

}

#endif //SUPERMATERIAL_HPP
