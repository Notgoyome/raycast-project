//
// Created by Guillaume Tran on 26/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP

#include "../AShape.hpp"
#include "Ray.hpp"
#include "../../../include/Maybe.hpp"
#include "Ray.hpp"
#include <cmath>
#include <memory>
#include <map>

namespace ray {
    class Plane : public ray::AShape {
    public:
        Plane();

        ~Plane() override = default;

        Maybe<Math::Point3D> hit(const ray::Ray &ray) override;

        Math::Vector3D getNormale(const Math::Point3D &point) override;

    private:
    };
}
extern "C" ray::Plane *create(std::map<std::string, std::string>& properties);
extern "C" ray::type getType();

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
