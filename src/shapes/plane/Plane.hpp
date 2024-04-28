//
// Created by Guillaume Tran on 26/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP

#include "../AShape.hpp"
#include "Ray.hpp"
#include "math/Vector3D.hpp"

class Plane : public ray::AShape {
public:
    Plane(Math::Vector3D vec);
    ~Plane() = default;
    Maybe<Math::Point3D> hit(const Raytracer::Ray &ray) override;
private:
    float x;
    float y;
    float z;
};


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_PLANE_HPP
