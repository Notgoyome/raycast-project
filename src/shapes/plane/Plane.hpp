//
// Created by Guillaume Tran on 26/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP

#include "../AShape.hpp"
#include "Ray.hpp"
#include "../../../include/Maybe.hpp"
#include <cmath>
#include <memory>
#include <map>
#include "../../scenes/base/Scene.hpp"

namespace ray {
    class Plane : public ray::AShape {
        Math::Point3D center;
        Math::Matrix<4, 1> _normale;

    public:
        Plane() = default;
        ~Plane() override = default;

        void setPosition();
        void initValues() override;

        Maybe<Math::Point3D> hit(const ray::Ray &ray) const override;
        Math::Vector3D getNormale(const Math::Point3D &point, const ray::Ray& camRay) const override;
    };
}
extern "C" ray::INode *create(std::map<std::string, std::string>& properties);

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
