//
// Created by Guillaume Tran on 25/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP

#include "../../../src/shapes/AShape.hpp"
#include "../../materials/AMaterial.hpp"
#include "../../../include/Maybe.hpp"
#include "Ray.hpp"
#include <cmath>
#include <memory>

namespace ray {
    class Sphere : public ray::AShape {
    public:
        float radius;
        Math::Point3D center;
        std::shared_ptr<ray::AMaterial> material;

        Sphere(float radius, Math::Point3D center);

        ~Sphere() override = default;

        Maybe<Math::Point3D> hit(const ray::Ray& ray) override;

        Math::Vector3D getNormale(const Math::Point3D& point) override;
    };
}


extern "C" ray::Sphere *create();
extern "C" ray::type getType();

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
