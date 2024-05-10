/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** GlassMaterial.hpp
*/

#ifndef GLASSMATERIAL_HPP
#define GLASSMATERIAL_HPP

#include <map>

#include "../AMaterial.hpp"
#include "../Phong.hpp"

namespace ray {

    class GlassMaterial : public AMaterial {
        Math::Matrix<1, 3> _kd;
        Phong::Model _phong;

    public:
        GlassMaterial(RGB color, double transparency);

        [[nodiscard]] RGB getColor(
            int recursion,
            Math::Point3D collisionPoint,
            Math::Vector3D normale,
            Math::Point3D camPos,
            const std::shared_ptr<ray::IShape> &shape,
            const std::shared_ptr<ray::IScene> &scene) const override;
    };

} // ray

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //GLASSMATERIAL_HPP
