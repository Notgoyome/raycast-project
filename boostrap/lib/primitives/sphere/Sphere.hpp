//
// Created by Guillaume Tran on 25/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP

#include "../APrimitive.hpp"
#include "../../../include/Ray.hpp"

class Sphere : public APrimitive {
public:
    bool hit(const Raytracer::Ray &ray) override;
private:
    float radius;
    Math::Vector3D center;
};


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
