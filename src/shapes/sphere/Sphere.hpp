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

namespace RayTracer {
    class Sphere : public ray::AShape {
    public:
        float radius;
        Math::Point3D center;
        std::shared_ptr<ray::AMaterial> material;

        Sphere(float radius, Math::Point3D center);

        ~Sphere() = default;

        Maybe<Math::Point3D> hit(const Raytracer::Ray ray) override;

        Math::Vector3D getNormale(const Math::Point3D point) override;

    private:
    };
}

extern "C" RayTracer::Sphere *create();
extern "C" ray::type getType();
#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
