//
// Created by Guillaume Tran on 25/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP

#include "../../../src/shapes/AShape.hpp"
#include "../../materials/IMaterial.hpp"
#include "../../../include/Maybe.hpp"
#include "Ray.hpp"
#include <cmath>
#include <map>
#include <memory>

namespace ray {

    class Sphere : public ray::AShape {
        void setRadius();
        void setPosition();
    public:
        double radius = -1;
        Math::Point3D center;

        Sphere() = default;
        ~Sphere() override = default;

        Maybe<Math::Point3D> hit(const ray::Ray& ray) override;
        Math::Vector3D getNormale(const Math::Point3D& point) override;
    };

}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
