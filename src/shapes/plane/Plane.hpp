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

class Plane : public ray::AShape {
public:
    Plane();
    ~Plane() = default;
    Maybe<Math::Point3D> hit(const Raytracer::Ray ray) override;
    Math::Vector3D getNormale(const Math::Point3D point);
private:
};


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
